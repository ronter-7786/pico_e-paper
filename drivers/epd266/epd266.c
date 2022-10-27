
/********************************************************************
*
*   Driver for  UC8151D e-paper Controller
*
*
***********************************************************************/

#include "epd266.h"

/************************/
/*	Local Variables		*/
/************************/

#if LUT_SPEED_EPD266 != 0
const uint8_t LUT[159] = {
0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x40,0x40,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x0A,0x00,0x00,0x00,0x00,0x00,0x02,0x01,0x00,0x00,
0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x22,0x22,0x22,0x22,0x22,0x22,
0x00,0x00,0x00,0x22,0x17,0x41,0xB0,0x32,0x36,
};

const uint8_t LUT2[10] = { 0, 0, 0, 0, 0, 0x40, 0, 0, 0, 0 };


#endif

static const EPD266_CMD	epd266CommandInitSequence[] =
					{
						{.EPD266Cmd_code_data = EPD266CMD, .EPD266Cmd_delay = 0, .EPD266BusyWait = true, .EPD266HoldCS = false, .EPD266Args = 0, .EPD266Cmd_value = EPD266_CMD_RST },
#if LUT_SPEED_EPD266 != 0
						{.EPD266Cmd_code_data = EPD266CMD, .EPD266Cmd_delay = 0, .EPD266BusyWait = false, .EPD266HoldCS = false, .EPD266Args = 1, .EPD266Cmd_value = EPD266_CMD_LUT },
							{.EPD266Cmd_code_data = EPD266ARRAY, .EPD266Array= (uint8_t *)&LUT[0], .EPD266Args = sizeof(LUT) }, 
						{.EPD266Cmd_code_data = EPD266CMD, .EPD266Cmd_delay = 0, .EPD266BusyWait = false, .EPD266HoldCS = false, .EPD266Args = 1, .EPD266Cmd_value = EPD266_CMD_WTF },
							{.EPD266Cmd_code_data = EPD266ARRAY, .EPD266Array= (uint8_t *)&LUT2[0], .EPD266Args = sizeof(LUT2) }, 
#endif
						{.EPD266Cmd_code_data = EPD266CMD, .EPD266Cmd_delay = 0, .EPD266BusyWait = false, .EPD266HoldCS = false, .EPD266Args = 1, .EPD266Cmd_value = EPD266_CMD_DEM },
							{.EPD266Cmd_code_data = EPD266DATA, .EPD266Cmd_value =  0x03 },
						{.EPD266Cmd_code_data = EPD266CMD, .EPD266Cmd_delay = 0, .EPD266BusyWait = false, .EPD266HoldCS = false, .EPD266Args = 2, .EPD266Cmd_value = EPD266_CMD_RAM_X },
							{.EPD266Cmd_code_data = EPD266DATA, .EPD266Cmd_value =  0x01 },
							{.EPD266Cmd_code_data = EPD266DATA, .EPD266Cmd_value =  EPD266_LCDHEIGHT/8 },
						{.EPD266Cmd_code_data = EPD266CMD, .EPD266Cmd_delay = 0, .EPD266BusyWait = false, .EPD266HoldCS = false, .EPD266Args = 4, .EPD266Cmd_value = EPD266_CMD_RAM_Y },
							{.EPD266Cmd_code_data = EPD266DATA, .EPD266Cmd_value = 0 },
							{.EPD266Cmd_code_data = EPD266DATA, .EPD266Cmd_value = 0 },
							{.EPD266Cmd_code_data = EPD266DATA, .EPD266Cmd_value =  EPD266_LCDWIDTH & 0xFF },
							{.EPD266Cmd_code_data = EPD266DATA, .EPD266Cmd_value =  (EPD266_LCDWIDTH >>8) & 0x01 }, 
#if LUT_SPEED_EPD266 != 0
						{.EPD266Cmd_code_data = EPD266CMD, .EPD266Cmd_delay = 0, .EPD266BusyWait = false, .EPD266HoldCS = false, .EPD266Args = 1, .EPD266Cmd_value = EPD266_CMD_VBD },
							{.EPD266Cmd_code_data = EPD266DATA, .EPD266Cmd_value =  0x80 },
						{.EPD266Cmd_code_data = EPD266CMD, .EPD266Cmd_delay = 0, .EPD266BusyWait = false, .EPD266HoldCS = false, .EPD266Args = 1, .EPD266Cmd_value = EPD266_CMD_DUC2 },
							{.EPD266Cmd_code_data = EPD266DATA, .EPD266Cmd_value =  0xCF },
						{.EPD266Cmd_code_data = EPD266CMD, .EPD266Cmd_delay = 0, .EPD266BusyWait = true, .EPD266HoldCS = false, .EPD266Args = 0, .EPD266Cmd_value = EPD266_CMD_ACTIVATE },
#endif
						{.EPD266Cmd_code_data = EPD266DONE },	
					};

