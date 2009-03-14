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
#include "Vector2D.h"
#include "primitive_const.h"

#include <GL/gl.h>

Vector2D::Vector2D( const Vector2D &v )
{
	this->_vector[0] = v.x(); this->_vector[1] = v.y();
}


const Vector2D &Vector2D::operator=( const Vector2D &v )
{
  this -> _vector[0] = v.x() ; this -> _vector[1] = v.y();
  return *this;
}

const Vector2D Vector2D::operator+( const Vector2D &v ) const
{
	Vector2D s( this->_vector[0] + v.x() , this->_vector[1] + v.y() );
	return s;
}

const Vector2D Vector2D::operator-( const Vector2D &v ) const
{
  Vector2D s( this->_vector[0] - v.x() , this->_vector[1] - v.y()   );
	return s;
}

const Vector2D &Vector2D::operator+=( const Vector2D &v )
{
	this-> set( this->_vector[0] + v.x() , this->_vector[1] + v.y() );
	return *this;
}

const Vector2D &Vector2D::operator-=( const Vector2D &v )
{
	this-> set( this->_vector[0] - v.x() , this->_vector[1] - v.y() );
	return *this;
}

const Vector2D Vector2D::operator*( real alpha ) const
{
  Vector2D p( this -> _vector[0] * alpha , this -> _vector[1] * alpha );
  return p;
}

const Vector2D operator*( real alpha , const Vector2D &v )
{
  Vector2D p( v.x() * alpha , v.y() * alpha );
  return p;
}

bool Vector2D::operator==( const Vector2D &v ) const
{
	return ( this->_vector[0] == v.x() ) && ( this->_vector[1] == v.y() ) ;
}

real Vector2D::cosTheta( const Vector2D &v ) const
{

	double pn = (this->norm()) * (v.norm());

	if( pn < 2.22045E-16 ) return 0.0;
	pn = (this->dot( v )) / pn;
	return pn;
}

real Vector2D::theta( const Vector2D &v ) const
{
	return (real)acos( this->cosTheta( v ) ) ;
}

real Vector2D::theta( void ) const
{
	Vector2D e1( 1.0 , 0.0 );
	real theta = (real)acos( this->cosTheta( e1 ) ) ;
	if ( this-> _vector[1] >= 0.0) return theta ;
	theta -=  2.0f*PI ;
	return -theta;
}

std::ostream &operator<<(std::ostream & outPut , const Vector2D &v )
{
	return outPut << "  ( " << v.x() << " , " << v.y() << " )  " ;
}

void Vector2D::display( void )
{
	glPushMatrix();
		glBegin(GL_LINES);
			glVertex2f( 0.0f , 0.0f );
			glVertex2f( (float)(this->_vector[0]) , (float)(this->_vector[1]) ) ;
		glEnd();
	glPopMatrix();
}

void Vector2D::display( Vector2D &O )
{
	glPushMatrix();
		glBegin(GL_LINES);
			glVertex2f( (float)(O.x()) , (float)(O.y()) );
			glVertex2f( (float)(O.x()) + (float)(this->_vector[0]) ,
				    (float)(O.y()) + (float)(this->_vector[1]) )  ;
		glEnd();
	glPopMatrix();
}

std::pair<real,Vector2D> Vector2D::distQuadToSeg( const Vector2D a , const Vector2D b ) const
{
    real alpha , dist ;
    Vector2D p = *this ;
    Vector2D pMa = *this - a ;
    Vector2D bMa = b-a ;
    alpha = bMa.dot(pMa)/bMa.normQuad() ;
    if( alpha <= 0 )
    {
        dist = pMa.normQuad();
        std::pair<real,Vector2D> pairSolu( dist , a );
        return pairSolu;
    }
    if( alpha >= 1 )
    {
        dist = (p-b).normQuad();
        std::pair<real,Vector2D> pairSolu( dist , b );
        return pairSolu;
    }
    Vector2D pProjected = ( 1 - alpha )*a + alpha*b ;
    dist = ( p - pProjected ).normQuad();
    std::pair <real,Vector2D> pairSolu( dist , pProjected );
    return pairSolu;
}
