/*
 * ColorRGB.h
 *
 *  Created on: Oct 25, 2008
 *      Author: emilio
 */

#ifndef ECOLOR_H_
#define ECOLOR_H_

class ColorRGB {
public:
	ColorRGB( void ) {this-> _color[0] = 0 ; this-> _color[1] = 0 ; this-> _color[2] = 0 ;};
	ColorRGB( float r , float g , float b);
	virtual ~ColorRGB(){}

	void setColor( float r , float g , float b ) ;
	float r( void ) {return this-> _color[0];}
	float g( void ) {return this-> _color[1];}
	float b( void ) {return this-> _color[2];}

private:
	float _color[3];
};

/////////////////////////
// GREY
/////////////////////////

class ColorGrey{
public:
	ColorGrey( float tone = 0);
	virtual ~ColorGrey(){}

	void setTone( float tone );
	float tone(void) {return this-> _tone;}

private:
	float _tone;
};


#endif /* ECOLOR_H_ */
