
#include "pico_bike.h"


/////////////////////
// Local defines
/////////////////////

#define UPDATE_INTERVAL_MS	2000		// 2 second update

/////////////////////
// Local variables
/////////////////////

static uint8_t			strSpeed[8];
static uint8_t			strDistance[8];
static uint8_t			strTime[8];

static const uint8_t	strKm[] = "km";
static const uint8_t	strKph[] = "km/h";

static mutex_t			frameBufferMutex;			// mutex to lock frame buffer
static semaphore_t		displayRefreshRequest;		// semaphore to request frame refresh
static semaphore_t		updateRequest;				// semaphore to trigger re-calculation of spped/distance

static DISPLAY_PARAMS	*pDisplayParams = &UC8151DDisplayParams;

/////////////////////
// Global variables
/////////////////////

/////////////////////
// Local functions
/////////////////////

static void displayHandler(void);
static bool alarm_timer_callback(repeating_timer_t *rt);

/********************************************************

	Main entry


*********************************************************/


int main()
{
	double				_fSpeed = 0,
						_fDistance = 0,
						_fDisplayedSpeed = 99.99,
						_fDisplayedDistance = 999.99;

	absolute_time_t		_start_time_us,
						_current_time_us;
	int64_t				_elapsedTime_us,
						_elapsedTime_ms,
						_elapsedTime_sec,
						_elapsedTime_min,
						_elapsedTime_hour;

	uint8_t				_displayWhat = 0;

	uint8_t				*_pstrValue,
						*_pstrUnits;

	FONT_DESC			*_pFontDesc = pDisplayParams->pFontDesc;

	repeating_timer_t	updateTimer;

	// Initialize the GPIO pins //
	gpio_init(PICO_LED_PIN);						// define LED pin
	gpio_set_dir(PICO_LED_PIN,true);				// output
	gpio_put(PICO_LED_PIN,false);					// off

	// create synchronization objects for core1 interaction
	mutex_init( &frameBufferMutex );				// create a mutex to lock frame buffer
	sem_init( &displayRefreshRequest, 0, 8 );		// counting semaphore to request frame refreshes

	// inititialize alarm pool for an update timer
	sem_init( &updateRequest, 0, 1 );				// binary semaphore to request update
	alarm_pool_init_default();
	add_repeating_timer_ms( UPDATE_INTERVAL_MS, alarm_timer_callback, NULL, &updateTimer );

	// start core 1 as the display refresh handler, it will refresh display
	// from frame buffer when semaphore displayRefreshRequest has permits.
	multicore_reset_core1();
	multicore_launch_core1(displayHandler);

	// get the start time
	_start_time_us = get_absolute_time();

	while(true)
	{
		// see if time to update metrics
		if ( sem_try_acquire( &updateRequest ) )
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

			// cyclically change what's displayed, give speed a longer time
			switch ( _displayWhat )
			{
			case 0:		// display elapsed time
				sprintf((char *)strTime, "%02lld:%02lld", _elapsedTime_hour, _elapsedTime_min );
				_pstrValue = strTime;
				_pstrUnits = NULL;
				break;
			case 1:		// display total distance
				_fDisplayedDistance = 9999.99;
			case 2:		// gets a double time
				if (  round(_fDisplayedDistance) == round(_fDistance) )
				{
					_pstrValue = NULL;
				}
				else
				{
					sprintf((char *)strDistance, "%5.1f", _fDistance );
					_pstrValue = strDistance;
					_pstrUnits = (uint8_t *)strKm;
					_fDisplayedDistance = _fDistance; // update last displayed distance
				}
				break;
			case 3:
				_fDisplayedSpeed = 99.9f;		// 1st time passed, fall through & force display of speed
			default:	// display current  average speed
				if ( round(_fDisplayedSpeed) == round(_fSpeed) )
				{
					_pstrValue = NULL;
				}
				else
				{
					sprintf((char *)strSpeed, "%5.0f", round(_fSpeed) );
					_pstrValue = strSpeed;
					_pstrUnits = (uint8_t *)strKph;
					_fDisplayedSpeed = _fSpeed;		// update last displayed speed
				}
				break;
			}
	
			// bump to next item to display, wrap @ 8
			if ( ++_displayWhat > 8 ) _displayWhat = 0;

			/////////////////////////////////////////////////////////////
			// test only... make up some numbers for next iteration
			/////////////////////////////////////////////////////////////
			if ( _fSpeed < 60.0f ) _fSpeed +=  0.25f;
			_fDistance +=  0.005f;
			/////////////////////////////////////////////////////////////

			if ( _pstrValue != NULL ) 						// need to display ?
			{
				// create the new image & request refresh
				mutex_enter_blocking(&frameBufferMutex);		// lock the frame buffer
				clear_frameBuffer(pDisplayParams,WHITE);		
				pDisplayParams->pFontDesc = &font_8x16_desc;	// 48 x 96 font
				pDisplayParams->magn = 6;
				draw_string(pDisplayParams,_pstrValue,0,0,WHITE,BLACK);	// display the value
				if(_pstrUnits != NULL)
				{
					pDisplayParams->pFontDesc = &font_8x16_desc; // 16 x 32 font
					pDisplayParams->magn = 2;
					draw_string(pDisplayParams,_pstrUnits,160,96,WHITE,BLACK);	// display the units
				}
				sem_release(&displayRefreshRequest);			// request a refresh by core1
				mutex_exit(&frameBufferMutex);					// free the frame buffer
				sleep_ms(5);									// give core 1 a chance to take f.b. mutex
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
// callback from repeating timer
///////////////////////////////////
static bool alarm_timer_callback(repeating_timer_t *rt)
{
	sem_release (&updateRequest);
}


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


