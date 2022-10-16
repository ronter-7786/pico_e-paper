#include "pico_bike.h"


///////////////////
// Global variables
///////////////////

///////////////////
// Local variables
///////////////////

///////////////////
// Local functions
///////////////////

bool draw_pixel(DISPLAY_PARAMS *pDisplayParams, uint16_t _x, uint16_t _y, COLOR_INDEX _pixelColor )
{
	uint32_t	_pixelPosn;


	if ( pDisplayParams->flags & DISPLAY_FLAG_MIRROR )
	{
		_x =  pDisplayParams->width - 1 - _x;
		_y =  pDisplayParams->height - 1 - _y;
	}

	if ((_x >= pDisplayParams->width) || (_y >= pDisplayParams->height))  return false;

	
	if ( pDisplayParams->pixelDepth == 1 )
	{
		if ( pDisplayParams->flags & DISPLAY_FLAG_ROTATE_90 ) _pixelPosn = ( _x * (pDisplayParams->height/8) ) + ( _y / 8 );
		else _pixelPosn = ( _x + ( ( _y / 8 ) * pDisplayParams->width  ) );

		if ( _pixelColor == WHITE )
		{
			if ( pDisplayParams->flags & DISPLAY_FLAG_ROTATE_90 ) pDisplayParams->pFrameBuffer[_pixelPosn] |= ( 0x80 >> (_y & 0x07 ) );
			else  pDisplayParams->pFrameBuffer[_pixelPosn] |= ( 0x01 << (_y & 0x07 ) );
		}
		else
		{
			if ( pDisplayParams->flags & DISPLAY_FLAG_ROTATE_90 ) pDisplayParams->pFrameBuffer[_pixelPosn] &= ~( 0x80 >> (_y & 0x07) );
			else  pDisplayParams->pFrameBuffer[_pixelPosn] &= ~( 0x01 << (_y & 0x07) );
		}
	}
	else if ( pDisplayParams->pixelDepth == 16 )
	{
		_pixelPosn = ( _x + ( _y * pDisplayParams->width ) ) * 2;
		pDisplayParams->pFrameBuffer[_pixelPosn++] = pDisplayParams->pColorMap[_pixelColor] &0xff;	
		pDisplayParams->pFrameBuffer[_pixelPosn] = (pDisplayParams->pColorMap[_pixelColor] >>8) &0xff;	
	}

	return true;
}

bool draw_char( DISPLAY_PARAMS *pDisplayParams, uint8_t _char, uint16_t _x, uint16_t _y, COLOR_INDEX _bgColor, COLOR_INDEX _fgColor )
{
	FONT_DESC	*_pFontDesc = pDisplayParams->pFontDesc;
	uint8_t		*_pFontMap = _pFontDesc->pBitmap;		
	uint16_t	_magn = pDisplayParams->magn;
	uint16_t	_px,
				_py;
	uint8_t		_mask;

	if ( ( _char <  _pFontDesc->MinChar ) || ( _char >  _pFontDesc->MaxChar ) ) return false;

	_char -= _pFontDesc->MinChar;

	_pFontMap += _char * ( _pFontDesc->Width /8) *_pFontDesc->Height;	

	for ( uint16_t __y = 0; __y < _pFontDesc->Height; __y++ )
	{
		for ( uint16_t __x = 0; __x < _pFontDesc->Width; __x++ )
		{
			_px = _x + (__x * _magn);		// get pixel X location
			_py = _y + (__y * _magn);		// get pixel Y location
			
			if ( (__x & 0x07) == 0) _mask = 0x80;

			if (_magn == 1)
			{
				draw_pixel( pDisplayParams, _px, _py,  ( *_pFontMap & _mask)? _fgColor : _bgColor );
			}
			else
			{
				for (unsigned short mag_x = 0; mag_x < _magn; mag_x++)
				{
					for (unsigned short mag_y = 0; mag_y < _magn; mag_y++) 
					{
						draw_pixel( pDisplayParams, _px + mag_x, _py + mag_y,  ( *_pFontMap & _mask)? _fgColor : _bgColor );
					}
				}
			}

			_mask = _mask >> 1;
			if ( _mask == 0 ) _pFontMap++;
		}
	}
}



bool draw_string( DISPLAY_PARAMS *pDisplayParams, uint8_t *_pString, uint16_t _x, uint16_t _y,COLOR_INDEX _bgColor, COLOR_INDEX _fgColor )
{
	FONT_DESC	*_pFontDesc = pDisplayParams->pFontDesc;

	while ( *_pString != 0 )
	{
		draw_char( pDisplayParams, *_pString, _x, _y, _bgColor, _fgColor );
		_pString++;
		_x += ( _pFontDesc->Width * pDisplayParams->magn );
	}
}


void clear_frameBuffer( DISPLAY_PARAMS *pDisplayParams, COLOR_INDEX _colorIndex  )
{
	uint8_t		*_pFB = pDisplayParams->pFrameBuffer;

	if ( pDisplayParams->pixelDepth == 1 )
	{
		memset ( _pFB, pDisplayParams->pColorMap[_colorIndex] ,( ( pDisplayParams->width/8) * pDisplayParams->height) );
	}
	else if ( pDisplayParams->pixelDepth == 16 )
	{
		for ( uint32_t _i = 0; _i < ( pDisplayParams->height * pDisplayParams->width ); _i++ )
		{
			*_pFB++ = pDisplayParams->pColorMap[_colorIndex] &0xff;	
			*_pFB++ = (pDisplayParams->pColorMap[_colorIndex] >>8) &0xff;	
		}
	}
}