static const EPD266_CMD	EPD266CommandDisplayOn[] =
					{
						{.EPD266Cmd_code_data = EPD266DONE },		
					};

static const EPD266_CMD	EPD266CommandDisplayOff[] =
					{
						{.EPD266Cmd_code_data = EPD266DONE },		
					};
static const EPD266_CMD	EPD266CommandRefreshDisplayBuffer[] =
					{
						{.EPD266Cmd_code_data = EPD266CMD, .EPD266Cmd_delay = 0, .EPD266BusyWait = false, .EPD266HoldCS = true, .EPD266Args = 0, .EPD266Cmd_value = EPD266_CMD_WRITE_RAM },
						{.EPD266Cmd_code_data = EPD266DONE },	
					};
static const EPD266_CMD	EPD266CommandRefreshDisplay[] =
					{
						{.EPD266Cmd_code_data = EPD266CMD, .EPD266Cmd_delay = 0, .EPD266BusyWait = true, .EPD266HoldCS = false, .EPD266Args = 0, .EPD266Cmd_value = EPD266_CMD_ACTIVATE },
						{.EPD266Cmd_code_data = EPD266DONE },	
					};


static uint8_t		epd266CommandBuffer[64];

static uint8_t		epd266FrameBuffer[EPD266_FRAME_BUFFER_SIZE];
static uint8_t		junkBuffer[EPD266_FRAME_BUFFER_SIZE];		// a dumpster for SPI Rx data or for pre white-wash cycle.  MISO hardware always writes 0s over it

static uint16_t		epd266ColourTable[16] = { 	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0xff };


//////////////////////////////
// Local Function prototypes
//////////////////////////////

static bool epd266_init(void);
static bool epd266_power( bool _bPowerup  );
static bool epd266_busyWait(void);
static bool epd266_isBusy(void);
static bool epd266_refresh(void);
static bool	send_LCD_Message( EPD266_CMD *_pMsg );


//////////////////////////////
// Global variables
//////////////////////////////

DISPLAY_PARAMS	EPD266DisplayParams =
{
	.initDisplay = epd266_init,
	.powerDisplay = epd266_power,
	.busyWaitDisplay = epd266_busyWait,
	.isBusyDisplay = epd266_isBusy,
	.refreshDisplay = epd266_refresh,
	.pFrameBuffer = &epd266FrameBuffer[0],
	.frameBufferSize = EPD266_FRAME_BUFFER_SIZE,
	.pixelDepth = 1,
	.pColorMap = epd266ColourTable,
	.pFontDesc = &font_8x16_desc,
	.magn = 1,
#if LUT_SPEED_EPD266 == 0
	.busyTime_ms = 4500,	
#elif LUT_SPEED_EPD266 == 1
	.busyTime_ms = 880,			
#elif LUT_SPEED_EPD266 == 2
	.busyTime_ms = 1760,			
#endif
	.height = EPD266_LCDHEIGHT,
	.width = EPD266_LCDWIDTH,
	.resetPin = EPD266_RESET_PIN,
	.busyPin = EPD266_BUSY_PIN,
	.spiChannel = EPD266_SPI_CHANNEL,
	.spiMosiPin = EPD266_MOSI_PIN,
	.spiMisoPin = EPD266_MISO_PIN,
	.spiSckPin = EPD266_SCK_PIN,
	.spiCsPin = EPD266_CS_PIN,
	.spiDcPin = EPD266_DC_PIN,
	.flags = DISPLAY_FLAG_HEAD_OVER | DISPLAY_FLAG_BYTE_PIXELS_VERTICAL
};


/////////////////////////////////////
// EPD266 Initialization function
/////////////////////////////////////

