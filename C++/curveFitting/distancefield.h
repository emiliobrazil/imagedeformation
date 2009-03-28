#ifndef DISTANCEFIELD_H
#define DISTANCEFIELD_H

#include <QPoint>

#include <vector>

#include <primitive_types.h>

class DistanceField
{
public:
    DistanceField( uint32 w , uint32 h , uint32 radius );
    ~DistanceField( void );

    real dx( uint32 i , uint32 j ) ;
    real dy( uint32 i , uint32 j ) ;
    real dx( real x , real y ) ;
    real dy( real x , real y ) ;

    void setDx( uint32 i , uint32 j ) ;
    void setDy( uint32 i , uint32 j ) ;

    void putLine( QPointF a , QPointF b ) ;
    void putPoint( QPointF a ) ;

    QImage toImageDx( void );
    QImage toImageDy( void );
    QImage toImageD( void );
    QImage toImageRGB( void );

    void clear( void );

private:
    std::vector<real> _dx;
    std::vector<real> _dy;

};

#endif // DISTANCEFIELD_H
