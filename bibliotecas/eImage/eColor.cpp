/*
 * eColor.cpp
 *
 *  Created on: Oct 25, 2008
 *      Author: emilio
 */

#include "eColor.h"
#include <iostream>


ColorRGB::ColorRGB( float r , float g , float b)
{
	if( r >= 0.0 && r <= 1.0 )	this-> _color[0] = r;
		else
		{
			this-> _color[0] = 0.0;
			std::cerr << "ERROR!! color value not between [0 , 1], r was set 0" << std::endl;
		}
	if( g >= 0.0 && g <= 1.0 )	this-> _color[1] = g;
		else
		{
			this->_color[1] = 0.0;
			std::cerr << "ERROR!! color value not between [0 , 1], g was set 0" << std::endl ;
		}
	if( b >= 0.0 && b <= 1.0 )	this->_color[2] = b;
		else
		{
			this-> _color[2] = 0.0;
			std::cerr << "ERROR!! color value not between [0 , 1], b was set 0" << std::endl ;
		}
}

void ColorRGB::setColor( float r , float g , float b )
{
	if( r >= 0.0 && r <= 1.0 )	this-> _color[0] = r;
		else
		{
			this-> _color[0] = 0.0;
			std::cerr << "ERROR!! color value not between [0 , 1], r was set 0" << std::endl;
		}
	if( g >= 0.0 && g <= 1.0 )	this->_color[1] = g;
		else
		{
			this->_color[1] = 0.0;
			std::cerr << "ERROR!! color value not between [0 , 1], g was set 0" << std::endl ;
		}
	if( b >= 0.0 && b <= 1.0 )	this-> _color[2] = b;
		else
		{
			this->_color[2] = 0.0;
			std::cerr << "ERROR!! color value not between [0 , 1], b was set 0" << std::endl ;
		}
}

/////////////////////////
// GREY
/////////////////////////

ColorGrey::ColorGrey( float tone )
{
	if( tone >= 0.0 && tone <= 1.0 )	this-> _tone = tone;
		else
		{
			this-> _tone = 0.0;
			std::cerr << "ERROR!! tone value not between [0 , 1], tone was set 0" << std::endl;
		}
}

void ColorGrey::setTone( float tone )
{
	if( tone >= 0.0 && tone <= 1.0 )	this-> _tone = tone;
		else
		{
			this-> _tone = 0.0;
			std::cerr << "ERROR!! tone value not between [0 , 1], tone was set 0" << std::endl;
		}
}