static bool epd266_init(void)
{
	SPI_CHANNEL		*_pSpiChannel = pSpiChannelDescript[EPD266DisplayParams.spiChannel];

	// define EPD266 Reset pin 
	gpio_init(EPD266DisplayParams.resetPin);			// reset...
	gpio_set_dir(EPD266DisplayParams.resetPin,true);	// output
	gpio_put(EPD266DisplayParams.resetPin,true);		// high

	// define EPD266 Busy pin 
	gpio_init(EPD266DisplayParams.busyPin);				// busy...   
	gpio_set_dir(EPD266DisplayParams.busyPin,false);	// input
	gpio_pull_up(EPD266DisplayParams.busyPin);			// pulled up

	// define EPD266 D/C pin 
	gpio_init(EPD266DisplayParams.spiDcPin);			// dc...
	gpio_set_dir(EPD266DisplayParams.spiDcPin,true);	// output
	gpio_put(EPD266DisplayParams.spiDcPin,true);		// high

	// strobe the reset pin
	gpio_put(EPD266DisplayParams.resetPin,false);		// low
	sleep_us( 2000 );									// wait 2 ms
	gpio_put(EPD266DisplayParams.resetPin,true);		// high
	epd266_busyWait();

	// set all gpios used by the spi driver
	_pSpiChannel->gpio_cs_pin = EPD266DisplayParams.spiCsPin;
	_pSpiChannel->gpio_tx_pin = EPD266DisplayParams.spiMosiPin;
	_pSpiChannel->gpio_rx_pin = EPD266DisplayParams.spiMisoPin;
	_pSpiChannel->gpio_sclk_pin = EPD266DisplayParams.spiSckPin;
	_pSpiChannel->spi_baud = EPD266_SPI_BAUD;

	// initialize the pio_spi if it isn't already, else just return false
	if ( isInitialized_pio_spi(EPD266DisplayParams.spiChannel) ) return false;
	init_pio_spi( EPD266DisplayParams.spiChannel );

	return send_LCD_Message((EPD266_CMD *)&epd266CommandInitSequence[0]);
}

/////////////////////////////////////
// EPD266 Power up/down
/////////////////////////////////////

static bool epd266_power( bool _bPowerup  )
{
	if ( !isInitialized_pio_spi(EPD266DisplayParams.spiChannel) ) return false;		// must be initialized!

	return send_LCD_Message( _bPowerup ? (EPD266_CMD *)&EPD266CommandDisplayOn[0] : (EPD266_CMD *)&EPD266CommandDisplayOff[0] );
}


/////////////////////////////////////
// EPD266 Refresh Display
/////////////////////////////////////

static bool epd266_refresh(void)
{
	SPI_CHANNEL		*_pSpiChannel = pSpiChannelDescript[EPD266DisplayParams.spiChannel];

	if ( !isInitialized_pio_spi(EPD266DisplayParams.spiChannel) ) return false;		// must be initialized!

#if LUT_SPEED_EPD266 == 2
	if ( !send_LCD_Message((EPD266_CMD *)&EPD266CommandRefreshDisplayBuffer[0]) ) return false;
	gpio_put(EPD266DisplayParams.spiDcPin,true);			//  dc high = DATA
	_pSpiChannel->txBuffer = epd266FrameBuffer;
	_pSpiChannel->rxBuffer = junkBuffer; 
	_pSpiChannel->txBufferSize = EPD266_FRAME_BUFFER_SIZE;
	_pSpiChannel->rxBufferSize = _pSpiChannel->txBufferSize;
	_pSpiChannel->chipSelect = SPI_CHIP_SELECT_DEASSERT;
	start_pio_spi(EPD266DisplayParams.spiChannel);
	send_LCD_Message((EPD266_CMD *)&EPD266CommandRefreshDisplay[0]);
	// let this finish
	epd266_busyWait();
#endif

	// send the frame buffer
	if ( !send_LCD_Message((EPD266_CMD *)&EPD266CommandRefreshDisplayBuffer[0]) ) return false;
	gpio_put(EPD266DisplayParams.spiDcPin,true);			//  dc high = DATA
	_pSpiChannel->txBuffer = epd266FrameBuffer;
	_pSpiChannel->rxBuffer = junkBuffer; 
	_pSpiChannel->txBufferSize = EPD266_FRAME_BUFFER_SIZE;
	_pSpiChannel->rxBufferSize = _pSpiChannel->txBufferSize;
	_pSpiChannel->chipSelect = SPI_CHIP_SELECT_DEASSERT;
	start_pio_spi(EPD266DisplayParams.spiChannel);
	// send the suffix
	return (send_LCD_Message((EPD266_CMD *)&EPD266CommandRefreshDisplay[0]));
}	

