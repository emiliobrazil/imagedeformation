/*
 * Vector3D.cpp
 *
 *  Created on: Oct 23, 2008
 *      Author: emilio
 */

#include "Vector3D.h"
#include "primitive_const.h"

#include <GL/gl.h>

const Vector3D &Vector3D::operator=( const Vector3D &v )
{
	this -> _vector[0] = v.x() ;
	this -> _vector[1] = v.y() ;
	this -> _vector[2] = v.z() ;
	return *this;
}

const Vector3D Vector3D::operator+( const Vector3D &v ) const
{
	Vector3D s( this->_vector[0] + v.x() ,
		    this->_vector[1] + v.y() ,
		    this->_vector[2] + v.z() );
	return s;
}

const Vector3D Vector3D::operator-( const Vector3D &v ) const
{
	Vector3D s( this->_vector[0] - v.x() ,
		    this->_vector[1] - v.y() ,
		    this->_vector[2] - v.z() );
	return s;
}

const Vector3D &Vector3D::operator+=( const Vector3D &v )
{
	this-> set( this->_vector[0] + v.x() ,
		    this->_vector[1] + v.y() ,
		    this->_vector[2] + v.z() );
	return *this;
}

const Vector3D &Vector3D::operator-=( const Vector3D &v )
{
	this-> set( this->_vector[0] - v.x() ,
                    this->_vector[1] - v.y() ,
                    this->_vector[2] - v.z() );
	return *this;
}

const Vector3D Vector3D::operator*( real alpha ) const
{
	Vector3D p( this->_vector[0] * alpha ,
                    this->_vector[1] * alpha ,
                    this->_vector[2] * alpha );
	return p;
}

const Vector3D operator*( real alpha , const Vector3D &v )
{
	return v*alpha;
}

bool Vector3D::operator==( const Vector3D &v ) const
{
	return ( ( ( this->_vector[0] == v.x() )   &&
                   ( this->_vector[1] == v.y() ) ) &&
                     this->_vector[2] == v.z() ) ;
}


std::ostream &operator<<( std::ostream & outPut , const Vector3D &v )
{
	return outPut << "  ( " << v.x() << " , " << v.y() <<  " , " << v.z() << " )  " ;
}

real Vector3D::cosTheta( const Vector3D &v ) const
{
	real factor = sqrt( this->normQuad() * v.normQuad() );
	if ( factor <= zero ){
		printf("zero vector angle????\n");
		return INF ;
	}
	real cosTmp = this->dot(v) / factor;
	cosTmp = ( cosTmp <= -1 ) ? -1.0 : cosTmp;
	cosTmp = ( cosTmp >=  1 ) ?  1.0 : cosTmp;
	return cosTmp;
}

real Vector3D::theta( const Vector3D &v ) const
{
	return acos( this->cosTheta(v) );
}

Vector3D Vector3D::cross( const Vector3D &u )
{
	Vector3D c( this->y()*u.z() - u.y()*this->z() ,
			   -this->x()*u.z() + u.x()*this->z() ,
			    this->x()*u.y() - u.x()*this->y() );
	return c;
}

Vector3D Vector3D::transform ( const Vector3D &R1 , const Vector3D &R2 , const Vector3D &R3 )
{
	Vector3D t( this->dot(R1) , this->dot(R2) , this->dot(R3) );
	return t;
}

Vector3D Vector3D::scale ( const Vector3D &P )
{
	Vector3D s( this->x()*P.x() , this->y()*P.y() , this->z()*P.z() );
	return s;
}

Vector3D Vector3D::translate ( const Vector3D &S )
{
	return *this+S;
}

void Vector3D::display( void )
{
	glPushMatrix();
		glBegin(GL_LINES);
			glVertex3f( 0.0f , 0.0f , 0.0f );
			glVertex3f(  (float)(this->_vector[0]) ,
				     (float)(this->_vector[1]) ,
				     (float)(this->_vector[2]) ) ;
		glEnd();
	glPopMatrix();
}

void Vector3D::display( Vector3D &O )
{
	glPushMatrix();
		glBegin(GL_LINES);
			glVertex3f( (float)(O.x()) , (float)(O.y()) , (float)(O.z()) );
			glVertex3f( (float)(O.x()) + (float)(this->_vector[0]) ,
				    (float)(O.y()) + (float)(this->_vector[1]) ,
			            (float)(O.z()) + (float)(this->_vector[2]) ) ;
		glEnd();
	glPopMatrix();
}

