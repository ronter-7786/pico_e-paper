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
	bool		(*initDisplay)(uint8_t _channel);
	bool		(*refreshDisplay)(uint8_t _channel);
	bool		(*busyWaitDisplay)(uint8_t _channel);
	bool		(*isBusyDisplay)(uint8_t _channel);
	bool		(*powerDisplay)(uint8_t _channel, bool _power);
	uint32_t	frameBufferSize;
	uint8_t		magn;
	uint8_t		pixelDepth;
	uint16_t	height,				// frame dimensions in pixels
				width;
	uint8_t		flags;
}DISPLAY_PARAMS;


#define DISPLAY_FLAG_MIRROR			0x01	// flip the display
#define DISPLAY_FLAG_ROTATE_90		0x02	// display rotates 90 deg

#define SYMBOL_8x8_ZONE		0
#define SYMBOL_8x8_GUN		1
#define SYMBOL_8x8_SHIELD	2

extern FONT_DESC	font_8x16_desc;
extern FONT_DESC	font_7seg_24x48_desc;

extern bool draw_pixel(DISPLAY_PARAMS *pDisplayParams, uint16_t _x, uint16_t _y, COLOR_INDEX _pixelColor );
extern bool draw_char( DISPLAY_PARAMS *pDisplayParams, char _char, uint16_t _x, uint16_t _y, COLOR_INDEX _bgColor, COLOR_INDEX _fgColor );
extern bool draw_string( DISPLAY_PARAMS *pDisplayParams , char *_pString, uint16_t _x, uint16_t _y,  COLOR_INDEX _bgColor, COLOR_INDEX _fgColor );
extern void clear_frameBuffer(DISPLAY_PARAMS *pDisplayParams, COLOR_INDEX _colorIndex );