/////////////////////////////////////
// EPD266 Wait busy 
/////////////////////////////////////

static bool epd266_busyWait(void)
{
	if ( !isInitialized_pio_spi(EPD266DisplayParams.spiChannel) ) return false;		// must be initialized!

	while ( gpio_get(EPD266DisplayParams.busyPin) == 1 ) tight_loop_contents();
}

/////////////////////////////////////
// EPD266 is busy 
/////////////////////////////////////

static bool epd266_isBusy(void)
{
	if ( !isInitialized_pio_spi(EPD266DisplayParams.spiChannel) ) return false;		// must be initialized!

	return ( gpio_get(EPD266DisplayParams.busyPin) == 1 );
}




/////////////////////////////////////////////
// Send Message ( Command and data )mfrom table 
//////////////////////////////////////////////


static bool	send_LCD_Message( EPD266_CMD *_pMsg )
{
	SPI_CHANNEL		*_pSpiChannel = pSpiChannelDescript[EPD266DisplayParams.spiChannel];

	uint8_t			*_pArray;

	uint8_t			_i;
	uint16_t		_delay;
	bool			_busyWait,
					_holdCS;
	uint8_t			_nArgs;

	bool			_bRc = true;

	_pSpiChannel->txBuffer = epd266CommandBuffer+1;
	_pSpiChannel->rxBuffer = epd266CommandBuffer;

	// do till end marker
	while ( _bRc && ( (_pMsg->EPD266Cmd_code_data ) != EPD266DONE ) )
	{
		// must 1st be a conmmand
		if ( _pMsg->EPD266Cmd_code_data == EPD266CMD )
		{
			_nArgs = _pMsg->EPD266Args;			// how many args?
			_delay = _pMsg->EPD266Cmd_delay;		// remember the delay
			_busyWait = _pMsg->EPD266BusyWait;		// remember busy wait requirement
			_holdCS = _pMsg->EPD266HoldCS;			// remember hold CS

			gpio_put(EPD266DisplayParams.spiDcPin,false);	// dc low = command
			_pSpiChannel->txBuffer[0] = _pMsg->EPD266Cmd_value;
			_pSpiChannel->txBufferSize = 1;
			_pSpiChannel->rxBufferSize = _pSpiChannel->txBufferSize;
			_pSpiChannel->chipSelect = ( (_nArgs == 0) && !_holdCS ) ? SPI_CHIP_SELECT_BOTH : SPI_CHIP_SELECT_ASSERT;
			start_pio_spi(EPD266DisplayParams.spiChannel);


			for ( _i = 0; _i < _nArgs; _i++ )
			{
				_pMsg++;
				if(_pMsg->EPD266Cmd_code_data == EPD266ARRAY)
				{
					_nArgs = _pMsg->EPD266Args;
					memcpy( _pSpiChannel->txBuffer, _pMsg->EPD266Array, _nArgs );
					break;
				}
				else  if(_pMsg->EPD266Cmd_code_data == EPD266DATA)
				{
					_pSpiChannel->txBuffer[_i] = _pMsg->EPD266Cmd_value;
				}
				else
				{
					_bRc = false;
					break;
				}
			}

			if ( _bRc )
			{
				gpio_put(EPD266DisplayParams.spiDcPin,true);				//  dc high = DATA
				_pSpiChannel->txBufferSize = _nArgs;
				_pSpiChannel->rxBufferSize = _pSpiChannel->txBufferSize;
				_pSpiChannel->chipSelect = _holdCS ? SPI_CHIP_SELECT_NONE : SPI_CHIP_SELECT_DEASSERT ;		
				start_pio_spi(EPD266DisplayParams.spiChannel);			 // start the spi transfer
			}
			
			_pMsg++;
		}
		else
		{
			_bRc = false;
		}

		if ( _bRc && (_delay != 0 ) )		// fixed time delay ?
		{
			sleep_ms(_delay);
		}

		if ( _bRc && _busyWait )				// wait for !Busy ?
		{
			epd266_busyWait();
		}
	}

	return _bRc;
}

