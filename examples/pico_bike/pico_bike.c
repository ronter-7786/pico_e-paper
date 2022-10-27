/********************************************************
*														
* pico-bike:											
*    Display current speed, distance travelled, and	
*			elapsed time on e-paper display				
*														
********************************************************/
#include "pico_bike.h"


/////////////////////
// Local defines
/////////////////////

#define UPDATE_INTERVAL_MS	2000		// every 2 seconds update display

#define DISPLAY_SPLASH_SCREEN				0
#define DISPLAY_SUMMARY_SCREEN				1
#define DISPLAY_ELAPSED_TIME_SCREEN			2
#define DISPLAY_TOTAL_DISTANCE_SCREEN		3
#define DISPLAY_CURRENT_SPEED				4	

#define MULTICORE_FLAG						0xa55a

#define NUM_AVG_SPEED						10


typedef struct
{
	absolute_time_t		lastWheelRevTime;					// last time wheel revolution
	absolute_time_t		currentWheelRevTime;				// this time wheel revolution
}WHEEL_EVENT;

typedef struct
{
	absolute_time_t		buttonPressTime;					// when button was pressed
	absolute_time_t		buttonReleaseTime;					// when button released
	bool				bButtonPressActive;					// pressed, but not yet released... to detect 'long hold'
}BUTTON_EVENT;


/////////////////////
// Local variables
/////////////////////

static const char		strPico_bike[] =	"pico-bike";	// labels
static const char		strKm[] =			"km";						
static const char		strKph[] =			"km/h";

static mutex_t			frameBufferMutex;					// mutex to lock frame buffer
static semaphore_t		displayRefreshRequestSemaphore;		// semaphore to request framebuffer->screen refresh
static semaphore_t		updateRequestSemaphore;				// semaphore to trigger update display

static semaphore_t		wheelEventSemaphore;				// an event semaphore for every time the wheel does a revolution
static WHEEL_EVENT		wheelEvent;							// timestamps

static int64_t			elapsedTime_us,						// elapsed time of trip
						elapsedTime_ms,
						elapsedTime_sec,
						elapsedTime_min,
						elapsedTime_hour;

static double			fSpeedArray[NUM_AVG_SPEED];			// for calculating avg speed
uint8_t					iSpeedIndex;

static char				strSpeed[6];						// strings for the speed, distance & time
static char				strDistance[16];
static char				strTime[16];

//----------------------------------------------------------
// this selects the display we will use,  see CMakeLists.txt
//----------------------------------------------------------
#define	INKY			1
#define EPAPER_266		2

#if DISPLAY_TYPE == INKY
static DISPLAY_PARAMS	*pDisplayParams = &UC8151DDisplayParams;
#elif  DISPLAY_TYPE == EPAPER_266
static DISPLAY_PARAMS	*pDisplayParams = &EPD266DisplayParams;
#endif


/////////////////////
// Global variables
/////////////////////

/////////////////////
// Local functions
/////////////////////

static void displayHandler(void);
static int64_t alarm_callback(alarm_id_t id, void *user_data);
#if defined(DEMO_MODE)
static bool timer_callback(repeating_timer_t *rt);
#endif
static void __no_inline_not_in_flash_func(gpioIrqCallback)(void);



/********************************************************

	Main entry

*********************************************************/

