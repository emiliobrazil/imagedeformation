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
        uint32 index = this->pIndex( i , j );
        if( index > this->pNumberOfElements ) return INF ;
        return this->pDx[ index ];
    }
    inline real dy( int i , int j ){
        uint32 index = this->pIndex( i , j );
        if( index > this->pNumberOfElements ) return INF ;
        return this->pDy[ index ];
    }

    real dx( real x , real y ) ;
    real dy( real x , real y ) ;

    real dx( QPointF p ){ return this->dx( (real)p.x() , (real)p.y() );}
    real dy( QPointF p ){ return this->dy( (real)p.x() , (real)p.y() );}

    inline QPointF dxdy( QPointF p ){ return QPointF( dx( p ) , dy( p ) ); }

    void putLine( QPointF a , QPointF b ) ;
    void putPoint( QPointF a ) ;

    QImage toImageDx( void );
    QImage toImageDy( void );
    QImage toImageD( void );
    QImage toImageRGB( void );
    QImage toImageRGBTest( void );

    inline void clear( void ){
        this->pDx.clear();
        this->pDy.clear();
        this->pDx = std::vector<real> ( pNumberOfElements , INF) ;
        this->pDy = std::vector<real> ( pNumberOfElements , INF) ;
    }

protected:
    inline void pSetDx( int i , int j , real v ){ this->pDx[ this->pIndex( i , j ) ] = v ; }
    inline void pSetDy( int i , int j , real v ){ this->pDy[ this->pIndex( i , j ) ] = v ; }
    inline uint32 pIndex( int i , int j ){ return ( j + this->pRadius )*( this->pW + (2 * this->pRadius) ) + ( i + this->pRadius ); }

    inline real _kBilinear( real x ){
        if (x<-1.0f) return 0.0f;
        else if (x<0.0f) return 1.0f+x;
        else if  (x<1.0f) return 1.0f-x;
        return 0.0f;
    }

private:
    uint32 pW , pH , pRadius , pNumberOfElements;
    std::vector<real> pDx;
    std::vector<real> pDy;
};

#endif // DISTANCEFIELD_H
