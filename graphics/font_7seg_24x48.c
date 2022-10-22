/**********************************************/
/*                                            */
/*       13 char 24 x 48 pixel bitmap font	  */
/*                                            */
/**********************************************/
#include "pixel_func.h"

#define FONT_HEIGHT			48
#define FONT_WIDTH			24
#define FONT_NUM_CHARS		13

static const uint8_t  font_7seg_24x48_bitmap[FONT_NUM_CHARS*FONT_HEIGHT*(FONT_WIDTH/8)] = 
{
	/* 0x2e '.' */
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
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */

	/* 0x2f '/' */
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
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */
	0x00,0x00,0x00,	 /* 00000000|00000000|00000000 */

	/* 0x30 '0' */
	0x2f,0xff,0xf4,	 /* 00101111|11111111|11110100 ... top */
	0x37,0xff,0xec,	 /* 00110111|11111111|11101100 */
	0x3b,0xff,0xdc,	 /* 00111011|11111111|11011100 */
	0x3d,0xff,0xbc,	 /* 00111101|11111111|10111100 */
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
	0x3d,0xff,0xbc,	 /* 00111101|11111111|10111100 */
	0x3b,0xff,0xdc,	 /* 00111011|11111111|11011100 */
	0x37,0xff,0xec,	 /* 00110111|11111111|11101100 */
	0x2f,0xff,0xf4,	 /* 00101111|11111111|11110100 ... bottom */
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

	/* 0x31 '1' */
	0x00,0x00,0x04,	 /* 00000000|00000000|00000100 ... top */
	0x00,0x00,0x0c,	 /* 00000000|00000000|00001100 */
	0x00,0x00,0x1c,	 /* 00000000|00000000|00011100 */
	0x00,0x00,0x3c,	 /* 00000000|00000000|00111100 */
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
	0x00,0x00,0x3c,	 /* 00000000|00000000|00111100 */
	0x00,0x00,0x1c,	 /* 00000000|00000000|00011100 */
	0x00,0x00,0x0c,	 /* 00000000|00000000|00001100 */
	0x00,0x00,0x04,	 /* 00000000|00000000|00000100 ... bottom */
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

	/* 0x32 '2' */
	0x3f,0xff,0xf4,	 /* 00111111|11111111|11110100 ... top */
	0x1f,0xff,0xec,	 /* 00011111|11111111|11101100 */
	0x0f,0xff,0xdc,	 /* 00001111|11111111|11011100 */
	0x07,0xff,0xbc,	 /* 00000111|11111111|10111100 */
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
	0x2f,0xff,0xbc,	 /* 00101111|11111111|10111100 */
	0x37,0xff,0xdc,	 /* 00110111|11111111|11011100 ... middle */
	0x3b,0xff,0xec,	 /* 00111011|11111111|11101100 */
	0x3d,0xff,0xf4,	 /* 00111101|11111111|11110100 */
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
	0x3d,0xff,0xe0,	 /* 00111101|11111111|11100000 */
	0x3b,0xff,0xf0,	 /* 00111011|11111111|11110000 */
	0x37,0xff,0xf8,	 /* 00110111|11111111|11111000 */
	0x2f,0xff,0xfc,	 /* 00101111|11111111|11111100 ... bottom */
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

	/* 0x33 '3' */
	0x3f,0xff,0xf4,	 /* 00111111|11111111|11110100 ... top */
	0x1f,0xff,0xec,	 /* 00011111|11111111|11101100 */
	0x0f,0xff,0xdc,	 /* 00001111|11111111|11011100 */
	0x07,0xff,0xbc,	 /* 00000111|11111111|10111100 */
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
	0x1f,0xff,0xbc,	 /* 00011111|11111111|10111100 */
	0x3f,0xff,0xdc,	 /* 00111111|11111111|11011100 ... middle */
	0x3f,0xff,0xdc,	 /* 00111111|11111111|11011100 */
	0x1f,0xff,0xbc,	 /* 00011111|11111111|10111100 */
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
	0x07,0xff,0xbc,	 /* 00000111|11111111|10111100 */
	0x0f,0xff,0xdc,	 /* 00001111|11111111|11011100 */
	0x1f,0xff,0xec,	 /* 00011111|11111111|11101100 */
	0x3f,0xff,0xf4,	 /* 00111111|11111111|11110100 ... bottom */
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

	/* 0x34 '4' */
	0x20,0x00,0x04,	 /* 00100000|00000000|00000100 ... top */
	0x30,0x00,0x0c,	 /* 00110000|00000000|00001100 */
	0x38,0x00,0x1c,	 /* 00111000|00000000|00011100 */
	0x3c,0x00,0x3c,	 /* 00111100|00000000|00111100 */
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
	0x3d,0xff,0xbc,	 /* 00111101|11111111|10111100 */
	0x3b,0xff,0xdc,	 /* 00111011|11111111|11011100 ... middle */
	0x37,0xff,0xdc,	 /* 00110111|11111111|11011100 */
	0x2f,0xff,0xbc,	 /* 00101111|11111111|10111100 */
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
	0x00,0x00,0x1c,	 /* 00000000|00000000|00011100 */
	0x00,0x00,0x0c,	 /* 00000000|00000000|00001100 */
	0x00,0x00,0x04,	 /* 00000000|00000000|00000100 ... bottom */
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

	/* 0x35 '5' */
	0x2f,0xff,0xfc,	 /* 00101111|11111111|11111100 ... top */
	0x37,0xff,0xf8,	 /* 00110111|11111111|11111000 */
	0x3b,0xff,0xf0,	 /* 00111011|11111111|11110000 */
	0x3d,0xff,0xe0,	 /* 00111101|11111111|11100000 */
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
	0x3d,0xff,0xf4,	 /* 00111101|11111111|11110100 */
	0x3b,0xff,0xec,	 /* 00111011|11111111|11101100 ... middle */
	0x37,0xff,0xdc,	 /* 00110111|11111111|11011100 */
	0x2f,0xff,0xbc,	 /* 00101111|11111111|10111100*/
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
	0x07,0xff,0xbc,	 /* 00000111|11111111|10111100 */
	0x0f,0xff,0xdc,	 /* 00001111|11111111|11011100 */
	0x1f,0xff,0xec,	 /* 00011111|11111111|11101100 */
	0x3f,0xff,0xf4,	 /* 00111111|11111111|11110100 ... bottom */
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

	/* 0x36 '6' */
	0x2f,0xff,0xfc,	 /* 00101111|11111111|11111100 ... top */
	0x37,0xff,0xf8,	 /* 00110111|11111111|11111000 */
	0x3b,0xff,0xf0,	 /* 00111011|11111111|11110000 */
	0x3d,0xff,0xe0,	 /* 00111101|11111111|11100000 */
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
	0x3d,0xff,0xf4,	 /* 00111101|11111111|11110100 */
	0x3b,0xff,0xec,	 /* 00111011|11111111|11101100 ... middle */
	0x3b,0xff,0xdc,	 /* 00111011|11111111|11011100 */
	0x3d,0xff,0xbc,	 /* 00111101|11111111|10111100 */
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
	0x3d,0xff,0xbc,	 /* 00111101|11111111|10111100 */
	0x3b,0xff,0xdc,	 /* 00111011|11111111|11011100 */
	0x37,0xff,0xec,	 /* 00110111|11111111|11101100 */
	0x2f,0xff,0xf4,	 /* 00101111|11111111|11110100 ... bottom */
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

	/* 0x37 '7' */
	0x3f,0xff,0xf4,	 /* 00111111|11111111|11110100 ... top */
	0x1f,0xff,0xec,	 /* 00011111|11111111|11101100 */
	0x0f,0xff,0xdc,	 /* 00001111|11111111|11011100 */
	0x07,0xff,0xbc,	 /* 00000111|11111111|10111100 */
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
	0x00,0x00,0x3c,	 /* 00000000|00000000|00111100 */
	0x00,0x00,0x1c,	 /* 00000000|00000000|00011100 */
	0x00,0x00,0x0c,	 /* 00000000|00000000|00001100 */
	0x00,0x00,0x04,	 /* 00000000|00000000|00000100 ... bottom */
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

	/* 0x38 '8' */
	0x2f,0xff,0xf4,	 /* 00101111|11111111|11110100 ... top */
	0x37,0xff,0xec,	 /* 00110111|11111111|11101100 */
	0x3b,0xff,0xdc,	 /* 00111011|11111111|11011100 */
	0x3d,0xff,0xbc,	 /* 00111101|11111111|10111100 */
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
	0x3d,0xff,0xbc,	 /* 00111101|11111111|10111100 */
	0x3b,0xff,0xdc,	 /* 00111011|11111111|11011100 ... middle */
	0x3b,0xff,0xdc,	 /* 00111011|11111111|11011100 */
	0x3d,0xff,0xbc,	 /* 00111101|11111111|10111100 */
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
	0x3d,0xff,0xbc,	 /* 00111101|11111111|10111100 */
	0x3b,0xff,0xdc,	 /* 00111011|11111111|11011100 */
	0x37,0xff,0xec,	 /* 00110111|11111111|11101100 */
	0x2f,0xff,0xf4,	 /* 00101111|11111111|11110100 ... bottom */
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

	/* 0x39 '9' */
	0x2f,0xff,0xf4,	 /* 00101111|11111111|11110100 ... top */
	0x37,0xff,0xec,	 /* 00110111|11111111|11101100 */
	0x3b,0xff,0xdc,	 /* 00111011|11111111|11011100 */
	0x3d,0xff,0xbc,	 /* 00111101|11111111|10111100 */
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
	0x3d,0xff,0xbc,	 /* 00111101|11111111|10111100 */
	0x3b,0xff,0xdc,	 /* 00111011|11111111|11011100 ... middle */
	0x37,0xff,0xdc,	 /* 00110111|11111111|11011100 */
	0x2f,0xff,0xbc,	 /* 00101111|11111111|10111100 */
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
	0x07,0xff,0xbc,	 /* 00000111|11111111|10111100 */
	0x0f,0xff,0xdc,	 /* 00001111|11111111|11011100 */
	0x1f,0xff,0xec,	 /* 00011111|11111111|11101100 */
	0x3f,0xff,0xf4,	 /* 00111111|11111111|11110100 ... bottom */
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

	/* 0x3A ':' */
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