int main()
{
	double				_fSpeed = 0,
						_fDistance_km = 0,
						_fDistance_mm = 0,
						_fDisplayedSpeed = 99.99,
						_fDisplayedDistance = 999.99;

	int64_t				_displayedElapsedTime_min = 99,
						_displayedElapsedTime_sec = 66;

	uint64_t			_iWheelRevTime_us;								// how long the wheel took for 1 rev
	
	double				_fWheelCircum_mm = WHEEL_DIAMETER_MM * M_PI;	// the wheel circumference in mm
	double				_fWheel_mm_perSecond;							// calculated mm/sec speed

	absolute_time_t		_start_time_us,
						_current_time_us,
						_last_display_update_time;

	int64_t				_deltaTime;

	uint32_t			_flagValue = 0;

	uint8_t				_displayWhat = DISPLAY_SPLASH_SCREEN;
	bool				_bNeedRefresh;

	uint8_t				*_pstrValue,
						*_pstrUnits;

	alarm_id_t			_alarmID = -1;

#if defined(DEMO_MODE)
	repeating_timer_t	_wheelRevTimerID;
	bool				_bInDemoMode = false,
						_bDemoAccelerate;
	int32_t				_demoWheelRev_ms = 500;		// start at 5 km/h
	absolute_time_t		_lastWheelSpeedChange;		// last time wheel revolution was changed

#endif


	// Initialize the GPIO pins //
	gpio_init(PICO_LED_PIN);								// define LED pin
	gpio_set_dir(PICO_LED_PIN,true);						// output
	gpio_put(PICO_LED_PIN,false);							// off

	gpio_init(WHEEL_REV_PIN);								// define wheel revolution pin
#if defined(DEMO_MODE)  
	gpio_set_dir(WHEEL_REV_PIN,true);						// output
	gpio_put(WHEEL_REV_PIN,true);							// off = high
#else
	gpio_set_dir(WHEEL_REV_PIN,false);						// input
	gpio_pull_up(WHEEL_REV_PIN);							// pulled up
	gpio_set_input_enabled(WHEEL_REV_PIN, true);
	gpio_add_raw_irq_handler( WHEEL_REV_PIN, gpioIrqCallback );
	gpio_set_irq_enabled(WHEEL_REV_PIN, GPIO_IRQ_EDGE_FALL, true);
	irq_set_enabled(IO_IRQ_BANK0, true);
#endif

	// create synchronization objects for core1 interaction & local use
	mutex_init( &frameBufferMutex );						// create a mutex to lock frame buffer
	sem_init( &displayRefreshRequestSemaphore, 0, 4 );		// counting semaphore to request frame refresh by coore 1
	sem_init( &updateRequestSemaphore, 1, 1 );				// binary semaphore to request update screen, 1 permit to start things off
	sem_init( &wheelEventSemaphore, 0, 1 );					// binary semaphore to indicate 1 wheel revolution

	/////////////////////////////////////////////////////////////////////////////////
	// start core 1 as the display refresh handler, it will refresh display
	// from frame buffer when semaphore displayRefreshRequestSemaphore has permits.
	multicore_reset_core1(); 	
	multicore_launch_core1(displayHandler);
	do // wait til core 1 is ready to accept refresh requests
	{
		_flagValue = multicore_fifo_pop_blocking();
	} while(_flagValue != MULTICORE_FLAG);		
	/////////////////////////////////////////////////////////////////////////////////


#ifndef NDEBUG
	mutex_enter_blocking(&frameBufferMutex);			// lock the frame buffer
	clear_frameBuffer(pDisplayParams,WHITE);
	for ( uint16_t __x = 0; __x < 32; __x++ )
	{
		for ( uint16_t __y = 0; __y < 64; __y++ ) draw_pixel(pDisplayParams, __x, __y, BLACK );
	}
	mutex_exit(&frameBufferMutex);						// free the frame buffer
	sem_release(&displayRefreshRequestSemaphore);		// request a refresh by core1
	sleep_ms(3000);										// 3 second pause... see if a rectangle appears
#endif

	// get the start time
	_start_time_us = get_absolute_time();
	_last_display_update_time = _start_time_us;

	watchdog_enable( 8000, true );							// 8 second watchdog  

	// now loop to service events as they occur
	while(true)
	{
		// get the elapsed time in uS, and calculate higher order units
		_current_time_us  = get_absolute_time();

		elapsedTime_us = absolute_time_diff_us ( _start_time_us, _current_time_us );
		if ( elapsedTime_us != 0 )
		{
			elapsedTime_ms = elapsedTime_us / 1000;
			elapsedTime_us = elapsedTime_us % 1000;
			elapsedTime_sec = elapsedTime_ms / 1000;
			elapsedTime_ms = elapsedTime_ms % 1000;
			elapsedTime_min = elapsedTime_sec / 60;
			elapsedTime_sec = elapsedTime_sec % 60;
			elapsedTime_hour = elapsedTime_min / 60;
			elapsedTime_min = elapsedTime_min % 60;
		}

		watchdog_update();							// keep the watchdog on-leash

#if defined(DEMO_MODE)
		if ( !_bInDemoMode )	
		{
			// start the demo after 10 seconds
			_deltaTime = absolute_time_diff_us ( _start_time_us, _current_time_us );
			if ( _deltaTime >= (int64_t)20000000LL )	// 20 seconds
			{
				add_repeating_timer_ms( _demoWheelRev_ms, timer_callback, NULL, &_wheelRevTimerID );	
				_lastWheelSpeedChange = _current_time_us;
				_bInDemoMode = true;
				_bDemoAccelerate = true;
			}
		}
		else
		{
			if (  ( _fSpeed != 0.0 ) )
			{
				_deltaTime = absolute_time_diff_us ( _start_time_us, _current_time_us );
				if( _deltaTime >= (int64_t)3600000000LL ) 	// 60 minutes
				{
					cancel_repeating_timer( &_wheelRevTimerID );
				}
				else 
				{
					_deltaTime = absolute_time_diff_us (  _lastWheelSpeedChange, _current_time_us);
					if ( _deltaTime > 5000000LL )			// every 5 seconds vary speed
					{
						if ( _fSpeed > 40.0 ) _bDemoAccelerate = false;
						else  if ( _fSpeed < 10.0 ) _bDemoAccelerate = true;
						_demoWheelRev_ms +=  _bDemoAccelerate ?  -10 : 25 ; 
						cancel_repeating_timer( &_wheelRevTimerID );
						add_repeating_timer_ms( _demoWheelRev_ms, timer_callback, NULL, &_wheelRevTimerID );	
						_lastWheelSpeedChange = _current_time_us;
					}
				}
			}
		}
#endif

		// see if a wheel revolution has completed
		if ( sem_try_acquire( &wheelEventSemaphore ) )
		{
#if defined(DEMO_MODE)
			gpio_put(WHEEL_REV_PIN,true);							// off = high
#endif
			if ( (!is_nil_time(wheelEvent.lastWheelRevTime)) && (!is_nil_time(wheelEvent.currentWheelRevTime)) )
			{
				_iWheelRevTime_us = absolute_time_diff_us ( wheelEvent.lastWheelRevTime, wheelEvent.currentWheelRevTime );
				_fWheel_mm_perSecond = ( _fWheelCircum_mm / _iWheelRevTime_us ) * 1000000.0f;

				fSpeedArray[iSpeedIndex] = _fWheel_mm_perSecond;			// store the last NUM_AVG_SPEED speeds
				if ( ++iSpeedIndex >= NUM_AVG_SPEED ) iSpeedIndex = 0;

				_fDistance_mm += _fWheelCircum_mm ;	
			}
		}
		else
		// how long has it been since last wheel rev detected?
		{
			if ( !is_nil_time(wheelEvent.lastWheelRevTime) )
			{
				_iWheelRevTime_us = absolute_time_diff_us ( wheelEvent.lastWheelRevTime, _current_time_us );
				if ( _iWheelRevTime_us > (int64_t)10000000LL )
				{
					memset ( &wheelEvent, 0, sizeof(WHEEL_EVENT) );
					for ( uint8_t __i=0; __i < NUM_AVG_SPEED; __i++ ) fSpeedArray[__i] = 0.0f;
					_displayWhat = DISPLAY_SUMMARY_SCREEN;
				}
			}
		}

		// see if time to update display
		if ( sem_try_acquire( &updateRequestSemaphore ) )
		{
			_fDistance_km = _fDistance_mm / 1000000.0f;				// convert mm to km

			// calculate the average speed over NUM_AVG_SPEED samples
			uint8_t		__i, __j;
			_fSpeed = 0.0f;
			for ( __i=0, __j=0; __i < NUM_AVG_SPEED; __i++ )
			{
				if ( fSpeedArray[__i] != 0.0f ) 
				{
					_fSpeed += fSpeedArray[__i];
					__j++;
				}
			}
			if ( __j != 0 ) 
			{
				_fSpeed = _fSpeed / __j;														// avg mm/s
				_fSpeed = ( _fWheel_mm_perSecond * 60.0f * 60.0f ) / ( 1000.0f * 1000.0f );		// km/h
			}

			// Display the screen(s)
			switch ( _displayWhat )
			{
			case DISPLAY_SPLASH_SCREEN:
				mutex_enter_blocking(&frameBufferMutex);			// lock the frame buffer
				clear_frameBuffer(pDisplayParams,WHITE);		
				pDisplayParams->pFontDesc = &font_8x16_desc;		// 32 x 64 font
				pDisplayParams->magn = 4;
				draw_string(pDisplayParams,(char *)strPico_bike, 0, 0, WHITE,BLACK);
				mutex_exit(&frameBufferMutex);						// free the frame buffer
				sem_release(&displayRefreshRequestSemaphore);		// request a refresh by core1
				sem_release(&displayRefreshRequestSemaphore);		// request another refresh by core1
				sem_release(&displayRefreshRequestSemaphore);		// request yet another refresh by core1

				// set alarm for what/when to display next
				if ( _alarmID != -1 ) cancel_alarm(_alarmID);
				_alarmID = add_alarm_in_ms( ( pDisplayParams->busyTime_ms > 5000)? pDisplayParams->busyTime_ms : 5000, alarm_callback, NULL, true );	// hold splash screen for 5 sec
				_displayWhat = DISPLAY_SUMMARY_SCREEN;
				_displayedElapsedTime_min = 99;
				break;

			case DISPLAY_SUMMARY_SCREEN:
				if ( ( (_fDistance_km - _fDisplayedDistance) >= 0.1f ) || ( _displayedElapsedTime_sec != elapsedTime_sec )	)	// do we need to update display now?
				{
					mutex_enter_blocking(&frameBufferMutex);		// lock the frame buffer
					clear_frameBuffer(pDisplayParams,WHITE);		
					pDisplayParams->pFontDesc = &font_7seg_24x48_desc;	// 24 x 48 font
					pDisplayParams->magn = 1;
					sprintf(strTime, "%02lld:%02lld:%02lld", elapsedTime_hour, elapsedTime_min, elapsedTime_sec );
					draw_string(pDisplayParams,strTime, 0, 0, WHITE,BLACK);
					sprintf(strDistance, "%-4.1f", _fDistance_km );
					draw_string(pDisplayParams,strDistance, 0, 64, WHITE,BLACK);
					pDisplayParams->pFontDesc = &font_8x16_desc;		// 16 x 32 font
					pDisplayParams->magn = 2;
					draw_string(pDisplayParams,(char *)strKm, (strlen(strDistance) * font_7seg_24x48_desc.Width) + 8 , 64 + font_7seg_24x48_desc.Height - font_8x16_desc.Height - 16, WHITE,BLACK);
					mutex_exit(&frameBufferMutex);						// free the frame buffer
					sem_release(&displayRefreshRequestSemaphore);		// request a refresh by core1
					_displayedElapsedTime_sec = elapsedTime_sec;
					_fDisplayedDistance = _fDistance_km;
				}

				// set alarm for what/when to display next
				if ( _alarmID != -1 ) cancel_alarm(_alarmID);
				_alarmID = add_alarm_in_ms( ( pDisplayParams->busyTime_ms > 1000)? pDisplayParams->busyTime_ms : 1000, alarm_callback, NULL, true );  // update in 1 second

				// if bike stopped, then keep displaying SUMMARY screen. otherwise go to automatic changing display, hands-free!!!!!
				if ( _fSpeed >= 0.5f ) 
				{
					_displayWhat = DISPLAY_CURRENT_SPEED;
					_fDisplayedSpeed = 99.99;
					_last_display_update_time = _current_time_us;
				}
				break;

			case DISPLAY_CURRENT_SPEED:
				//if ( round(_fDisplayedSpeed) != round(_fSpeed) )		// has speed changed?
				//{
					mutex_enter_blocking(&frameBufferMutex);			// lock the frame buffer
					clear_frameBuffer(pDisplayParams,WHITE);		
					pDisplayParams->pFontDesc = &font_7seg_24x48_desc;	// 48 x 96 font
					pDisplayParams->magn = 2;
					sprintf(strSpeed, "%5.0f", round(_fSpeed) );
					draw_string(pDisplayParams,strSpeed, 0, 0,WHITE,BLACK);	// display the value
					pDisplayParams->pFontDesc = &font_8x16_desc;		// 16 x 32 font
					pDisplayParams->magn = 2;
					draw_string(pDisplayParams,(char *)strKph,160,96,WHITE,BLACK);	// display the units
					mutex_exit(&frameBufferMutex);						// free the frame buffer
					sem_release(&displayRefreshRequestSemaphore);		// request a refresh by core1
					_fDisplayedSpeed = _fSpeed;							// update last displayed speed
				//}

				// set alarm for what/when to display next
				if ( _alarmID != -1 ) cancel_alarm(_alarmID);
				_alarmID = add_alarm_in_ms( ( pDisplayParams->busyTime_ms > 1000)? pDisplayParams->busyTime_ms : 1000, alarm_callback, NULL, true );  // update in 1 second

				// if not moving, go back to summary screen
				if ( _fSpeed  < 0.5f )
				{
					_displayWhat =  DISPLAY_SUMMARY_SCREEN;
				}
				else
				{
					// how long has this display been active ?
					_deltaTime = absolute_time_diff_us ( _last_display_update_time, _current_time_us );
					if ( _deltaTime >= (int64_t)30000000LL )	 // hold speed display for 30 seconds
					{
						// new display next time
						_displayWhat = DISPLAY_TOTAL_DISTANCE_SCREEN;
						_fDisplayedDistance = 9999.99;					// force a display 1st time
						_last_display_update_time = _current_time_us;
					}
				}
				break;

			case DISPLAY_TOTAL_DISTANCE_SCREEN:		// display total distance
				//if (  fabs( _fDistance_km - _fDisplayedDistance ) >= .1 )
				//{
					mutex_enter_blocking(&frameBufferMutex);					// lock the frame buffer
					clear_frameBuffer(pDisplayParams,WHITE);		
					pDisplayParams->pFontDesc = &font_7seg_24x48_desc;			// 48 x 96 font
					pDisplayParams->magn = 2;
					sprintf(strDistance, "%5.1f", _fDistance_km );
					draw_string(pDisplayParams,strDistance, 0, 0,WHITE,BLACK);	// display the value
					pDisplayParams->pFontDesc = &font_8x16_desc;				// 16 x 32 font
					pDisplayParams->magn = 2;
					draw_string(pDisplayParams,(char *)strKm,160,96,WHITE,BLACK);	// display the units
					mutex_exit(&frameBufferMutex);								// free the frame buffer
					sem_release(&displayRefreshRequestSemaphore);				// request a refresh by core1
					sem_release(&displayRefreshRequestSemaphore);				// request another refresh by core1
					_fDisplayedDistance = _fDistance_km;						// update last displayed distance
				//}

				// set alarm for what/when to display next
				if ( _alarmID != -1 ) cancel_alarm(_alarmID);
				_alarmID = add_alarm_in_ms ( (pDisplayParams->busyTime_ms > 2000)? pDisplayParams->busyTime_ms : 2000, alarm_callback, NULL, true );  // update in 2 seconds

				_deltaTime = absolute_time_diff_us ( _last_display_update_time, _current_time_us );
				if ( _deltaTime >= (int64_t)30000000LL)							// has this been displayed for 30 seconds?
				{
					_displayWhat = DISPLAY_ELAPSED_TIME_SCREEN;
					_displayedElapsedTime_min = 0xff;	// force a display 1st time
					_last_display_update_time = _current_time_us;
				}
				break;

			case DISPLAY_ELAPSED_TIME_SCREEN:							// display elapsed time
				//if (  _displayedElapsedTime_min != elapsedTime_min )	// do we need to update display now?
				//{
					mutex_enter_blocking(&frameBufferMutex);			// lock the frame buffer
					clear_frameBuffer(pDisplayParams,WHITE);		
					pDisplayParams->pFontDesc = &font_7seg_24x48_desc;	// 48 x 96 font
					pDisplayParams->magn = 2;
					sprintf(strTime, "%02lld:%02lld", elapsedTime_hour, elapsedTime_min );
					draw_string(pDisplayParams,strTime, 0, 0, WHITE,BLACK);
					mutex_exit(&frameBufferMutex);						// free the frame buffer
					sem_release(&displayRefreshRequestSemaphore);		// request a refresh by core1
					sem_release(&displayRefreshRequestSemaphore);		// request another refresh by core1
					_displayedElapsedTime_min = elapsedTime_min;
				//}
				// set alarm for what/when to display next
				if ( _alarmID != -1 ) cancel_alarm(_alarmID);
				_alarmID = add_alarm_in_ms(   (pDisplayParams->busyTime_ms > 5000)? pDisplayParams->busyTime_ms : 5000, alarm_callback, NULL, true );  // update in 5 seconds
				_deltaTime = absolute_time_diff_us ( _last_display_update_time, _current_time_us );
				if ( _deltaTime >= (int64_t)15000000LL )				// has this been displayed for 15 seconds?
				{
					_displayWhat = DISPLAY_CURRENT_SPEED;
					_last_display_update_time = _current_time_us;
					_fDisplayedSpeed = 99.99;
				}
				break;
			}
		}
	}
}

