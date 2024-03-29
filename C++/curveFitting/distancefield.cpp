#include "distancefield.h"
#include <math.h>

#define ROUND(a) ( (int)( a + 0.5 ) )
#define ABS(a)   ( (a >= 0 ) ? a : -a  )
#define INF_LOCAL INF


DistanceField::DistanceField( uint32 w , uint32 h , uint32 radius )
{
    this->pW = w;
    this->pH = h;
    this->pRadius = radius;
    this->pNumberOfElements = (w+2*radius)*(h+2*radius);
    this->pDx = std::vector<real> ( this->pNumberOfElements , INF_LOCAL);
    this->pDy = std::vector<real> ( this->pNumberOfElements , INF_LOCAL);
}

DistanceField::DistanceField(const DistanceField &field)
{
    (*this) = field;
}

void DistanceField::initialize( uint32 w , uint32 h , uint32 radius )
{
    this->pW = w;
    this->pH = h;
    this->pRadius = radius;
    this->pNumberOfElements = (w+2*radius)*(h+2*radius);
    this->pDx = std::vector<real> ( this->pNumberOfElements , INF_LOCAL);
    this->pDy = std::vector<real> ( this->pNumberOfElements , INF_LOCAL);
}

DistanceField &DistanceField::operator=(const DistanceField &field)
{
    this->pDx = field.pDx;
    this->pDy = field.pDy;
    this->pW = field.pW;
    this->pH = field.pH;
    this->pRadius =  field.pRadius;
    this->pNumberOfElements = field.pNumberOfElements;

    return (*this);
}

