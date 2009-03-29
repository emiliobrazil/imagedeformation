#include "distancefield.h"
#include <math.h>

#define ROUND(a) ( (uint32)( a + 0.5 ) )
#define ABS(a)   ( (a >= 0 ) ? a : -a  )

DistanceField::DistanceField( uint32 w , uint32 h , uint32 radius )
{
    this->_w = w;
    this->_h = h;
    this->_radius = radius;
    this->_numberOfElements = (w+2*radius)*(h+2*radius);
    this->_dx = std::vector<real> ( this->_numberOfElements , INF );
    this->_dy = std::vector<real> ( this->_numberOfElements , INF );
}

real DistanceField::dx( real x , real y )
{
    int x1 = (int)floor(x)   , x2 = x1 + 1 ;
    int y1 = (int)floor(y)   , y2 = y1 + 1 ;

    real tmpV, tmpH;
    real valueTmp , value = 0 ;

    valueTmp = this->dx( x1 , y1 );
    tmpV = this->_kBilinear(x-x1) ;
    tmpH = this->_kBilinear(y-y1) ;
    value += valueTmp*(tmpV*tmpH) ;

    valueTmp = this->dx( x1 , y2 );
    tmpV = this->_kBilinear(x-x1) ;
    tmpH = this->_kBilinear(y-y2) ;
    value += valueTmp*(tmpV*tmpH) ;

    valueTmp = this->dx( x2 , y1 );
    tmpV = this->_kBilinear(x-x2) ;
    tmpH = this->_kBilinear(y-y1) ;
    value += valueTmp*(tmpV*tmpH) ;

    valueTmp = this->dx( x2 , y2 );
    tmpV = this->_kBilinear(x-x2) ;
    tmpH = this->_kBilinear(y-y2) ;
    value += valueTmp*(tmpV*tmpH) ;

    return value;
}

real DistanceField::dy( real x , real y )
{
    int x1 = (int)floor(x)   , x2 = x1 + 1 ;
    int y1 = (int)floor(y)   , y2 = y1 + 1 ;

    real tmpV, tmpH;
    real valueTmp , value = 0 ;

    valueTmp = this->dy( x1 , y1 );
    tmpV = this->_kBilinear(x-x1) ;
    tmpH = this->_kBilinear(y-y1) ;
    value += valueTmp*(tmpV*tmpH) ;

    valueTmp = this->dy( x1 , y2 );
    tmpV = this->_kBilinear(x-x1) ;
    tmpH = this->_kBilinear(y-y2) ;
    value += valueTmp*(tmpV*tmpH) ;

    valueTmp = this->dy( x2 , y1 );
    tmpV = this->_kBilinear(x-x2) ;
    tmpH = this->_kBilinear(y-y1) ;
    value += valueTmp*(tmpV*tmpH) ;

    valueTmp = this->dy( x2 , y2 );
    tmpV = this->_kBilinear(x-x2) ;
    tmpH = this->_kBilinear(y-y2) ;
    value += valueTmp*(tmpV*tmpH) ;

    return value;
}

void DistanceField::putLine( QPointF a , QPointF b )
{

    real hx = b.y() - a.y();
    real hy = a.x() - b.x();

    real abnormInv = 1.0/sqrt( hx*hx + hy*hy );

    hx = 2.0 * radius * ( hx * abnormInv );
    hy = 2.0 * radius * ( hy * abnormInv );

    real xIncrement;
    real yIncrement;

    real ddx =  -(0.5 * hx);
    real ddy =  -(0.5 * hy);

    real x1 = a.x() + ddx , y1 = a.y() + ddy ;
    real x2 = b.x() + ddx , y2 = b.y() + ddy ;

    uint32 step = ( ABS( hx ) > ABS( hy ) ) ? (uint32)ABS( hx ) : (uint32)ABS( hy ) ;

    xIncrement = hx/(real)step;
    yIncrement = hy/(real)step;

    for( uint32 i = 0 ; i < step ; i++ )
    {
        x1+=xIncrement;
        x2+=xIncrement;
        y1+=yIncrement;
        y2+=yIncrement;

        ddx+=xIncrement;
        ddy+=yIncrement;


    }

}

void DistanceField::putPoint( QPointF a )
{

}

QImage DistanceField::toImageDx( void )
{

}

QImage DistanceField::toImageDy( void )
{

}

QImage DistanceField::toImageD( void )
{

}

QImage DistanceField::toImageRGB( void )
{

}