/********************************************************
*********************************************************

	Display (refresh) handler   ....run by core 1

*********************************************************
*********************************************************/

static void displayHandler(void)
{	
	// initialize the physical display
	pDisplayParams->initDisplay( );

	multicore_fifo_push_blocking(MULTICORE_FLAG);

	while ( true )
	{
		sem_acquire_blocking(&displayRefreshRequestSemaphore);	// wait for a refresh permit
		mutex_enter_blocking(&frameBufferMutex);		// lock the frame buffer
		pDisplayParams->refreshDisplay( );				// refresh the display 
		mutex_exit(&frameBufferMutex);					// free the frame buffer
		
		pDisplayParams->busyWaitDisplay( );				// wait till not busy before next refresh... with slower LUT speeds, this may take a while
	}		

}


/********************************************************
*********************************************************

	Utility functions


*********************************************************
*********************************************************/

///////////////////////////////////
// callback from alarm timer
///////////////////////////////////
static int64_t alarm_callback(alarm_id_t id, void *user_data)
{
	sem_release (&updateRequestSemaphore);
}

#if defined(DEMO_MODE)
///////////////////////////////////
// callback from repeating timer
///////////////////////////////////
static bool timer_callback(repeating_timer_t *rt)
{
	wheelEvent.lastWheelRevTime = wheelEvent.currentWheelRevTime;
	wheelEvent.currentWheelRevTime = get_absolute_time();
	gpio_put(WHEEL_REV_PIN,false);							// on = low
	sem_release (&wheelEventSemaphore);
}
#endif


