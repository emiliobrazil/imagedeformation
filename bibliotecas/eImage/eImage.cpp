/*
 * Image.cpp
 *
 *  Created on: Feb 18, 2009
 *      Author: emilio
 */

#include "eImage.h"

eImage::eImage( unsigned int w , unsigned int h , COLOR_TYPE colorType )
{
	this-> _w = w;
	this-> _h = h;
	unsigned int size = h*w;
	this->_colorType = colorType;
	switch (this-> _colorType ){
	        case RGBA:
	        	this->_mask = new bool[size];
	        	this->_alpha = new ColorGrey[size];
	        	this->_pixelRGB = new ColorRGB[size];
	            break;
	        case RGB:
	        	this->_mask = new bool[size];
	        	this->_alpha = 0;
	        	this->_pixelRGB = new ColorRGB[size];
	            break;
	        case GREYSCALE:
	        	this->_mask = new bool[size];
	        	this->_alpha = new ColorGrey[size];
	        	this->_pixelRGB = 0;
	            break;
	        case BITMAP:
	        	this->_mask = new bool[size];
	        	this->_alpha = 0;
	        	this->_pixelRGB = 0;
	            break;
	            }
}

eImage::~eImage()
{
	delete[] _mask;
	delete[] _alpha;
	delete[] _mask;
}

