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

typedef struct
{
	absolute_time_t		lastWheelRevTime;		// last time wheel revolution
	absolute_time_t		currentWheelRevTime;	// this time wheel revolution
}WHEEL_EVENT;

/////////////////////
// Local variables
/////////////////////

static char				strSpeed[8];						// strings for the speed, distance & time
static char				strDistance[8];
static char				strTime[8];

	
static const char		strPico_bike[] =	"pico-bike";	// labels
static const char		strKm[] =			"km";						
static const char		strKph[] =			"km/h";

static mutex_t			frameBufferMutex;					// mutex to lock frame buffer
static semaphore_t		displayRefreshRequestSemaphore;			// semaphore to request frame refresh
static semaphore_t		updateRequestSemaphore;						// semaphore to trigger re-calculation of spped/distance

static semaphore_t		wheelEventSemaphore;							// an event semaphore for every time the wheel does a revolution
static WHEEL_EVENT		wheelEvent;

// this selects the display we will use
static DISPLAY_PARAMS	*pDisplayParams = &UC8151DDisplayParams;

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

	uint8_t				_displayedElapsedTime_min = 99;

	uint64_t			_iWheelRevTime_us;		// how long the wheel took for 1 rev
	double				_fWheelCircum_mm,		// circumference of wheel in mm
						_fWheel_mm_perSecond;	// calculated mm/sec speed

	absolute_time_t		_start_time_us,
						_current_time_us,
						_last_display_update_time;

	int64_t				_elapsedTime_us,
						_elapsedTime_ms,
						_elapsedTime_sec,
						_elapsedTime_min,
						_elapsedTime_hour;

	int64_t				_deltaTime;


	uint8_t				_displayWhat = DISPLAY_SPLASH_SCREEN;
	bool				_bNeedRefresh;

	uint8_t				*_pstrValue,
						*_pstrUnits;

	FONT_DESC			*_pFontDesc = pDisplayParams->pFontDesc;

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
	gpio_set_dir(PICO_LED_PIN,false);						// input
	gpio_pull-up(PICO_LED_PIN,true);						// pulled up
#endif

	// create synchronization objects for core1 interaction & local use
	mutex_init( &frameBufferMutex );				// create a mutex to lock frame buffer
	sem_init( &displayRefreshRequestSemaphore, 0, 4 );		// counting semaphore to request frame refresh by coore 1
	sem_init( &updateRequestSemaphore, 1, 1 );				// binary semaphore to request update screen, give 1 permit to start
	sem_init( &wheelEventSemaphore, 0, 1 );					// binary semaphore to indicate 1 wheel revolution

	// inititialize alarm pool 
	alarm_pool_init_default();

	// start core 1 as the display refresh handler, it will refresh display
	// from frame buffer when semaphore displayRefreshRequestSemaphore has permits.
	multicore_reset_core1();
	multicore_launch_core1(displayHandler);

	// get the start time
	_start_time_us = get_absolute_time();
	_last_display_update_time = _start_time_us;

	watchdog_enable( 2000, true );						// 2 second watchdog  

	// set the wheel circumference in mm
#if defined (WHEEL_CIRCUMFERENCE_MM)
	_fWheelCircum_mm = WHEEL_CIRCUMFERENCE_MM;
#else
	_fWheelCircum_mm = 700.0f;
