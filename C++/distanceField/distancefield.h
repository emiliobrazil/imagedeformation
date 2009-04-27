#ifndef DISTANCEFIELD_H
#define DISTANCEFIELD_H

#include <iostream>

#include <QPoint>
#include <QImage>
#include <vector>

#include "primitive_types.h"
#include "primitive_const.h"

class DistanceField
{
public:
    DistanceField( void ){  }
    DistanceField( uint32 w , uint32 h , uint32 radius );
    DistanceField(const DistanceField &field);
    ~DistanceField( void ){}

    DistanceField &operator=(const DistanceField &field);
    void initialize( uint32 w , uint32 h , uint32 radius );

    inline real dx( int i , int j ){
        uint32 index = this->_index( i , j );
        if( index > this->_numberOfElements ) return INF ;
        return this->_dx[ index ];
    }
    inline real dy( int i , int j ){
        uint32 index = this->_index( i , j );
        if( index > this->_numberOfElements ) return INF ;
        return this->_dy[ index ];
    }

    real dx( real x , real y ) ;
    real dy( real x , real y ) ;

    real dx( QPointF p ){ return this->dx( (real)p.x() , (real)p.y() );}
    real dy( QPointF p ){ return this->dy( (real)p.x() , (real)p.y() );}

    inline QPointF dxdy( QPointF p ){ return QPointF( dx( p ) , dy( p ) ); }

    void putLine( QPointF a , QPointF b ) ;
    void putPoint( QPointF a ) ;

    QImage toImageRGBTest( int color = 0 );

    QImage toImageDx( void );
    QImage toImageDy( void );
    QImage toImageD( void );
    QImage toImageRGB( void );

    inline void clear( void ){
        this->_dx.clear();
        this->_dy.clear();
        this->_dx = std::vector<real> ( _numberOfElements , INF) ;
        this->_dy = std::vector<real> ( _numberOfElements , INF) ;
    }

protected:
    inline void _setDx( int i , int j , real v ){ this->_dx[ this->_index( i , j ) ] = v ; }
    inline void _setDy( int i , int j , real v ){ this->_dy[ this->_index( i , j ) ] = v ; }
    inline uint32 _index( int i , int j ){ return ( j + this->_radius )*( this->_w + (2 * this->_radius) ) + ( i + this->_radius ); }

    inline real _kBilinear( real x ){
        if (x<-1.0f) return 0.0f;
        else if (x<0.0f) return 1.0f+x;
        else if  (x<1.0f) return 1.0f-x;
        return 0.0f;
    }

private:
    uint32 _w , _h , _radius , _numberOfElements;
    std::vector<real> _dx;
    std::vector<real> _dy;
};

#endif // DISTANCEFIELD_H