real DistanceField::dx( real x , real y )
{
    int x1 = (int)floor(x)   , x2 = x1 + 1 ;
    int y1 = (int)floor(y)   , y2 = y1 + 1 ;

    real tmpV, tmpH;
    real valueTmp , value = 0 ;

    valueTmp = this->dx( x1 , y1 );
    if( valueTmp == INF_LOCAL ) return INF_LOCAL;
    tmpV = this->_kBilinear(x-x1) ;
    tmpH = this->_kBilinear(y-y1) ;
    value += valueTmp*(tmpV*tmpH) ;

    valueTmp = this->dx( x1 , y2 );
    if( valueTmp == INF_LOCAL ) return INF_LOCAL;
    tmpV = this->_kBilinear(x-x1) ;
    tmpH = this->_kBilinear(y-y2) ;
    value += valueTmp*(tmpV*tmpH) ;

    valueTmp = this->dx( x2 , y1 );
    if( valueTmp == INF_LOCAL ) return INF_LOCAL;
    tmpV = this->_kBilinear(x-x2) ;
    tmpH = this->_kBilinear(y-y1) ;
    value += valueTmp*(tmpV*tmpH) ;

    valueTmp = this->dx( x2 , y2 );
    if( valueTmp == INF_LOCAL ) return INF_LOCAL;
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
    if( valueTmp == INF_LOCAL ) return INF_LOCAL;
    tmpV = this->_kBilinear(x-x1) ;
    tmpH = this->_kBilinear(y-y1) ;
    value += valueTmp*(tmpV*tmpH) ;

    valueTmp = this->dy( x1 , y2 );
    if( valueTmp == INF_LOCAL ) return INF_LOCAL;
    tmpV = this->_kBilinear(x-x1) ;
    tmpH = this->_kBilinear(y-y2) ;
    value += valueTmp*(tmpV*tmpH) ;

    valueTmp = this->dy( x2 , y1 );
    if( valueTmp == INF_LOCAL ) return INF_LOCAL;
    tmpV = this->_kBilinear(x-x2) ;
    tmpH = this->_kBilinear(y-y1) ;
    value += valueTmp*(tmpV*tmpH) ;

    valueTmp = this->dy( x2 , y2 );
    if( valueTmp == INF_LOCAL ) return INF_LOCAL;
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

    hx = 2.0 * this->pRadius * ( ttx ) ;
    hy = 2.0 * this->pRadius * ( tty ) ;

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

                    if( this->dx( xij + k , yij + l ) < INF_LOCAL)
                    {
                        real tmpD = ( this->dx( xij + k , yij + l  ) * this->dx( xij + k , yij + l  ) ) +
                                    ( this->dy( xij + k , yij + l  ) * this->dy( xij + k , yij + l  ) ) ;
                        if( ( tmpD ) >  ( (tmpVx*tmpVx) + (tmpVy*tmpVy) ) )
                        {
                            this->pSetDx( xij + k , yij + l , -tmpVx ) ;
                            this->pSetDy( xij + k , yij + l , -tmpVy ) ;
                        }
                    }
                    else
                    {
                        this->pSetDx( xij + k , yij + l , -tmpVx ) ;
                        this->pSetDy( xij + k , yij + l , -tmpVy ) ;
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
    uint32 r2 = 2*this->pRadius;

    for(uint32 i = 0 ; i < r2 ; ++i )
    {
        for(uint32 j = 0 ; j < r2 ; ++j )
        {
            int ddx =  i - this->pRadius ;
            int ddy =  j - this->pRadius ;
            int xij = ROUND(a.x()) + ddx, yij = ROUND(a.y()) + ddy ;
            if( this->dx( xij , yij ) < INF_LOCAL)
            {
                real tmpDx = this->dx( xij ,yij ) , tmpDy =  this->dy( xij ,yij ) ;
                if( ( tmpDx*tmpDx + tmpDy*tmpDy ) >  ( (ddx * ddx ) + ( ddy * ddy ) ) )
                {
                    this->pSetDx( xij ,yij , -(real)ddx ) ;
                    this->pSetDy( xij ,yij , -(real)ddy ) ;
                }
            }
            else
            {
                this->pSetDx( xij ,yij , -(real)ddx ) ;
                this->pSetDy( xij ,yij , -(real)ddy ) ;
            }
        }
    }
}

QImage DistanceField::toImageDx( void )
{
    real r = (real)(this->pRadius) + 2.0 ;
    uint32 r2 = 2*this->pRadius;
    QImage image( this->pW + r2 , this->pH + r2 , QImage::Format_ARGB32 );
    real invMax = 1.0/(2.0f*r);

    for ( int i = 0 ; i < (int)this->pW ; ++i )
    {
        for ( int j = 0 ; j < (int)this->pH ; ++j )
        {
            if( this->dx( i , j) < INF_LOCAL)
            {
                int v = (int)( ( ( this->dx( i , j) + r ) *invMax)*255.0f);
                QRgb grey = qRgb( 0, 0, v );
                image.setPixel( i , j , grey );
            }
        }
    }
    return image;
}

QImage DistanceField::toImageDy( void )
{
    real r = (real)(this->pRadius) + 2.0 ;
    uint32 r2 = 2*this->pRadius;
    QImage image( this->pW + r2 , this->pH + r2 , QImage::Format_ARGB32 );
    real invMax = 1.0/(2.0f*r);

    for ( int i = 0 ; i < (int)this->pW ; ++i )
    {
        for ( int j = 0 ; j < (int)this->pH ; ++j )
        {
            if( this->dx( i , j) < INF_LOCAL)
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
    real r = (real)(this->pRadius) + 2.0 ;
    uint32 r2 = 2*this->pRadius;
    QImage image( this->pW + r2 , this->pH + r2 , QImage::Format_ARGB32 );
    real invMax = 1.0/(2*r*r);

    for ( int i = 0 ; i < (int)this->pW ; ++i )
    {
        for ( int j = 0 ; j < (int)this->pH ; ++j )
        {
            if( this->dx( i , j) < INF_LOCAL)
            {
                int v = (int)( sqrt( ( this->dx(i , j) * this->dx(i , j) + this->dy(i , j) * this->dy(i , j) ) * invMax ) * 255.0f);
                QRgb grey = qRgb( v, 0, 0 );
                image.setPixel( i , j , grey );
            }
        }
    }
    return image;
}

QImage DistanceField::toImageRGB( void )
{
    real r = (real)(this->pRadius) + 2.0 ;
    uint32 r2 = 2*this->pRadius;
    QImage image( this->pW + r2 , this->pH + r2 , QImage::Format_ARGB32 );
    real invMaxS = 1.0/(2*r*r);
    real invMax = 1.0/(2.0f*r);

    for ( int i = 0 ; i < (int)this->pW ; ++i )
    {
        for ( int j = 0 ; j < (int)this->pH ; ++j )
        {
            if( this->dx( i , j ) < INF_LOCAL)
            {
                int blue = (int)( ( ( this->dx( i , j) + r ) *invMax)*255.0f);
                int green = (int)( ( ( this->dy( i , j) + r ) *invMax)*255.0f);
                int red = (int)( sqrt( ( this->dx( i , j) * this->dx( i , j) + this->dy( i , j) * this->dy( i , j) ) *invMaxS) * 255.0f);
                QRgb color = qRgb( red, green, blue );
                image.setPixel( i , j , color );
            }
        }
    }
    return image;
}

QImage DistanceField::toImageRGBTest( void )
{
    real r = (real)(this->pRadius) + 2.0 ;
    uint32 r2 = 2*this->pRadius;
    QImage image( this->pW + r2 , this->pH + r2 , QImage::Format_ARGB32 );
    real invMaxS = 1.0/(2*r*r);
    real invMax = 1.0/(2.0f*r);

    for ( int i = 0 ; i < (int)this->pW ; ++i )
    {
        for ( int j = 0 ; j < (int)this->pH ; ++j )
        {
            if( this->dx( i , j ) < INF_LOCAL )
            {
                real u = (real)rand()/(real)RAND_MAX;
                real v = (real)rand()/(real)RAND_MAX;
                int blue = (int)( ( ( this->dx( (real)i + u , (real)j + v) + r ) *invMax)*255.0f);
                int green = (int)( ( ( this->dy((real)i + u , (real)j + v) + r ) *invMax)*255.0f);
                int red = (int)( sqrt( ( this->dx( i , j) * this->dx( i , j) + this->dy( i , j) * this->dy( i , j) ) *invMaxS) * 255.0f);
                QRgb color = qRgb( red , green , blue );
                image.setPixel( i , j , color );
            }
        }
    }
    return image;
}
