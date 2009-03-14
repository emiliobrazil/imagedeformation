/***************************************************************************
 *   Copyright (C) 2008 by Emilio Ashton Vital Brazil   *
 *   emilio@impa.br   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <math.h>
#include <iostream>

#include "primitive_types.h"

/**
	@author Emilio Ashton Vital Brazil <emilio@impa.br>
*/
class Vector2D{
public:
    Vector2D( void ){ this->_vector[0] = 0.0 ; this->_vector[1]=0.0 ;}
    Vector2D( real x , real y ){ this->_vector[0] = x; this->_vector[1] = y; }
    Vector2D( const Vector2D &v );

    ~Vector2D( void ){}

    real x( void ) const { return this->_vector[0]; }
    real y( void ) const { return this->_vector[1]; }

    void set( real x , real y ) { this->_vector[0] = x; this->_vector[1] = y; }

    const Vector2D &operator=( const Vector2D &v ) ;

    const Vector2D operator+( const Vector2D &v ) const ;
    const Vector2D operator-( const Vector2D &v ) const;
    const Vector2D &operator+=( const Vector2D &v ) ;
    const Vector2D &operator-=( const Vector2D &v ) ;
    const Vector2D operator*( real alpha ) const;
    friend const Vector2D operator*( real alpha , const Vector2D &v ) ;

    bool operator==( const Vector2D &v ) const ;
    bool operator!=( const Vector2D &v ) const {return !(*this == v); }

    friend std::ostream &operator<<(std::ostream & outPut , const Vector2D &v );

    real dot( const Vector2D &v ) const {	return ( this->_vector[0] * v.x() + this->_vector[1] * v.y() ); }
    real normQuad( void ) const {	return this->_vector[0]*this->_vector[0] + this->_vector[1]*this->_vector[1]; }
    real norm( void ) const {	return sqrt( this->normQuad() ); }

    real cosTheta( const Vector2D &v ) const ;
    real theta( const Vector2D &v ) const ;
    real theta( void ) const ;

    void display( void );
    void display( Vector2D &O );

    std::pair<real,Vector2D> distQuadToSeg( const Vector2D S0 , const Vector2D S1 ) const ;


private:
	real _vector[2] ;
};


#endif
