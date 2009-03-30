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
    std::cerr << "initialize { normal } _numberOfElements = " << this->_numberOfElements << std::endl;
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

    real ddx =  -( 0.5 * hx );
    real ddy =  -( 0.5 * hy );

    real x1 = a.x() + ddx , y1 = a.y() + ddy ;
    real x2 = b.x() + ddx , y2 = b.y() + ddy ;

    uint32 step = ( ABS( hx ) > ABS( hy ) ) ? (uint32)ABS( hx ) : (uint32)ABS( hy ) ;

    real xIncrement = hx/(real)step;
    real yIncrement = hy/(real)step;

    for( uint32 i = 0 ; i < step ; i++ )
    {
        real dxTMP = x2 - x1;
        real dyTMP = y2 - y1;

        real xTMP = x1;
        real yTMP = y1;

        uint32 stepTMP = ( ABS( dxTMP ) > ABS( dyTMP ) ) ? (uint32)ABS( dxTMP ) : (uint32)ABS( dyTMP ) ;

        real stepInvTMP = 1.0/(real)stepTMP;

        real xIncrementTMP = dxTMP*stepInvTMP;
        real yIncrementTMP = dyTMP*stepInvTMP;

        for( uint32 j = 0 ; j < stepTMP ; j++ )
        {
            int xij = ROUND( xTMP ) ;
            int yij = ROUND( yTMP );

            for( int k = 0 ; k < 2 ; ++k)
            {
                for( int l = 0 ; l < 2 ; ++l)
                {
                    real tmpVx = ddx + k*ttx ;
                    real tmpVy = ddy + l*tty ;

                    if( this->dx( xij + k , yij + l ) < INF )
                    {
                        real tmpD = ( this->dx( xij + k , yij + l  ) * this->dx( xij + k , yij + l  ) ) +
                                    ( this->dy( xij + k , yij + l  ) * this->dy( xij + k , yij + l  ) ) ;
                        if( ( tmpD ) >  ( (tmpVx*tmpVx) + (tmpVy*tmpVy) ) )
                        {
                            this->_setDx( xij + k , yij + l , tmpVx ) ;
                            this->_setDy( xij + k , yij + l , tmpVy ) ;
                        }
                    }
                    else
                    {
                        this->_setDx( xij + k , yij + l , tmpVx ) ;
                        this->_setDy( xij + k , yij + l , tmpVy ) ;
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
    uint32 r2 = 2*this->_radius;

    for(uint32 i = 0 ; i < r2 ; ++i )
    {
        for(uint32 j = 0 ; j < r2 ; ++j )
        {
            int ddx =  i - this->_radius ;
            int ddy =  j - this->_radius ;
            int xij = ROUND(a.x()) + ddx, yij = ROUND(a.y()) + ddy ;
            if( this->dx( xij , yij ) < INF )
            {
                real tmpDx = this->dx( xij ,yij ) , tmpDy =  this->dy( xij ,yij ) ;
                if( ( tmpDx*tmpDx + tmpDy*tmpDy ) >  ( (ddx * ddx ) + ( ddy * ddy ) ) )
                {
                    this->_setDx( xij ,yij , (real)ddx ) ;
                    this->_setDy( xij ,yij , (real)ddy ) ;
                }
            }
            else
            {
                this->_setDx( xij ,yij , (real)ddx ) ;
                this->_setDy( xij ,yij , (real)ddy ) ;
            }
        }
    }
}

QImage DistanceField::toImageDx( void )
{
    real r = (real)(this->_radius) + 2.0 ;
    uint32 r2 = 2*this->_radius;
    QImage image( this->_w + r2 , this->_h + r2 , QImage::Format_ARGB32 );
    real invMax = 1.0/(2.0f*r);

    for ( int i = 0 ; i < (int)this->_w ; ++i )
    {
        for ( int j = 0 ; j < (int)this->_h ; ++j )
        {
            if( this->dx( i , j) < INF )
            {
                int v = (int)( ( ( this->dx( i , j) + r ) *invMax)*255.0f);
                QRgb grey = qRgb( v, 0, 0 );
                image.setPixel( i , j , grey );
            }
        }
    }
    return image;
}

QImage DistanceField::toImageDy( void )
{
    real r = (real)(this->_radius) + 2.0 ;
    uint32 r2 = 2*this->_radius;
    QImage image( this->_w + r2 , this->_h + r2 , QImage::Format_ARGB32 );
    real invMax = 1.0/(2.0f*r);

    for ( int i = 0 ; i < (int)this->_w ; ++i )
    {
        for ( int j = 0 ; j < (int)this->_h ; ++j )
        {
            if( this->dx( i , j) < INF )
            {
                int v = (int)( ( ( this->dy( i , j) + r ) *invMax)*255.0f);
                QRgb grey = qRgb( 0, v , 0 );
                image.setPixel( i , j , grey );
            }
        }
    }
    return image;
}

QImage DistanceField::toImageD( void )
{
    real r = (real)(this->_radius) + 2.0 ;
    uint32 r2 = 2*this->_radius;
    QImage image( this->_w + r2 , this->_h + r2 , QImage::Format_ARGB32 );
    real invMax = 1.0/(2*r*r);

    for ( int i = 0 ; i < (int)this->_w ; ++i )
    {
        for ( int j = 0 ; j < (int)this->_h ; ++j )
        {
            if( this->dx( i , j) < INF )
            {
                int v = (int)( sqrt( ( this->dx(i , j) * this->dx(i , j) + this->dy(i , j) * this->dy(i , j) ) * invMax ) * 255.0f);
                QRgb grey = qRgb( 0, 0, v );
                image.setPixel( i , j , grey );
            }
        }
    }
    return image;
}

QImage DistanceField::toImageRGB( void )
{
    real r = (real)(this->_radius) + 2.0 ;
    uint32 r2 = 2*this->_radius;
    QImage image( this->_w + r2 , this->_h + r2 , QImage::Format_ARGB32 );
    real invMaxS = 1.0/(2*r*r);
    real invMax = 1.0/(2.0f*r);

    for ( int i = 0 ; i < (int)this->_w ; ++i )
    {
        for ( int j = 0 ; j < (int)this->_h ; ++j )
        {
            if( this->dx( i , j ) < INF )
            {
                int red = (int)( ( ( this->dx( i , j) + r ) *invMax)*255.0f);
                int green = (int)( ( ( this->dy( i , j) + r ) *invMax)*255.0f);
                int blue = (int)( sqrt( ( this->dx( i , j) * this->dx( i , j) + this->dy( i , j) * this->dy( i , j) ) *invMaxS) * 255.0f);
                QRgb color = qRgb( red, green, blue );
                image.setPixel( i , j , color );
            }
        }
    }
    return image;
}
