/********************************************************/
/*														*/
/* pico-bike:											*/
/*    Display current speed, distance travelled, and	*/
/*			elapsed time on e-paper display				*/
/*														*/
/********************************************************/

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
static semaphore_t		displayRefreshRequest;				// semaphore to request frame refresh
static semaphore_t		updateRequest;						// semaphore to trigger re-calculation of spped/distance
static semaphore_t		wheelEvent;							// an event semaphore for every time the wheel does a revolution

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
						_fDistance = 0,
						_fDisplayedSpeed = 99.99,
						_fDisplayedDistance = 999.99;

	uint8_t				_displayedElapsedTime_min = 99;

	absolute_time_t		_lastWheelRevTime;		// last time wheel revolution
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
	bool				_bDemoMode = false;
#endif

	// Initialize the GPIO pins //
	gpio_init(PICO_LED_PIN);						// define LED pin
	gpio_set_dir(PICO_LED_PIN,true);				// output
	gpio_put(PICO_LED_PIN,false);					// off

	// create synchronization objects for core1 interaction & local use
	mutex_init( &frameBufferMutex );				// create a mutex to lock frame buffer
	sem_init( &displayRefreshRequest, 0, 4 );		// counting semaphore to request frame refresh by coore 1
	sem_init( &updateRequest, 1, 1 );				// binary semaphore to request update screen, give 1 permit to start
	sem_init( &wheelEvent, 0, 1 );					// binary semaphore to indicate 1 wheel revolution

	// inititialize alarm pool 
	alarm_pool_init_default();

	// start core 1 as the display refresh handler, it will refresh display
	// from frame buffer when semaphore displayRefreshRequest has permits.
	multicore_reset_core1();
	multicore_launch_core1(displayHandler);

	// get the start time
	_start_time_us = get_absolute_time();
	_last_display_update_time = _start_time_us;

	// set the wheel circumference mm
	_fWheelCircum_mm = 700.0f;

	// now loop to service events
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

#if defined(DEMO_MODE)
		if ( !_bDemoMode )	
		{
			// start the demo after 10 seconds
			_deltaTime = absolute_time_diff_us ( _start_time_us, _current_time_us );
			if ( _deltaTime > (int64_t)(10*1000*1000) )
			{
				add_repeating_timer_ms( 125, timer_callback, NULL, &_wheelRevTimerID );
				_lastWheelRevTime = _current_time_us;
				_bDemoMode = true;
			}
		}
