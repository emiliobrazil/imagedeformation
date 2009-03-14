/*
 * Vector3D.h
 *
 *  Created on: Oct 23, 2008
 *      Author: emilio
 */

#ifndef VECTOR3D_H_
#define VECTOR3D_H_

#include "primitive_types.h"
#include <iostream>
#include <math.h>

class Vector3D {
public:
    Vector3D( void ){ 	this->_vector[0] = 0.0 ;
			this->_vector[1] = 0.0 ; 
			this->_vector[2] = 0.0 ; 
			}
    Vector3D( real x , real y , real z){	this->_vector[0] = x; 
						this->_vector[1] = y;
						this->_vector[2] = z; 
						}
    Vector3D( const Vector3D &v ){	this->_vector[0] = v.x();
					this->_vector[1] = v.y();
					this->_vector[2] = v.z();
					}

    ~Vector3D( void ){}

	real x( void ) const { return this->_vector[0]; }
	real y( void ) const { return this->_vector[1]; }
	real z( void ) const { return this->_vector[2]; }

	void set( real x , real y , real z) { 	this->_vector[0] = x;
						this->_vector[1] = y;
						this->_vector[2] = z;
						}

	const Vector3D &operator=( const Vector3D &v ) ;

	const Vector3D operator+( const Vector3D &v ) const ;
	const Vector3D operator-( const Vector3D &v ) const;
	const Vector3D &operator+=( const Vector3D &v ) ;
	const Vector3D &operator-=( const Vector3D &v ) ;
	const Vector3D operator*( real alpha ) const;
	friend const Vector3D operator*( real alpha , const Vector3D &v ) ;

	bool operator==( const Vector3D &v ) const ;
	bool operator!=( const Vector3D &v ) const { return !( *this == v ); }

	friend std::ostream &operator<<(std::ostream & outPut , const Vector3D &v );

	real dot( const Vector3D &v ) const {return(	this->_vector[0] * v.x() +
							this->_vector[1] * v.y() +
							this->_vector[2] * v.z() );
						}
	real normQuad( void ) const {	return 	this->_vector[0]*this->_vector[0] +
						this->_vector[1]*this->_vector[1] +
						this->_vector[2]*this->_vector[2] ;
					}
	real norm( void ) const {	return sqrt( this->normQuad() ); }

	real cosTheta( const Vector3D &v ) const ;
	real theta( const Vector3D &v ) const ;

	Vector3D cross( const Vector3D &u );
	Vector3D transform ( const Vector3D &R1 , const Vector3D &R2 , const Vector3D &R3 );
	Vector3D scale ( const Vector3D &P );
	Vector3D translate ( const Vector3D &S );

	void display( void ) ;
	void display( Vector3D &O ) ;

private:
	real _vector[3];
};

#endif /* VECTOR3D_H_ */
