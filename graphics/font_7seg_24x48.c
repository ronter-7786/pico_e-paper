/**********************************************/
/*                                            */
/*       12 char 24 x 48 pixel bitmap font	  */
/*                                            */
/**********************************************/
#include "pixel_func.h"

#define FONT_HEIGHT			48
#define FONT_WIDTH			24
#define FONT_NUM_CHARS		13

static const uint8_t  font_7seg_24x48_bitmap[FONT_NUM_CHARS*FONT_HEIGHT*(FONT_WIDTH/8)] = 
{
	/* 0x2e '.' */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 ... top */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x3f,0xf0,	 /* 00000000|00111111|11110000 */
	0x00,0x3f,0xf0,	 /* 00000000|00111111|11110000 */
	0x00,0x3f,0xf0,	 /* 00000000|00111111|11110000 */
	0x00,0x3f,0xf0,	 /* 00000000|00111111|11110000 */
	0x00,0x3f,0xf0,	 /* 00000000|00111111|11110000 */
	0x00,0x3f,0xf0,	 /* 00000000|00111111|11110000 */
	0x00,0x3f,0xf0,	 /* 00000000|00111111|11110000 */
	0x00,0x3f,0xf0,	 /* 00000000|00111111|11110000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 ... bottom */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */

	/* 0x2f '/' */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 ... top*/
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x3c,	 /* 00000000|00000000|00111100 */
	0x00,0x00,0x3c,	 /* 00000000|00000000|00111100 */
	0x00,0x00,0x78,	 /* 00000000|00000000|01111000 */
	0x00,0x00,0x78,	 /* 00000000|00000000|01111000 */
	0x00,0x00,0xf0,	 /* 00000000|00000000|11110000 */
	0x00,0x00,0xf0,	 /* 00000000|00000000|11110000 */
	0x00,0x01,0xe0,	 /* 00000000|00000001|11100000 */
	0x00,0x01,0xe0,	 /* 00000000|00000001|11100000 */
	0x00,0x03,0xc0,	 /* 00000000|00000011|11000000 */
	0x00,0x03,0xc0,	 /* 00000000|00000011|11000000 */
	0x00,0x07,0x80,	 /* 00000000|00000111|10000000 */
	0x00,0x07,0x80,	 /* 00000000|00000111|10000000 */
	0x00,0x0f,0x00,	 /* 00000000|00001111|00000000 */
	0x00,0x0f,0x00,	 /* 00000000|00001111|00000000 */
	0x00,0x1e,0x00,	 /* 00000000|00011110|00000000 */
	0x00,0x1e,0x00,	 /* 00000000|00011110|00000000 */
	0x00,0x3c,0x00,	 /* 00000000|00111100|00000000 */
	0x00,0x3c,0x00,	 /* 00000000|00111100|00000000 */
	0x00,0x78,0x00,	 /* 00000000|01111000|00000000 */
	0x00,0x78,0x00,	 /* 00000000|01111000|00000000 */
	0x00,0xf0,0x00,	 /* 00000000|11110000|00000000 */
	0x00,0xf0,0x00,	 /* 00000000|11110000|00000000 */
	0x01,0xe0,0x00,	 /* 00000001|11100000|00000000 */
	0x01,0xe0,0x00,	 /* 00000001|11100000|00000000 */
	0x03,0xc0,0x00,	 /* 00000011|11000000|00000000 */
	0x03,0xc0,0x00,	 /* 00000011|11000000|00000000 */
	0x07,0x80,0x00,	 /* 00000111|10000000|00000000 */
	0x07,0x80,0x00,	 /* 00000111|10000000|00000000 */
	0x0f,0x00,0x00,	 /* 00001111|00000000|00000000 */
	0x0f,0x00,0x00,	 /* 00001111|00000000|00000000 */
	0x1e,0x00,0x00,	 /* 00011110|00000000|00000000 */
	0x1e,0x00,0x00,	 /* 00011110|00000000|00000000 */
	0x3c,0x00,0x00,	 /* 00111100|00000000|00000000 */
	0x3c,0x00,0x00,	 /* 00111100|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 ... bottom */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */

	/* 0x30 '0' */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 ... top */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111100|00000000|00111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111100|00000000|00111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 ... bottom */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */

	/* 0x31 '1' */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 ... top */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 ... bottom */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */

	/* 0x32 '2' */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 ... top */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 ... middle */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 ... bottom */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */

	/* 0x33 '3' */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 ... top */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 ... middle */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 ... bottom */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */

	/* 0x34 '4' */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 ... top */
	0x3e,0x00,0x7c,	 /* 00111100|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111100|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111100|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111100|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111100|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111100|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111100|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111100|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111100|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111100|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111100|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111100|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111100|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111100|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111100|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111100|00000000|01111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 ... middle */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 ... bottom */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */

	/* 0x35 '5' */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 ... top */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 ... middle */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 ... bottom */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */

	/* 0x36 '6' */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x3f,0xff,0x00,	 /* 00111111|11111111|00000000 ... top */
	0x3f,0xff,0x00,	 /* 00111111|11111111|00000000 */
	0x3f,0xff,0x00,	 /* 00111111|11111111|00000000 */
	0x3f,0xff,0x00,	 /* 00111111|11111111|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3e,0x00,0x00,	 /* 00111110|00000000|00000000 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 ... middle */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 ... bottom */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */

	/* 0x37 '7' */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 ... top */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x3c,	 /* 00000000|00000000|00111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 ... bottom */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */

	/* 0x38 '8' */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 ... top */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 ... middle */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 ... bottom */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */

	/* 0x39 '9' */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 ... top */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3e,0x00,0x7c,	 /* 00111110|00000000|01111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 ... middle */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x3f,0xff,0xfc,	 /* 00111111|11111111|11111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0x00,0x7c,	 /* 00000000|00000000|01111100 */
	0x00,0xff,0xfc,	 /* 00000000|11111111|11111100 */
	0x00,0xff,0xfc,	 /* 00000000|11111111|11111100 */
	0x00,0xff,0xfc,	 /* 00000000|11111111|11111100 */
	0x00,0xff,0xfc,	 /* 00000000|11111111|11111100 ... bottom */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */

	/* 0x3A ':' */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 ... top */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x3f,0xf0,	 /* 00000000|00111111|11110000 */
	0x00,0x3f,0xf0,	 /* 00000000|00111111|11110000 */
	0x00,0x3f,0xf0,	 /* 00000000|00111111|11110000 */
	0x00,0x3f,0xf0,	 /* 00000000|00111111|11110000 */
	0x00,0x3f,0xf0,	 /* 00000000|00111111|11110000 */
	0x00,0x3f,0xf0,	 /* 00000000|00111111|11110000 */
	0x00,0x3f,0xf0,	 /* 00000000|00111111|11110000 */
	0x00,0x3f,0xf0,	 /* 00000000|00111111|11110000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x3f,0xf0,	 /* 00000000|00111111|11110000 */
	0x00,0x3f,0xf0,	 /* 00000000|00111111|11110000 */
	0x00,0x3f,0xf0,	 /* 00000000|00111111|11110000 */
	0x00,0x3f,0xf0,	 /* 00000000|00111111|11110000 */
	0x00,0x3f,0xf0,	 /* 00000000|00111111|11110000 */
	0x00,0x3f,0xf0,	 /* 00000000|00111111|11110000 */
	0x00,0x3f,0xf0,	 /* 00000000|00111111|11110000 */
	0x00,0x3f,0xf0,	 /* 00000000|00111111|11110000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 ... bottom */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
};



FONT_DESC	font_7seg_24x48_desc =
{
	.MinChar = '.',
	.MaxChar = ':',
	.Height = FONT_HEIGHT,
	.Width = FONT_WIDTH,
	.pBitmap = (uint8_t *)&font_7seg_24x48_bitmap[0]
};