#endif

		// see if a wheel revolution has completed
		if ( sem_try_acquire( &wheelEvent ) )
		{
			_iWheelRevTime_us = absolute_time_diff_us ( _lastWheelRevTime, _current_time_us );
			_fWheel_mm_perSecond = (_fWheelCircum_mm / _iWheelRevTime_us ) * 1000000.0f;
			_fSpeed = ( _fWheel_mm_perSecond * ( 60.0f * 60.0f )) / ( 1000.0f * 1000.0f );		// km/h
			_fDistance += ( _fWheelCircum_mm / 1000.0f ) / 1000.0f;	// translate mm to Km
			_lastWheelRevTime = _current_time_us;
		}

		// see if event to update display
		if ( sem_try_acquire( &updateRequest ) )
		{
			_bNeedRefresh = false;		// assume we won't need to refresh

			// Display the screen
			switch ( _displayWhat )
			{
			case DISPLAY_SPLASH_SCREEN:
				mutex_enter_blocking(&frameBufferMutex);			// lock the frame buffer
				clear_frameBuffer(pDisplayParams,WHITE);		
				pDisplayParams->pFontDesc = &font_8x16_desc;		// 32 x 64 font
				pDisplayParams->magn = 4;
				draw_string(pDisplayParams,(char *)strPico_bike, 0, 0, WHITE,BLACK);
				mutex_exit(&frameBufferMutex);						// free the frame buffer
				sem_release(&displayRefreshRequest);				// request a refresh by core1
				// set alarm for what/when to display next
				if ( _alarmID != -1 ) cancel_alarm(_alarmID);
				_alarmID = add_alarm_in_ms( 5000, alarm_callback, NULL, true );
				_displayWhat = DISPLAY_SUMMARY_SCREEN;
				break;

			case DISPLAY_SUMMARY_SCREEN:
				if ( ( (_fDistance - _fDisplayedDistance) > 0.1f ) || ( _displayedElapsedTime_min != _elapsedTime_min )	)	// do we need to update display now?
				{
					mutex_enter_blocking(&frameBufferMutex);		// lock the frame buffer
					clear_frameBuffer(pDisplayParams,WHITE);		
					pDisplayParams->pFontDesc = &font_8x16_desc;	// 32 x 64 font
					pDisplayParams->magn = 4;
					sprintf(strTime, "%02lld:%02lld", _elapsedTime_hour, _elapsedTime_min );
					draw_string(pDisplayParams,strTime, 0, 0, WHITE,BLACK);
					sprintf(strDistance, "%-4.1f%s", _fDistance, strKm );
					draw_string(pDisplayParams,strDistance, 0, 64, WHITE,BLACK);
					mutex_exit(&frameBufferMutex);					// free the frame buffer
					sem_release(&displayRefreshRequest);			// request a refresh by core1
					_displayedElapsedTime_min = _elapsedTime_min;
					_fDisplayedDistance = _fDistance;
				}
				// set alarm for what/when to display next
				if ( _alarmID != -1 ) cancel_alarm(_alarmID);
				_alarmID = add_alarm_in_ms( 2000, alarm_callback, NULL, true );  // update in 2 seconds
				if ( _fSpeed < 1 ) _displayWhat = DISPLAY_SUMMARY_SCREEN;
				else 
				{
					_displayWhat = DISPLAY_CURRENT_SPEED;
					_fDisplayedSpeed = 99.99;
					_last_display_update_time = _current_time_us;
				}
				break;

			case DISPLAY_CURRENT_SPEED:
				if ( round(_fDisplayedSpeed) != round(_fSpeed) )
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
					sem_release(&displayRefreshRequest);				// request a refresh by core1
					_fDisplayedSpeed = _fSpeed;							// update last displayed speed
				}
				// set alarm for what/when to display next
				if ( _alarmID != -1 ) cancel_alarm(_alarmID);
				_alarmID = add_alarm_in_ms( 2000UL, alarm_callback, NULL, true );  // update in 2 seconds
				_deltaTime = absolute_time_diff_us ( _last_display_update_time, _current_time_us );
				if ( _deltaTime < (int64_t)(30*1000*1000) )	 _displayWhat = DISPLAY_CURRENT_SPEED;		// has this been displayed for 30 seconds?
				else 
				{
					_displayWhat = DISPLAY_TOTAL_DISTANCE_SCREEN;
					_fDisplayedDistance = 9999.99;					// force a display 1st time
					_last_display_update_time = _current_time_us;
				}
				break;

			case DISPLAY_TOTAL_DISTANCE_SCREEN:		// display total distance
				if (  fabs( _fDistance - _fDisplayedDistance ) >= .1 )
				{
					mutex_enter_blocking(&frameBufferMutex);			// lock the frame buffer
					clear_frameBuffer(pDisplayParams,WHITE);		
					pDisplayParams->pFontDesc = &font_7seg_24x48_desc;	// 48 x 96 font
					pDisplayParams->magn = 2;
					sprintf(strDistance, "%5.1f", _fDistance );
					draw_string(pDisplayParams,strDistance, 0, 0,WHITE,BLACK);	// display the value
					pDisplayParams->pFontDesc = &font_8x16_desc;		// 16 x 32 font
					pDisplayParams->magn = 2;
					draw_string(pDisplayParams,(char *)strKm,160,96,WHITE,BLACK);	// display the units
					mutex_exit(&frameBufferMutex);						// free the frame buffer
					sem_release(&displayRefreshRequest);				// request a refresh by core1
					_fDisplayedDistance = _fDistance;					// update last displayed distance
				}
				// set alarm for what/when to display next
				if ( _alarmID != -1 ) cancel_alarm(_alarmID);
				_alarmID = add_alarm_in_ms( 2000UL, alarm_callback, NULL, true );  // update in 2 seconds
				_deltaTime = absolute_time_diff_us ( _last_display_update_time, _current_time_us );
				if ( _deltaTime < (int64_t)(10*1000*1000) )	 _displayWhat = DISPLAY_TOTAL_DISTANCE_SCREEN;		// has this been displayed for 10 seconds?
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
					sem_release(&displayRefreshRequest);				// request a refresh by core1
					_displayedElapsedTime_min = _elapsedTime_min;
				}
				// set alarm for what/when to display next
				if ( _alarmID != -1 ) cancel_alarm(_alarmID);
				_alarmID = add_alarm_in_ms( 2000UL, alarm_callback, NULL, true );  // update in 2 seconds
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
		sem_acquire_blocking(&displayRefreshRequest);	// wait for a refresh permit

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
	sem_release (&updateRequest);
}

#if defined(DEMO_MODE)
///////////////////////////////////
// callback from repeating timer
///////////////////////////////////
static bool timer_callback(repeating_timer_t *rt)
{
	sem_release (&wheelEvent);
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