#endif

	// now loop to service events as they occur
	while(true)
	{
		// get the elapsed time in uS, and calculate higher order units
		_current_time_us  = get_absolute_time();

		_elapsedTime_us = absolute_time_diff_us ( _start_time_us, _current_time_us );
		_elapsedTime_ms = _elapsedTime_us / 1000;
		_elapsedTime_us = _elapsedTime_us % 1000;
		_elapsedTime_sec = _elapsedTime_ms / 1000;
		_elapsedTime_ms = _elapsedTime_ms % 1000;
		_elapsedTime_min = _elapsedTime_sec / 60;
		_elapsedTime_sec = _elapsedTime_sec % 60;
		_elapsedTime_hour = _elapsedTime_min / 60;
		_elapsedTime_min = _elapsedTime_min % 60;

		watchdog_update();

#if defined(DEMO_MODE)
		if ( !_bInDemoMode )	
		{
			// start the demo after 10 seconds
			_deltaTime = absolute_time_diff_us ( _start_time_us, _current_time_us );
			if ( _deltaTime >= (int64_t)10000000LL )	// 10 seconds
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
					_fSpeed = 0.0;
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
						sem_reset ( &wheelEventSemaphore, 0 );
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
				_fWheel_mm_perSecond = (_fWheelCircum_mm / _iWheelRevTime_us ) * 1000000.0f;
				_fSpeed = ( _fWheel_mm_perSecond * 60.0f * 60.0f ) / ( 1000.0f * 1000.0f );		// km/h

				_fDistance_mm += _fWheelCircum_mm ;	
			}
		}

		// see if time to update display
		if ( sem_try_acquire( &updateRequestSemaphore ) )
		{
			_fDistance_km = _fDistance_mm / 1000000.0f;				// convert to viewable units

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
				sem_release(&displayRefreshRequestSemaphore);				// request a refresh by core1

				// set alarm for what/when to display next
				if ( _alarmID != -1 ) cancel_alarm(_alarmID);
				_alarmID = add_alarm_in_ms( 5000, alarm_callback, NULL, true );	// hold splash screen for 5 sec
				_displayWhat = DISPLAY_SUMMARY_SCREEN;
				_displayedElapsedTime_min = 99;
				break;

			case DISPLAY_SUMMARY_SCREEN:
				if ( ( (_fDistance_km - _fDisplayedDistance) >= 0.1f ) || ( _displayedElapsedTime_min != _elapsedTime_min )	)	// do we need to update display now?
				{
					mutex_enter_blocking(&frameBufferMutex);		// lock the frame buffer
					clear_frameBuffer(pDisplayParams,WHITE);		
					pDisplayParams->pFontDesc = &font_8x16_desc;	// 32 x 64 font
					pDisplayParams->magn = 4;
					sprintf(strTime, "%02lld:%02lld", _elapsedTime_hour, _elapsedTime_min );
					draw_string(pDisplayParams,strTime, 0, 0, WHITE,BLACK);
					sprintf(strDistance, "%-4.1f%s", _fDistance_km, strKm );
					draw_string(pDisplayParams,strDistance, 0, 64, WHITE,BLACK);
					mutex_exit(&frameBufferMutex);					// free the frame buffer
					sem_release(&displayRefreshRequestSemaphore);			// request a refresh by core1
					_displayedElapsedTime_min = _elapsedTime_min;
					_fDisplayedDistance = _fDistance_km;
				}

				// set alarm for what/when to display next
				if ( _alarmID != -1 ) cancel_alarm(_alarmID);
				_alarmID = add_alarm_in_ms( 1000, alarm_callback, NULL, true );  // update in 1 second

				// if stopped, then keep displaying SUMMARY screen. otherwise go to automatic changing display, hands-free!!!!!
				if ( _fSpeed >= 0.5f ) 
				{
					_displayWhat = DISPLAY_CURRENT_SPEED;
					_fDisplayedSpeed = 99.99;
					_last_display_update_time = _current_time_us;
				}
				break;

			case DISPLAY_CURRENT_SPEED:
				if ( round(_fDisplayedSpeed) != round(_fSpeed) )		// has speed changed?
				{
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
					sem_release(&displayRefreshRequestSemaphore);				// request a refresh by core1
					_fDisplayedSpeed = _fSpeed;							// update last displayed speed
				}

				// set alarm for what/when to display next
				if ( _alarmID != -1 ) cancel_alarm(_alarmID);
				_alarmID = add_alarm_in_ms( 1000, alarm_callback, NULL, true );  // update in 1 second

				// if not moving, go back to summary screen
				if ( _fSpeed  < 0.5f )
				{
					_displayWhat =  DISPLAY_SUMMARY_SCREEN;
				}
				else
				{
					// how long has this display been active ?
					_deltaTime = absolute_time_diff_us ( _last_display_update_time, _current_time_us );
					if ( _deltaTime < (int64_t)30000000LL )	 _displayWhat = DISPLAY_CURRENT_SPEED;		// hold speed display for 30 seconds
					else 
					{
						// new display next time
						_displayWhat = DISPLAY_TOTAL_DISTANCE_SCREEN;
						_fDisplayedDistance = 9999.99;					// force a display 1st time
						_last_display_update_time = _current_time_us;
					}
				}
				break;

			case DISPLAY_TOTAL_DISTANCE_SCREEN:		// display total distance
				if (  fabs( _fDistance_km - _fDisplayedDistance ) >= .1 )
				{
					mutex_enter_blocking(&frameBufferMutex);			// lock the frame buffer
					clear_frameBuffer(pDisplayParams,WHITE);		
					pDisplayParams->pFontDesc = &font_7seg_24x48_desc;	// 48 x 96 font
					pDisplayParams->magn = 2;
					sprintf(strDistance, "%5.1f", _fDistance_km );
					draw_string(pDisplayParams,strDistance, 0, 0,WHITE,BLACK);	// display the value
					pDisplayParams->pFontDesc = &font_8x16_desc;		// 16 x 32 font
					pDisplayParams->magn = 2;
					draw_string(pDisplayParams,(char *)strKm,160,96,WHITE,BLACK);	// display the units
					mutex_exit(&frameBufferMutex);						// free the frame buffer
					sem_release(&displayRefreshRequestSemaphore);				// request a refresh by core1
					_fDisplayedDistance = _fDistance_km;					// update last displayed distance
				}

				// set alarm for what/when to display next
				if ( _alarmID != -1 ) cancel_alarm(_alarmID);
				_alarmID = add_alarm_in_ms( 2000, alarm_callback, NULL, true );  // update in 2 seconds

				_deltaTime = absolute_time_diff_us ( _last_display_update_time, _current_time_us );
				if ( _deltaTime < (int64_t)(5*1000*1000) )	 _displayWhat = DISPLAY_TOTAL_DISTANCE_SCREEN;		// has this been displayed for 5 seconds?
				else 
				{
					_displayWhat = DISPLAY_ELAPSED_TIME_SCREEN;
					_displayedElapsedTime_min = 0xff;	// force a display 1st time
					_last_display_update_time = _current_time_us;
				}
				break;

			case DISPLAY_ELAPSED_TIME_SCREEN:							// display elapsed time
				if (  _displayedElapsedTime_min != _elapsedTime_min )	// do we need to update display now?
				{
					mutex_enter_blocking(&frameBufferMutex);			// lock the frame buffer
					clear_frameBuffer(pDisplayParams,WHITE);		
					pDisplayParams->pFontDesc = &font_7seg_24x48_desc;	// 48 x 96 font
					pDisplayParams->magn = 2;
					sprintf(strTime, "%02lld:%02lld", _elapsedTime_hour, _elapsedTime_min );
					draw_string(pDisplayParams,strTime, 0, 0, WHITE,BLACK);
					mutex_exit(&frameBufferMutex);						// free the frame buffer
					sem_release(&displayRefreshRequestSemaphore);				// request a refresh by core1
					_displayedElapsedTime_min = _elapsedTime_min;
				}
				// set alarm for what/when to display next
				if ( _alarmID != -1 ) cancel_alarm(_alarmID);
				_alarmID = add_alarm_in_ms( 2000, alarm_callback, NULL, true );  // update in 2 seconds
				_deltaTime = absolute_time_diff_us ( _last_display_update_time, _current_time_us );
				if ( _deltaTime < (int64_t)(10*1000*1000) )	 _displayWhat = DISPLAY_ELAPSED_TIME_SCREEN;		// has this been displayed for 10 seconds?
				else 
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
	// initialize the display 
	pDisplayParams->initDisplay( UC8151D_SPI_CHANNEL );

	while ( true )
	{
		sem_acquire_blocking(&displayRefreshRequestSemaphore);	// wait for a refresh permit

		mutex_enter_blocking(&frameBufferMutex);		// lock the frame buffer
		pDisplayParams->refreshDisplay( UC8151D_SPI_CHANNEL );			// refresh the display 
		mutex_exit(&frameBufferMutex);					// free the frame buffer
		
		pDisplayParams->busyWaitDisplay( UC8151D_SPI_CHANNEL );		// wait till not busy before next refresh... with slower LUT speeds, this may take a while
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

void gpioIrqCallback(uint _gpioNum, uint32_t _events)
{
	gpio_acknowledge_irq(_gpioNum,_events);
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


