#include "lineScan.h"

#include <math.h>

#define ROUND(a) ( (uint32)( a + 0.5 ) )
#define ABS(a)   ( (a >= 0 ) ? a : -a  )


void dda( QImage &image , QPointF a , QPointF b )
{
    real dx = b.x() - a.x();
    real dy = b.y() - a.y();

    uint32 step;

    real xIncrement;
    real yIncrement;
    real x = a.x() , y = a.y();

    real stepInv = 1.0/(real)step;

    step = ( ABS( dx ) > ABS( dy ) ) ? (uint32)ABS( dx ) : (uint32)ABS( dy ) ;
    xIncrement = dx*stepInv;
    yIncrement = dy*stepInv;

    image.setPixel( ROUND(x  ) , ROUND(y  ), qRgb( 55 , 255, 0 ) );
    image.setPixel( ROUND(x-1) , ROUND(y  ), qRgb( 55 , 255, 0 ) );
    image.setPixel( ROUND(x  ) , ROUND(y-1), qRgb( 55 , 255, 0 ) );
    image.setPixel( ROUND(x-1) , ROUND(y-1), qRgb( 55 , 255, 0 ) );
    for( uint32 i = 0 ; i < step ; i++ )
    {
        x+=xIncrement;
        y+=yIncrement;
        image.setPixel( ROUND(x  ) , ROUND(y  ), qRgb( 0 , 0, 0 ) );
        image.setPixel( ROUND(x-1) , ROUND(y  ), qRgb( 0 , 0, 0 ) );
        image.setPixel( ROUND(x  ) , ROUND(y-1), qRgb( 0 , 0, 0 ) );
        image.setPixel( ROUND(x-1) , ROUND(y-1), qRgb( 0 , 0, 0 ) );
    }

}

void dda( QImage &image , QPointF a , QPointF b , uint32 radius )
{

    real hx = b.y() - a.y();
    real hy = a.x() - b.x();

    real abnormInv = 1.0/sqrt( hx*hx + hy*hy );

    hx = 2.0 * radius * ( hx * abnormInv );
    hy = 2.0 * radius * ( hy * abnormInv );

    real xIncrement;
    real yIncrement;
    real x1 = a.x() + 0.5 * hx  , y1 = a.y()  + 0.5 * hy ;
    real x2 = b.x() + 0.5 * hx  , y2 = b.y()  + 0.5 * hy ;

    uint32 step = ( ABS( hx ) > ABS( hy ) ) ? (uint32)ABS( hx ) : (uint32)ABS( hy ) ;

    xIncrement = hx/(real)step;
    yIncrement = hy/(real)step;

    fprintf( stderr ,"P1( %f , %f ); P2( %f , %f ) ; Ix = %f ; Iy = %f ; step = %d\n", x1 , y1 , x2 , y2 , xIncrement , yIncrement , step );

    dda( image , QPointF(x1,y1) , QPointF(x2,y2) );
    for( uint32 i = 0 ; i < step ; i++ )
    {
        x1+=xIncrement;
        x2+=xIncrement;
        y1+=yIncrement;
        y2+=yIncrement;
        dda( image , QPointF(x1,y1) , QPointF(x2,y2) );
    }

}
