/*
 * Image.h
 *
 *  Created on: Feb 18, 2009
 *      Author: emilio
 *
 */

#ifndef EIMAGE_H_
#define EIMAGE_H_


#include "eColor.h"

class eImage
{
public:
	enum COLOR_TYPE {	BITMAP,
						GREYSCALE,
						RGB ,
						RGBA
					};
public:
	eImage( unsigned int w = 512 , unsigned int h = 512 , COLOR_TYPE colorType = RGB );
	~eImage();

private:
	COLOR_TYPE _colorType;
	ColorRGB* _pixelRGB;
	ColorGrey* _alpha;
	bool* _mask;
	unsigned int _w ;
	unsigned int _h ;
};

#endif /* EIMAGE_H_ */
