#include "lineScan.h"

#include <math.h>

#define ROUND(a) ( (uint32)( a + 0.5 ) )
#define ABS(a)   ( (a >= 0 ) ? a : -a  )


void dda( QImage &image , QPointF a , QPointF b , real ddx , real ddy )
{
    real dx = b.x() - a.x();
    real dy = b.y() - a.y();

    uint32 step;

    real xIncrement;
    real yIncrement;
    real x = a.x() , y = a.y();
    real stepInv = 1.0/(real)step;

    ddx = ( ROUND(ddx) == 0 )?  0 : ddx + 128;
    ddy = ( ROUND(ddy) == 0 )?  0 : ddy + 128;

    step = ( ABS( dx ) > ABS( dy ) ) ? (uint32)ABS( dx ) : (uint32)ABS( dy ) ;
    xIncrement = dx*stepInv;
    yIncrement = dy*stepInv;

    image.setPixel( ROUND(x  ) , ROUND(y  ), qRgb( ROUND(ddx  ) , ROUND(ddy  ) , 0 ) );
    image.setPixel( ROUND(x-1) , ROUND(y  ), qRgb( ROUND(ddx-1) , ROUND(ddy  ) , 0 ) );
    image.setPixel( ROUND(x  ) , ROUND(y-1), qRgb( ROUND(ddx  ) , ROUND(ddy-1) , 0 ) );
    image.setPixel( ROUND(x-1) , ROUND(y-1), qRgb( ROUND(ddx-1) , ROUND(ddy-1) , 0 ) );
    for( uint32 i = 0 ; i < step ; i++ )
    {
        x+=xIncrement;
        y+=yIncrement;
//        image.setPixel( ROUND(x  ) , ROUND(y  ), qRgb( ROUND(ddx  ) , ROUND(ddy  ) , 0 ) );
//        image.setPixel( ROUND(x-1) , ROUND(y  ), qRgb( ROUND(ddx-1) , ROUND(ddy  ) , 0 ) );
//        image.setPixel( ROUND(x  ) , ROUND(y-1), qRgb( ROUND(ddx  ) , ROUND(ddy-1) , 0 ) );
        image.setPixel( ROUND(x-1) , ROUND(y-1), qRgb( ROUND(ddx-1) , ROUND(ddy-1) , 0 ) );
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
    
    real ddx =  -(0.5 * hx);
    real ddy =  -(0.5 * hy);
    
//    fprintf(stderr, "%f -- %f \n" , ddx , ddy );
    
    real x1 = a.x() + ddx , y1 = a.y() + ddy ;
    real x2 = b.x() + ddx , y2 = b.y() + ddy ;

    uint32 step = ( ABS( hx ) > ABS( hy ) ) ? (uint32)ABS( hx ) : (uint32)ABS( hy ) ;

    xIncrement = hx/(real)step;
    yIncrement = hy/(real)step;

    dda( image , QPointF(x1,y1) , QPointF(x2,y2) , ddx , ddy );
    for( uint32 i = 0 ; i < step ; i++ )
    {
        x1+=xIncrement;
        x2+=xIncrement;
        y1+=yIncrement;
        y2+=yIncrement;

        ddx+=xIncrement;
        ddy+=yIncrement;
        dda( image , QPointF(x1,y1) , QPointF(x2,y2) , ddx , ddy );
    }

}

void pBox( QImage &image, QPointF X , uint32 radius)
{
    for(uint32 i = 0 ; i < 2*radius ; ++i )
    {
        for(uint32 j = 0 ; j < 2*radius ; ++j )
        {
            int ddx = 128 - radius + i;
            int ddy = 128 - radius + j;
            image.setPixel( (uint32)X.x() - radius + i , (uint32)X.y() - radius + j , qRgb( ddx  , ddy , 0  ) );
        }
    }
}
