#ifndef PIXELMANIPULATION_QT_H
#define PIXELMANIPULATION_QT_H

#include <math.h>
#include <primitive_types.h>
#include <QImage>

enum interpolationKernel
{
    HAAR,
    BILINEAR,
    CUBIC
};

QRgb getValue( const QImage& image , uint32 iIndex , uint32 jIndex );
real kernelHaar( real x );
real kernelBilinear( real x );
real kernelCubic( real x );
real max( real x , real y);
QRgb pixelValue( QImage& image , QPointF P , interpolationKernel kernel =  BILINEAR );


QRgb getValue( const QImage& image , int iIndex , int jIndex )
{
    m = image.width();
    n = image.height();
    if (iIndex < 0 ) iIndex = 0;
    if (jIndex < 0 ) jIndex = 0;
    if (iIndex > m-1 ) iIndex = m;
    if (iIndex > n-1 ) iIndex = n;

    return image.pixel( i , j );
}

real kernelHaar( real x )
{
    if (x<-.5f) return 0f;
    else if (x<.5f) return 1f;
    return 0f;
}

real kernelBilinear( real x )
{
    if (x<-1f) return 0f;
    else if (x<0f) return 1+x;
    else if  (x<1f) return 1-x;
    return 0f;
}

real kernelCubic( real x )
{
    if (x<-2f) return 0;
    else if (x<-1f) return max( 4+8*x+5*x*x+x*x*x , 0f );
    else if (x< 0f) return max( 1-2*x*x-x*x*x , 0f );
    else if (x< 1f) return max( 1-2*x*x+x*x*x , 0f );
    else if (x< 2f) return max( 4-8*x+5*x*x-x*x*x , 0f );
    return 0f;
}

real max( real x , real y)
{
    return ( x > y ) ? x : y ;
}

QRgb pixelValue(QImage& image , QPointF P , interpolationKernel kernel =  BILINEAR )
{
    real x = P.x();
    real y = P.y();

    int x1 = (int)floor(x)   , x2 = (int)ceil(x);
    int x3 = (int)floor(x)-1 , x4 = (int)ceil(x) + 1 ;
    int y1 = (int)floor(x)   , y2 = (int)ceil(y);
    int y3 = (int)floor(x)-1 , y4 = (int)ceil(y) + 1 ;

    int r , g , b ;
    int vR=0 , vG=0 , vB=0;
    real tmpV,tmpH;


    QRgb colorTmp;

    switch ( kernel )
    {
        case BILINEAR:
            colorTmp = getValue( image, x1 , y1 );
            r = qRed(colorTmp);
            g = qGreen(colorTmp);
            b = qBlue(colorTmp);
            tmpV = kernelBilinear(x-x1);
            tmpH = kernelBilinear(y-y1);
            vR += r*tmpV*tmpH;
            vG += g*tmpV*tmpH;
            vB += b*tmpV*tmpH;

            colorTmp = getValue( image, x1 , y2 );
            r = qRed(colorTmp);
            g = qGreen(colorTmp);
            b = qBlue(colorTmp);
            tmpV = kernelBilinear(x-x1);
            tmpH = kernelBilinear(y-y2);
            vR += r*tmpV*tmpH;
            vG += g*tmpV*tmpH;
            vB += b*tmpV*tmpH;

            colorTmp = getValue( image, x2 , y1 );
            r = qRed(colorTmp);
            g = qGreen(colorTmp);
            b = qBlue(colorTmp);
            tmpV = kernelBilinear(x-x2);
            tmpH = kernelBilinear(y-y1);
            vR += r*tmpV*tmpH;
            vG += g*tmpV*tmpH;
            vB += b*tmpV*tmpH;

            colorTmp = getValue( image, x2 , y2 );
            r = qRed(colorTmp);
            g = qGreen(colorTmp);
            b = qBlue(colorTmp);
            tmpV = kernelBilinear(x-x2);
            tmpH = kernelBilinear(y-y2);
            vR += r*tmpV*tmpH;
            vG += g*tmpV*tmpH;
            vB += b*tmpV*tmpH;
            return QRgb( vR,  vG,  vB );
            break;
////////////////\\\\\\\\\\\\\\\\\\\
        case HAAR:
            colorTmp = getValue( image, x1 , y1 );
            r = qRed(colorTmp);
            g = qGreen(colorTmp);
            b = qBlue(colorTmp);
            tmpV = kernelHaar(x-x1);
            tmpH = kernelHaar(y-y1);
            vR += r*tmpV*tmpH;
            vG += g*tmpV*tmpH;
            vB += b*tmpV*tmpH;

            colorTmp = getValue( image, x1 , y2 );
            r = qRed(colorTmp);
            g = qGreen(colorTmp);
            b = qBlue(colorTmp);
            tmpV = kernelHaar(x-x1);
            tmpH = kernelHaar(y-y2);
            vR += r*tmpV*tmpH;
            vG += g*tmpV*tmpH;
            vB += b*tmpV*tmpH;

            colorTmp = getValue( image, x2 , y1 );
            r = qRed(colorTmp);
            g = qGreen(colorTmp);
            b = qBlue(colorTmp);
            tmpV = kernelHaar(x-x2);
            tmpH = kernelHaar(y-y1);
            vR += r*tmpV*tmpH;
            vG += g*tmpV*tmpH;
            vB += b*tmpV*tmpH;

            colorTmp = getValue( image, x2 , y2 );
            r = qRed(colorTmp);
            g = qGreen(colorTmp);
            b = qBlue(colorTmp);
            tmpV = kernelHaar(x-x2);
            tmpH = kernelHaar(y-y2);
            vR += r*tmpV*tmpH;
            vG += g*tmpV*tmpH;
            vB += b*tmpV*tmpH;
            return QRgb( vR,  vG,  vB );
            break;
 ////////////////\\\\\\\\\\\\\\\\\\\
        case CUBIC:
            // TODO
            return QRgb( vR,  vG,  vB );
            break;
        default:
            return QRgb( vR,  vG,  vB );
        }
}



#endif // PIXELMANIPULATION_QT_H