///////////////////////////////////
// callback from GPIO interrupts
///////////////////////////////////

static void __no_inline_not_in_flash_func(gpioIrqCallback)(void)
{
	if ( (gpio_get_irq_event_mask( WHEEL_REV_PIN ))  & GPIO_IRQ_EDGE_FALL ) 
	{
        gpio_acknowledge_irq( WHEEL_REV_PIN, GPIO_IRQ_EDGE_FALL);
		wheelEvent.lastWheelRevTime = wheelEvent.currentWheelRevTime;
		wheelEvent.currentWheelRevTime = get_absolute_time();
		sem_release (&wheelEventSemaphore);
	}
	else gpio_acknowledge_irq( WHEEL_REV_PIN, ~GPIO_IRQ_EDGE_FALL );
}

///////////////////
// wait for reboot
//////////////////

void __no_inline_not_in_flash_func(wait_for_reboot)(void)
{
	__asm volatile ( " cpsid i " );

	while(true) tight_loop_contents();	// reboot should happen here when watchdog times out, or USB boots
}


/////////////////////////////////////
// Reboot to USB Mass Storage Device
/////////////////////////////////////
void reboot_to_usb(void)
{
	multicore_reset_core1();
	multicore_launch_core1(wait_for_reboot);
	reset_usb_boot(0,0);
	wait_for_reboot();
}


