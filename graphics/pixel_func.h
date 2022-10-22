#pragma once


#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


typedef struct 
{
	uint8_t		MinChar,
				MaxChar;
	uint8_t		Height;
	uint8_t		Width;
	uint8_t	   *pBitmap;
}FONT_DESC;


typedef enum {				// some pre-defined colors
		BLACK = 0, 
		BLUE, 
		GREEN, 
		CYAN, 
		RED, 
		PURPLE, 
		ORANGE, 
		LIGHT_GREY, 
		GREY, 
		LIGHT_BLUE, 
		LIGHT_GREEN,
		LIGHT_CYAN,
		LIGHT_RED,
		LIGHT_PURPLE,
		YELLOW, 
		WHITE = 15
	} COLOR_INDEX;


typedef struct
{
	uint8_t		*pFrameBuffer;
	uint16_t	*pColorMap;
	FONT_DESC	*pFontDesc;
	bool		(*initDisplay)(void);
	bool		(*refreshDisplay)(void);
	bool		(*busyWaitDisplay)(void);
	bool		(*isBusyDisplay)(void);
	bool		(*powerDisplay)(bool _power);
	uint32_t	busyTime_ms;
	uint32_t	frameBufferSize;
	uint16_t	height,				// frame dimensions in pixels
				width;
	uint8_t		magn;				// font magnification
	uint8_t		pixelDepth;			// color info

	uint8_t		resetPin,			// reset pin
				busyPin;			// busy pin
	uint8_t		spiChannel;			// SPI channel
	uint8_t		spiMosiPin,			// pins for SPI MOSI, MISO, SCK, CS, D/C, BUSY
				spiMisoPin,
				spiSckPin,
				spiCsPin,
				spiDcPin;
	uint8_t		flags;				// rotate/mirror  see below
}DISPLAY_PARAMS;

#define DISPLAY_FLAG_ROTATE_180					0x01	// flip the display 180 deg
#define DISPLAY_FLAG_BYTE_PIXELS_VERTICAL		0x02	// display rotates 90 deg
#define DISPLAY_FLAG_HEAD_OVER					0x04	// flip the display over

extern FONT_DESC	font_8x16_desc;
extern FONT_DESC	font_7seg_24x48_desc;

extern bool draw_pixel(DISPLAY_PARAMS *pDisplayParams, uint16_t _x, uint16_t _y, COLOR_INDEX _pixelColor );
extern bool draw_char( DISPLAY_PARAMS *pDisplayParams, char _char, uint16_t _x, uint16_t _y, COLOR_INDEX _bgColor, COLOR_INDEX _fgColor );
extern bool draw_string( DISPLAY_PARAMS *pDisplayParams , char *_pString, uint16_t _x, uint16_t _y,  COLOR_INDEX _bgColor, COLOR_INDEX _fgColor );
extern void clear_frameBuffer(DISPLAY_PARAMS *pDisplayParams, COLOR_INDEX _colorIndex );

