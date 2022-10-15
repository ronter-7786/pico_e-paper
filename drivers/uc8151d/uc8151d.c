#include "uc8151d.h"

/************************************************/
/*  Definitions for UC8151D e-paper Controller	*/
/************************************************/


/************************/
/*	Local Variables		*/
/************************/

///////////////////////////////////////////
// Look Up Tables for refresh rate
//  4 speeds...
//			0 = slow	4500 mS   (default)
//			1 = medium  2000 mS
//			2 = fast	 800 mS
//			3 = turbo	 250 mS   ** leaves behind "ghosts" but an extra pre-write of all 1's helps
//
///////////////////////////////////////////
#if ( LUT_SPEED == 1 )
static const uint8_t	lutVCOM[] =
	{
      0x00, 0x16, 0x16, 0x0d, 0x00, 0x01,
      0x00, 0x23, 0x23, 0x00, 0x00, 0x02,
      0x00, 0x16, 0x16, 0x0d, 0x00, 0x01,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00
    };
static const uint8_t	lutWW[] =
	{
      0x54, 0x16, 0x16, 0x0d, 0x00, 0x01,
      0x60, 0x23, 0x23, 0x00, 0x00, 0x02,
      0xa8, 0x16, 0x16, 0x0d, 0x00, 0x01,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
static const uint8_t	lutBW[] =
	{
      0x54, 0x16, 0x16, 0x0d, 0x00, 0x01,
      0x60, 0x23, 0x23, 0x00, 0x00, 0x02,
      0xa8, 0x16, 0x16, 0x0d, 0x00, 0x01,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
static const uint8_t	lutWB[] =
	{
      0xa8, 0x16, 0x16, 0x0d, 0x00, 0x01,
      0x60, 0x23, 0x23, 0x00, 0x00, 0x02,
      0x54, 0x16, 0x16, 0x0d, 0x00, 0x01,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
static const uint8_t	lutBB[] =
	{
      0xa8, 0x16, 0x16, 0x0d, 0x00, 0x01,
      0x60, 0x23, 0x23, 0x00, 0x00, 0x02,
      0x54, 0x16, 0x16, 0x0d, 0x00, 0x01,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
#elif ( LUT_SPEED == 2 )
static const uint8_t	lutVCOM[] =
	{
      0x00, 0x04, 0x04, 0x07, 0x00, 0x01,
      0x00, 0x0c, 0x0c, 0x00, 0x00, 0x02,
      0x00, 0x04, 0x04, 0x07, 0x00, 0x02,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00
    };
static const uint8_t	lutWW[] =
	{
      0x54, 0x04, 0x04, 0x07, 0x00, 0x01,
      0x60, 0x0c, 0x0c, 0x00, 0x00, 0x02,
      0xa8, 0x04, 0x04, 0x07, 0x00, 0x02,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
static const uint8_t	lutBW[] =
	{
      0x54, 0x04, 0x04, 0x07, 0x00, 0x01,
      0x60, 0x0c, 0x0c, 0x00, 0x00, 0x02,
      0xa8, 0x04, 0x04, 0x07, 0x00, 0x02,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
static const uint8_t	lutWB[] =
	{
      0xa8, 0x04, 0x04, 0x07, 0x00, 0x01,
      0x60, 0x0c, 0x0c, 0x00, 0x00, 0x02,
      0x54, 0x04, 0x04, 0x07, 0x00, 0x02,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
static const uint8_t	lutBB[] =
	{
      0xa8, 0x04, 0x04, 0x07, 0x00, 0x01,
      0x60, 0x0c, 0x0c, 0x00, 0x00, 0x02,
      0x54, 0x04, 0x04, 0x07, 0x00, 0x02,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
#elif ( LUT_SPEED == 3 )
static const uint8_t	lutVCOM[] =
	{
      0x00, 0x01, 0x01, 0x02, 0x00, 0x01,
      0x00, 0x02, 0x02, 0x00, 0x00, 0x02,
      0x00, 0x02, 0x02, 0x03, 0x00, 0x02,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00
    };
static const uint8_t	lutWW[] =
	{
      0x54, 0x01, 0x01, 0x02, 0x00, 0x01,
      0x60, 0x02, 0x02, 0x00, 0x00, 0x02,
      0xa8, 0x02, 0x02, 0x03, 0x00, 0x02,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
static const uint8_t	lutBW[] =
	{
      0x54, 0x01, 0x01, 0x02, 0x00, 0x01,
      0x60, 0x02, 0x02, 0x00, 0x00, 0x02,
      0xa8, 0x02, 0x02, 0x03, 0x00, 0x02,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
static const uint8_t	lutWB[] =
	{
      0xa8, 0x01, 0x01, 0x02, 0x00, 0x01,
      0x60, 0x02, 0x02, 0x00, 0x00, 0x02,
      0x54, 0x02, 0x02, 0x03, 0x00, 0x02,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
static const uint8_t	lutBB[] =
	{
      0xa8, 0x01, 0x01, 0x02, 0x00, 0x01,
      0x60, 0x02, 0x02, 0x00, 0x00, 0x02,
      0x54, 0x02, 0x02, 0x03, 0x00, 0x02,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
#endif

static const UC8151D_CMD	uc8151dCommandInitSequence[] =
					{
						{.UC8151DCmd_code_data = UC8151DCMD, .UC8151DCmd_delay = 0, .UC8151DBusyWait = false, .UC8151DHoldCS = false, .UC8151DArgs = 1, .UC8151DCmd_value = UC8151D_CMD_PSR },
#if ( LUT_SPEED == 0 )
							{.UC8151DCmd_code_data = UC8151DDATA, .UC8151DCmd_value = ( RES_128x296 | FORMAT_BW | BOOSTER_ON | LUT_OTP | RESET_NONE | SHIFT_RIGHT | SCAN_DOWN) },
#else
							{.UC8151DCmd_code_data = UC8151DDATA, .UC8151DCmd_value = ( RES_128x296 | FORMAT_BW | BOOSTER_ON | LUT_REG | RESET_NONE | SHIFT_RIGHT | SCAN_DOWN) },
						{.UC8151DCmd_code_data = UC8151DCMD, .UC8151DCmd_delay = 0, .UC8151DBusyWait = false, .UC8151DHoldCS = false, .UC8151DArgs = 1, .UC8151DCmd_value = UC8151D_CMD_LUT_VCOM },
							{.UC8151DCmd_code_data = UC8151DARRAY, .UC8151DArray = (uint8_t *)&lutVCOM[0], .UC8151DArgs = sizeof(lutVCOM) },
						{.UC8151DCmd_code_data = UC8151DCMD, .UC8151DCmd_delay = 0, .UC8151DBusyWait = false, .UC8151DHoldCS = false, .UC8151DArgs = 1, .UC8151DCmd_value = UC8151D_CMD_LUT_WW },
							{.UC8151DCmd_code_data = UC8151DARRAY, .UC8151DArray = (uint8_t *)&lutWW[0], .UC8151DArgs = sizeof(lutWW) },
						{.UC8151DCmd_code_data = UC8151DCMD, .UC8151DCmd_delay = 0, .UC8151DBusyWait = false, .UC8151DHoldCS = false, .UC8151DArgs = 1, .UC8151DCmd_value = UC8151D_CMD_LUT_BW },
							{.UC8151DCmd_code_data = UC8151DARRAY, .UC8151DArray = (uint8_t *)&lutBW[0],  .UC8151DArgs = sizeof(lutBW) },
						{.UC8151DCmd_code_data = UC8151DCMD, .UC8151DCmd_delay = 0, .UC8151DBusyWait = false, .UC8151DHoldCS = false, .UC8151DArgs = 1, .UC8151DCmd_value = UC8151D_CMD_LUT_WB },
							{.UC8151DCmd_code_data = UC8151DARRAY, .UC8151DArray = (uint8_t *)&lutWB[0], .UC8151DArgs = sizeof(lutWB) },
						{.UC8151DCmd_code_data = UC8151DCMD, .UC8151DCmd_delay = 0, .UC8151DBusyWait = false, .UC8151DHoldCS = false, .UC8151DArgs = 1, .UC8151DCmd_value = UC8151D_CMD_LUT_BB },
							{.UC8151DCmd_code_data = UC8151DARRAY, .UC8151DArray = (uint8_t *)&lutBB[0], .UC8151DArgs = sizeof(lutBB) },
#endif
						{.UC8151DCmd_code_data = UC8151DCMD, .UC8151DCmd_delay = 0, .UC8151DBusyWait = false, .UC8151DHoldCS = false, .UC8151DArgs = 5, .UC8151DCmd_value = UC8151D_CMD_PWR },
							{.UC8151DCmd_code_data = UC8151DDATA, .UC8151DCmd_value =  ( VDS_INTERNAL | VDG_INTERNAL ) },
							{.UC8151DCmd_code_data = UC8151DDATA, .UC8151DCmd_value =  ( VCOM_VD | VGHL_16V ) },
							{.UC8151DCmd_code_data = UC8151DDATA, .UC8151DCmd_value = 0x2B },
							{.UC8151DCmd_code_data = UC8151DDATA, .UC8151DCmd_value = 0x2B },
							{.UC8151DCmd_code_data = UC8151DDATA, .UC8151DCmd_value = 0x2B },
						{.UC8151DCmd_code_data = UC8151DCMD, .UC8151DCmd_delay = 0, .UC8151DBusyWait = true, .UC8151DHoldCS = false, .UC8151DArgs = 0, .UC8151DCmd_value = UC8151D_CMD_PON },
						{.UC8151DCmd_code_data = UC8151DCMD, .UC8151DCmd_delay = 0, .UC8151DBusyWait = false, .UC8151DHoldCS = false, .UC8151DArgs = 3, .UC8151DCmd_value = UC8151D_CMD_BTST },
							{.UC8151DCmd_code_data = UC8151DDATA, .UC8151DCmd_value =  ( START_10MS | STRENGTH_3 | OFF_6_58US ) },
							{.UC8151DCmd_code_data = UC8151DDATA, .UC8151DCmd_value =  ( START_10MS | STRENGTH_3 | OFF_6_58US ) },
							{.UC8151DCmd_code_data = UC8151DDATA, .UC8151DCmd_value =  (  START_10MS | STRENGTH_3 | OFF_6_58US ) },
						{.UC8151DCmd_code_data = UC8151DCMD, .UC8151DCmd_delay = 0, .UC8151DBusyWait = false, .UC8151DHoldCS = false, .UC8151DArgs = 1, .UC8151DCmd_value = UC8151D_CMD_PFS },
							{.UC8151DCmd_code_data = UC8151DDATA, .UC8151DCmd_value = ( FRAMES_1 ) },
						{.UC8151DCmd_code_data = UC8151DCMD, .UC8151DCmd_delay = 0, .UC8151DBusyWait = false, .UC8151DHoldCS = false, .UC8151DArgs = 1, .UC8151DCmd_value = UC8151D_CMD_TSE },
							{.UC8151DCmd_code_data = UC8151DDATA, .UC8151DCmd_value = (  TEMP_INTERNAL | OFFSET_0 ) },
						{.UC8151DCmd_code_data = UC8151DCMD, .UC8151DCmd_delay = 0, .UC8151DBusyWait = false, .UC8151DHoldCS = false, .UC8151DArgs = 1, .UC8151DCmd_value = UC8151D_CMD_TCON },
							{.UC8151DCmd_code_data = UC8151DDATA,.UC8151DCmd_value = 0x22 },
						{.UC8151DCmd_code_data = UC8151DCMD, .UC8151DCmd_delay = 0, .UC8151DBusyWait = false, .UC8151DHoldCS = false, .UC8151DArgs = 1, .UC8151DCmd_value = UC8151D_CMD_CDI },
							{.UC8151DCmd_code_data = UC8151DDATA, .UC8151DCmd_value = 0x9C },
						{.UC8151DCmd_code_data = UC8151DCMD, .UC8151DCmd_delay = 0, .UC8151DBusyWait = false, .UC8151DHoldCS = false, .UC8151DArgs = 1, .UC8151DCmd_value = UC8151D_CMD_PLL },
							{.UC8151DCmd_code_data = UC8151DDATA, .UC8151DCmd_value = HZ_100 },
						{.UC8151DCmd_code_data = UC8151DDONE},		
					};

static const UC8151D_CMD	UC8151DCommandDisplayOn[] =
					{
						{.UC8151DCmd_code_data = UC8151DCMD, .UC8151DCmd_delay = 0, .UC8151DBusyWait = false, .UC8151DHoldCS = false, .UC8151DArgs = 0, .UC8151DCmd_value = UC8151D_CMD_PON },
						{.UC8151DCmd_code_data = UC8151DDONE },		
					};

static const UC8151D_CMD	UC8151DCommandDisplayOff[] =
					{
						{.UC8151DCmd_code_data = UC8151DCMD, .UC8151DCmd_delay = 0, .UC8151DBusyWait = false, .UC8151DHoldCS = false, .UC8151DArgs = 0, .UC8151DCmd_value = UC8151D_CMD_POF },
						{.UC8151DCmd_code_data = UC8151DDONE },		
					};
static const UC8151D_CMD	UC8151DCommandRefreshDisplayPrefix[] =
					{
						{.UC8151DCmd_code_data = UC8151DCMD, .UC8151DCmd_delay = 0, .UC8151DBusyWait = false, .UC8151DHoldCS = false, .UC8151DArgs = 0, .UC8151DCmd_value = UC8151D_CMD_PTOUT },
						{.UC8151DCmd_code_data = UC8151DCMD, .UC8151DCmd_delay = 0, .UC8151DBusyWait = false, .UC8151DHoldCS = true,  .UC8151DArgs = 0, .UC8151DCmd_value = UC8151D_CMD_DTM2  },
						{.UC8151DCmd_code_data = UC8151DDONE },	
					};
static const UC8151D_CMD	UC8151DCommandRefreshDisplaySuffix[] =
					{
						{.UC8151DCmd_code_data = UC8151DCMD, .UC8151DCmd_delay = 0, .UC8151DBusyWait = false, .UC8151DHoldCS = false, .UC8151DArgs = 0, .UC8151DCmd_value = UC8151D_CMD_DSP },
						{.UC8151DCmd_code_data = UC8151DCMD, .UC8151DCmd_delay = 0, .UC8151DBusyWait = false, .UC8151DHoldCS = false,  .UC8151DArgs = 0, .UC8151DCmd_value = UC8151D_CMD_DRF  },
						{.UC8151DCmd_code_data = UC8151DDONE },	
					};


static uint8_t		uc8151dCommandBuffer[64];

static uint8_t		uc8151dFrameBuffer[UC8151D_FRAME_BUFFER_SIZE];
static uint8_t		junkBuffer[UC8151D_FRAME_BUFFER_SIZE];		// a dumpster for SPI Rx data... always 0

static uint16_t		uc8151dColourTable[16] =
{
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0xff
};


//////////////////////////////
// Local Function prototypes
//////////////////////////////
static bool uc8151d_init( uint8_t _spiIndex  );
static bool	send_LCD_Message( uint8_t _spiIndex, UC8151D_CMD *_pMsg );
static bool uc8151d_power(uint8_t _spiIndex, bool _bPowerup  );
static bool uc8151d_busyWait(uint8_t _spiIndex );
static bool uc8151d_isBusy( uint8_t _spiIndex );
static bool uc8151d_refresh( uint8_t _spiIndex  );


///////////////////
// Global variables
///////////////////

DISPLAY_PARAMS	UC8151DDisplayParams =
{
	.initDisplay = uc8151d_init,
	.powerDisplay = uc8151d_power,
	.busyWaitDisplay = uc8151d_busyWait,
	.isBusyDisplay = uc8151d_isBusy,
	.refreshDisplay = uc8151d_refresh,
	.pFrameBuffer = &uc8151dFrameBuffer[0],
	.frameBufferSize = UC8151D_FRAME_BUFFER_SIZE,
	.pixelDepth = 1,
	.pColorMap = uc8151dColourTable,
	.pFontDesc = &font_8x16_desc,
	.magn = 1,
	.height = UC8151D_LCDHEIGHT,
	.width = UC8151D_LCDWIDTH,
	.flags = DISPLAY_FLAG_ROTATE_90
};



/////////////////////////////////////
// UC8151D Initialization function
/////////////////////////////////////

static bool uc8151d_init( uint8_t _spiIndex  )
{
	SPI_CHANNEL		*_pSpiChannel = pSpiChannelDescript[_spiIndex];

	// define UC8151D Reset pin & activate for > 50 uS
	gpio_init(UC8151D_RESET_PIN);
	gpio_set_dir(UC8151D_RESET_PIN,true);				// output
	gpio_put(UC8151D_RESET_PIN,false);					// low
	sleep_us( 100ULL );									// wait 100 uS
	gpio_put(UC8151D_RESET_PIN,true);					// high
	sleep_us( 2000ULL );								// wait 2 mS

	// set all gpios used by SPI
	_pSpiChannel->gpio_cs_pin = UC8151D_CS_PIN;
	_pSpiChannel->gpio_dc_pin = UC8151D_DC_PIN;
	_pSpiChannel->gpio_busy_pin = UC8151D_BUSY_PIN;
	_pSpiChannel->spi_baud = UC8151D_SPI_BAUD;

	gpio_init(_pSpiChannel->gpio_sclk_pin);				// spi sck...
	gpio_set_dir(_pSpiChannel->gpio_sclk_pin,true);		// output
	gpio_put(_pSpiChannel->gpio_sclk_pin,false);		// low

	gpio_init(_pSpiChannel->gpio_cs_pin);				// spi cs...
	gpio_set_dir(_pSpiChannel->gpio_cs_pin,true);		// output
	gpio_put(_pSpiChannel->gpio_cs_pin,true);			// high

	gpio_init(_pSpiChannel->gpio_dc_pin);				// spi dc...
	gpio_set_dir(_pSpiChannel->gpio_dc_pin,true);		// output
	gpio_put(_pSpiChannel->gpio_dc_pin,true);			// high ... for now

	gpio_init(_pSpiChannel->gpio_busy_pin);				// spi busy...
	gpio_set_dir(_pSpiChannel->gpio_busy_pin,false);		// input
	gpio_pull_up(_pSpiChannel->gpio_busy_pin);			// pulled up

	_pSpiChannel->spi_baud = UC8151D_SPI_BAUD;

	// initialize the pio_spi if it isn't already, else just return false
	if ( isInitialized_pio_spi(_spiIndex) ) return false;
	init_pio_spi( _spiIndex );

	return send_LCD_Message(_spiIndex, (UC8151D_CMD *)&uc8151dCommandInitSequence[0]);
}

/////////////////////////////////////
// UC8151D Power up/down
/////////////////////////////////////

static bool uc8151d_power(uint8_t _spiIndex, bool _bPowerup  )
{

	if ( !isInitialized_pio_spi(_spiIndex) ) return false;		// must be initialized!

	return send_LCD_Message(_spiIndex,  _bPowerup ? (UC8151D_CMD *)&UC8151DCommandDisplayOn[0] : (UC8151D_CMD *)&UC8151DCommandDisplayOff[0] );
}


/////////////////////////////////////
// UC8151D Refresh Display
/////////////////////////////////////

static bool uc8151d_refresh( uint8_t _spiIndex  )
{
	SPI_CHANNEL		*_pSpiChannel = pSpiChannelDescript[_spiIndex];

#if ( LUT_SPEED == 3 )	
	// send the whitewash
	memset ( junkBuffer, uc8151dColourTable[WHITE], UC8151D_FRAME_BUFFER_SIZE );
	if ( !send_LCD_Message(_spiIndex, (UC8151D_CMD *)&UC8151DCommandRefreshDisplayPrefix[0]) ) return false;
	gpio_put(_pSpiChannel->gpio_dc_pin,true);			//  dc high = DATA
	_pSpiChannel->txBuffer = junkBuffer;
	_pSpiChannel->rxBuffer = junkBuffer; 
	_pSpiChannel->txBufferSize = UC8151D_FRAME_BUFFER_SIZE;
	_pSpiChannel->rxBufferSize = _pSpiChannel->txBufferSize;
	_pSpiChannel->chipSelect = SPI_CHIP_SELECT_DEASSERT;
	start_pio_spi(_spiIndex);
	send_LCD_Message(_spiIndex, (UC8151D_CMD *)&UC8151DCommandRefreshDisplaySuffix[0]);
	// let this finish
	uc8151d_busyWait(_spiIndex);
#endif

	// send the frame buffer
	if ( !send_LCD_Message(_spiIndex, (UC8151D_CMD *)&UC8151DCommandRefreshDisplayPrefix[0]) ) return false;
	gpio_put(_pSpiChannel->gpio_dc_pin,true);			//  dc high = DATA
	_pSpiChannel->txBuffer = uc8151dFrameBuffer;
	_pSpiChannel->rxBuffer = junkBuffer; 
	_pSpiChannel->txBufferSize = UC8151D_FRAME_BUFFER_SIZE;
	_pSpiChannel->rxBufferSize = _pSpiChannel->txBufferSize;
	_pSpiChannel->chipSelect = SPI_CHIP_SELECT_DEASSERT;
	start_pio_spi(_spiIndex);
	// send the suffix
	return (send_LCD_Message(_spiIndex, (UC8151D_CMD *)&UC8151DCommandRefreshDisplaySuffix[0]));
	uc8151d_busyWait(_spiIndex);

}	

/////////////////////////////////////
// UC8151D Wait busy 
/////////////////////////////////////

static bool uc8151d_busyWait(uint8_t _spiIndex )
{
	SPI_CHANNEL		*_pSpiChannel = pSpiChannelDescript[_spiIndex];

	if ( !isInitialized_pio_spi(_spiIndex) ) return false;		// must be initialized!

	while ( gpio_get(_pSpiChannel->gpio_busy_pin) == 0 ) tight_loop_contents();
}

/////////////////////////////////////
// UC8151D is busy 
/////////////////////////////////////

static bool uc8151d_isBusy( uint8_t _spiIndex )
{
	SPI_CHANNEL		*_pSpiChannel = pSpiChannelDescript[_spiIndex];

	if ( !isInitialized_pio_spi(_spiIndex) ) return false;		// must be initialized!

	return ( gpio_get(_pSpiChannel->gpio_busy_pin) == 0 );
}




/////////////////////////////////////
// Local Send Message function
/////////////////////////////////////


static bool	send_LCD_Message( uint8_t _spiIndex, UC8151D_CMD *_pMsg )
{
	SPI_CHANNEL		*_pSpiChannel = pSpiChannelDescript[_spiIndex];

	uint8_t			*_pArray;

	uint8_t			_i;
	uint16_t		_delay;
	bool			_busyWait,
					_holdCS;
	uint8_t			_nArgs;

	bool			_bRc = true;

	_pSpiChannel->txBuffer = uc8151dCommandBuffer+1;
	_pSpiChannel->rxBuffer = uc8151dCommandBuffer;

	// do till end marker
	while ( _bRc && ( (_pMsg->UC8151DCmd_code_data ) != UC8151DDONE ) )
	{
		// must 1st be a conmmand
		if ( _pMsg->UC8151DCmd_code_data == UC8151DCMD )
		{
			_nArgs = _pMsg->UC8151DArgs;			// how many args?
			_delay = _pMsg->UC8151DCmd_delay;		// remember the delay
			_busyWait = _pMsg->UC8151DBusyWait;		// remember busy wait requirement
			_holdCS = _pMsg->UC8151DHoldCS;			// remember hold CS

			gpio_put(_pSpiChannel->gpio_dc_pin,false);	// dc low = command
			_pSpiChannel->txBuffer[0] = _pMsg->UC8151DCmd_value;
			_pSpiChannel->txBufferSize = 1;
			_pSpiChannel->rxBufferSize = _pSpiChannel->txBufferSize;
			_pSpiChannel->chipSelect = ( (_nArgs == 0) && !_holdCS ) ? SPI_CHIP_SELECT_BOTH : SPI_CHIP_SELECT_ASSERT;
			start_pio_spi(_spiIndex);


			for ( _i = 0; _i < _nArgs; _i++ )
			{
				_pMsg++;
				if(_pMsg->UC8151DCmd_code_data == UC8151DARRAY)
				{
					_nArgs = _pMsg->UC8151DArgs;
					memcpy( _pSpiChannel->txBuffer, _pMsg->UC8151DArray, _nArgs );
					break;
				}
				else  if(_pMsg->UC8151DCmd_code_data == UC8151DDATA)
				{
					_pSpiChannel->txBuffer[_i] = _pMsg->UC8151DCmd_value;
				}
				else
				{
					_bRc = false;
					break;
				}
			}

			if ( _bRc )
			{
				gpio_put(_pSpiChannel->gpio_dc_pin,true);			//  dc high = DATA
				_pSpiChannel->txBufferSize = _nArgs;
				_pSpiChannel->rxBufferSize = _pSpiChannel->txBufferSize;
				_pSpiChannel->chipSelect = _holdCS ? SPI_CHIP_SELECT_NONE : SPI_CHIP_SELECT_DEASSERT ;		
				start_pio_spi(_spiIndex);									// start the spi transfer
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
			while ( gpio_get(_pSpiChannel->gpio_busy_pin) == 0 ) tight_loop_contents();
		}
	}

	return _bRc;
}

