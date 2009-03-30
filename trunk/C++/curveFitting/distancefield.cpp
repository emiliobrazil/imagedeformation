#include "distancefield.h"
#include <math.h>

#define ROUND(a) ( (int)( a + 0.5 ) )
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

    real ttx = hx * abnormInv;
    real tty = hy * abnormInv;

    hx = 2.0 * this->_radius * ( ttx ) ;
    hy = 2.0 * this->_radius * ( tty ) ;

    real xIncrement;
    real yIncrement;

    real ddx =  -( 0.5 * hx );
    real ddy =  -( 0.5 * hy );

    real x1 = a.x() + ddx , y1 = a.y() + ddy ;
    real x2 = b.x() + ddx , y2 = b.y() + ddy ;

    uint32 step = ( ABS( hx ) > ABS( hy ) ) ? (uint32)ABS( hx ) : (uint32)ABS( hy ) ;

    xIncrement = hx/(real)step;
    yIncrement = hy/(real)step;

    for( uint32 i = 0 ; i < step ; i++ )
    {
        real dxTMP = x2 - x1;
        real dyTMP = y2 - y1;

        uint32 stepTMP;

        real xIncrementTMP;
        real yIncrementTMP;

        real xTMP = x1 , yTMP = y1;
        real stepInvTMP = 1.0/(real)stepTMP;

        stepTMP = ( ABS( dxTMP ) > ABS( dyTMP ) ) ? (uint32)ABS( dxTMP ) : (uint32)ABS( dyTMP ) ;

        xIncrementTMP = dxTMP*stepInvTMP;
        yIncrementTMP = dyTMP*stepInvTMP;

        for( uint32 j = 0 ; j < step ; i++ )
        {
            int xij = ROUND( xTMP ) , yij = ROUND( yTMP );

            int Neighbor[2] = { 0 , 1 };
            for( uint k = 0 ; k < 2 ; ++k)
            {
                for( uint k = 0 ; k < 2 ; ++l)
                {
                    if( this->dx( xij , yij ) < INF )
                    {
                        real tmpDx = this->dx( xij + Neighbor[k] , yij + Neighbor[l]  ) , tmpDy =  this->dy( xij + Neighbor[k] , yij + Neighbor[l]  ) ;
                        if( ( tmpDx*tmpDx + tmpDx*tmpDx ) <  ( (ddx + Neighbor[k]*ttx)*(ddx + Neighbor[k]*ttx) + (ddy + Neighbor[l]*tty)*(ddy + Neighbor[l]*tty) ) )
                        {
                            this->_setDx( xij + Neighbor[k] , yij + Neighbor[l] , (ddx + Neighbor[k]*ttx) ) ;
                            this->_setDy( xij + Neighbor[k] , yij + Neighbor[l] , (ddy + Neighbor[l]*tty) ) ;
                        }
                    }
                    else
                    {
                        this->_setDx( xij + Neighbor[k] , yij + Neighbor[l] , (ddx + Neighbor[k]*ttx) ) ;
                        this->_setDy( xij + Neighbor[k] , yij + Neighbor[l] , (ddy + Neighbor[l]*tty) ) ;
                    }
                }
            }

            xTMP+=xIncrementTMP;
            yTMP+=yIncrementTMP;
        }

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
    for(uint32 i = 0 ; i < 2*this->_radius ; ++i )
    {
        for(uint32 j = 0 ; j < 2*this->_radius ; ++j )
        {
            int ddx =  i - radius ;
            int ddy =  j - radius ;
            int xij = ROUND(X.x()) + ddx, yij = ROUND(X.y()) + ddy ;
            if( this->dx( xij , yij ) < INF )
            {
                real tmpDx = this->dx( xij ,yij ) , tmpDy =  this->dy( xij ,yij ) ;
                if( ( tmpDx*tmpDx + tmpDx*tmpDx ) <  ( (ddx * ddx ) + ( ddy * ddy ) ) )
                {
                    this->_setDx( xij ,yij , ddx ) ;
                    this->_setDy( xij ,yij , ddy ) ;
                }
            }
            else
            {
                this->_setDx( xij ,yij , ddx ) ;
                this->_setDy( xij ,yij , ddy ) ;
            }
        }
    }
}

QImage DistanceField::toImageDx( void )
{
    real r = (real)(this->_radius) + 2.0 ;
    QImage image( this->_w , this->_h , QImage::Format_Mono );
    real invMax = 1.0/(real)2.0f*r;

    for ( uint32 i = 0 ; i < this->_w ; ++i )
    {
        if( this->dx( i , j) < INF )
        {
            for ( uint32 j = 0 ; j < this->_w ; ++j )
            {
                int v = (int)( ( ( this->dx( i , j) + r ) *invMax)*255.0f);
                QRgb grey = qRgb( v, v, v );
                image.setPixel( i , j , grey );
            }
        }
    }
}

QImage DistanceField::toImageDy( void )
{
    real r = (real)(this->_radius) + 2.0 ;
    QImage image( this->_w , this->_h , QImage::Format_Mono );
    real invMax = 1.0/(real)2.0f*r;

    for ( uint32 i = 0 ; i < this->_w ; ++i )
    {
        for ( uint32 j = 0 ; j < this->_w ; ++j )
        {
            if( this->dx( i , j) < INF )
            {
                int v = (int)( ( ( this->dy( i , j) + r ) *invMax)*255.0f);
                QRgb grey = qRgb( v, v, v );
                image.setPixel( i , j , grey );
            }
        }
    }
}

QImage DistanceField::toImageD( void )
{
    real r = (real)(this->_radius) + 2.0 ;
    QImage image( this->_w , this->_h , QImage::Format_Mono );
    real invMax = 1.0/(real)r*r;

    for ( uint32 i = 0 ; i < this->_w ; ++i )
    {
        for ( uint32 j = 0 ; j < this->_w ; ++j )
        {
            if( this->dx( i , j) < INF )
            {
                int v = (int)( ( ( this->dx( i , j) * this->dx( i , j) + this->dy( i , j) * this->dy( i , j) ) *invMax) * 255.0f);
                QRgb grey = qRgb( v, v, v );
                image.setPixel( i , j , grey );
            }
        }
    }
}

QImage DistanceField::toImageRGB( void )
{
    real r = (real)(this->_radius) + 2.0 ;
    QImage image( this->_w , this->_h , QImage::Format_ARGB32 );
    real invMaxS = 1.0/(real)r*r;
    real invMax = 1.0/(real)2.0f*r;

    for ( uint32 i = 0 ; i < this->_w ; ++i )
    {
        for ( uint32 j = 0 ; j < this->_w ; ++j )
        {
            if( this->dx( i , j) < INF )
            {
                int g = (int)( ( ( this->dx( i , j) * this->dx( i , j) + this->dy( i , j) * this->dy( i , j) ) *invMaxS) * 255.0f);
                int r = (int)( ( ( this->dy( i , j) + r ) *invMax)*255.0f);
                int b = (int)( ( ( this->dy( i , j) + r ) *invMax)*255.0f);

                QRgb grey = qRgb( v, v, v );
                image.setPixel( i , j , grey );
            }
        }
    }
}
