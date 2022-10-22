#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <pico/util/queue.h>
#include <pico/unique_id.h>
#include <pico/mutex.h>
#include <pico/sem.h>
#include <pico/bootrom.h>

#include "pixel_func.h"
#include "pio_spi.h"


/*****************************************************
 *
 *  Defines for EPD266 controller chip
 *   on WaveShare e-paper 2.66" 296 x 128 Mono
 *
******************************************************/

// define GPIO pins used by this display
#define EPD266_SPI_CHANNEL				1			// display is on spi channel 1

#define EPD266_BUSY_PIN					13			// BUSY
#define EPD266_RESET_PIN				12			// Reset

#define EPD266_MOSI_PIN					11			// SPI MOSI
#define EPD266_MISO_PIN					16			// SPI MISO *** bogus, there is no MISO
#define EPD266_SCK_PIN					10			// SPI SCK
#define EPD266_DC_PIN					8			// C/D
#define EPD266_CS_PIN					9			// CS

#ifndef NDEBUG
#define EPD266_SPI_BAUD					1000000		// clock speed of SPI bus
#else
#define EPD266_SPI_BAUD					4000000		// clock speed of SPI bus
#endif


#define EPD266_LCDWIDTH					296			// 296 x 152 pixel display
#define EPD266_LCDHEIGHT				152
#define EPD266_FRAME_BUFFER_SIZE		( ( EPD266_LCDHEIGHT / 8 ) * EPD266_LCDWIDTH )

#define EPD266_CMD_RST					0x12		// Reset
#define EPD266_CMD_DEM					0x11		// Data entry mode
#define EPD266_CMD_ACTIVATE				0x20		// activate the display
#define EPD266_CMD_DUC2					0x22		// Display Update Control 2
#define EPD266_CMD_WRITE_RAM			0x24		// white to RAM buffer
#define EPD266_CMD_RAM_X				0x44		// Set RAM X address Start/End
#define EPD266_CMD_RAM_Y				0x45		// Set RAM Y address Start/End
#define EPD266_CMD_LUT					0x32		// write the look-up table
#define EPD266_CMD_WTF					0x37		// undocumented!
#define EPD266_CMD_VBD					0x3C



typedef struct
{
	uint8_t			EPD266Cmd_code_data;
	uint8_t			EPD266Args;
	uint8_t			EPD266Cmd_value;
	bool			EPD266BusyWait;
	bool			EPD266HoldCS;
	uint16_t		EPD266Cmd_delay;
	uint8_t			*EPD266Array;
}EPD266_CMD;

#define EPD266CMD		0
#define EPD266DATA		1
#define EPD266ARRAY		2
#define EPD266HOLD_CS	0x10
#define EPD266DONE		0xFF

extern DISPLAY_PARAMS	EPD266DisplayParams;
extern FONT_DESC		font_8x16_desc;



