#ifndef PIXELMANIPULATION_QT_H
#define PIXELMANIPULATION_QT_H

#include <math.h>
#include <primitive_types.h>
#include "qMyLine.h"
#include <QImage>
#include <QVector>
#include <QPolygonF>

enum interpolationKernel{ HAAR, BILINEAR, CUBIC };

QRgb getValue( const QImage& image , uint32 iIndex , uint32 jIndex );
real kernelHaar( real x );
real kernelBilinear( real x );
real kernelCubic( real x );
QRgb pixelValue(const QImage& image , QPointF P , interpolationKernel kernel =  BILINEAR );
void transformImage( const QImage& image , QImage& finalImage , const QImage& maskF , qMyLine& lineC );

real max( real x , real y){ return ( x > y ) ? x : y ; }
real mim( real x , real y){ return ( x < y ) ? x : y ; }



QRgb getValue( const QImage& image , int iIndex , int jIndex )
{
    int m = image.width();
    int n = image.height();
    if (iIndex < 0 ) iIndex = 0;
    if (jIndex < 0 ) jIndex = 0;
    if (iIndex > m-1 ) iIndex = m;
    if (jIndex > n-1 ) iIndex = n;

    return image.pixel( iIndex , jIndex );
}

real kernelHaar( real x )
{
    if ( x<-.5f ) return 0.0f;
    else if (x<.5f) return 1.0f;
    return 0.0f;
}

real kernelBilinear( real x )
{
    if (x<-1.0f) return 0.0f;
    else if (x<0.0f) return 1.0f+x;
    else if  (x<1.0f) return 1.0f-x;
    return 0.0f;
}

real kernelCubic( real x )
{
    if (x<-2.0f) return 0;
    else if (x<-1.0f) return max( 4.0f+8.0f*x+5.0f*x*x+x*x*x , 0.0f );
    else if (x< 0.0f) return max( 1.0f-2.0f*x*x-x*x*x , 0.0f );
    else if (x< 1.0f) return max( 1.0f-2.0f*x*x+x*x*x , 0.0f );
    else if (x< 2.0f) return max( 4.0f-8.0f*x+5.0f*x*x-x*x*x , 0.0f );
    return 0.0f;
}


QRgb pixelValue(const QImage& image , QPointF P , interpolationKernel kernel )
{
    real x = P.x();
    real y = P.y();

    int x1 = (int)floor(x)   , x2 = (int)ceil(x);
//    int x3 = (int)floor(x)-1 , x4 = (int)ceil(x) + 1 ;
    int y1 = (int)floor(x)   , y2 = (int)ceil(y);
//    int y3 = (int)floor(x)-1 , y4 = (int)ceil(y) + 1 ;

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
            break;
// =======================================================
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
            break;
// =======================================================
        case CUBIC:
            // TODO
            break;
        default:
            vR = 0; vG = 0; vB = 0;
        }
    return qRgb(vR,vG,vB);
}

void transformImage( const QImage& image , QImage& finalImage , const QImage& maskF , qMyLine& lineC )
{
    QPolygonF poli( lineC.toVector() );
    QRectF bBox = poli.boundingRect();
    uint32 i0, i1 , j0 , j1;
    i0 = mim( 0 , (uint32)floor( bBox.left() ) ) ;
    i1 = mim( finalImage.width() , (uint32)floor( bBox.right() ) );
    j0 = mim( 0 , (uint32)floor( bBox.top() ) ) ;
    j1 = mim( finalImage.height() , (uint32)floor( bBox.bottom() ) );

    fprintf(stderr, "i0 = %d , i1 = %d\n" , (uint32)floor( bBox.left() ) , (uint32)floor( bBox.right() ) );

    for( uint32 i = i0  ; i < i1 ; i++ )
    {
        for( uint32 j = j0 ; j < j1 ; j++ )
        {
            if( maskF.pixel( i , j ) )
            {
                finalImage.setPixel( i , j , qRgb(128, 255, 90 ) );
            }
        }
    }

}


#endif // PIXELMANIPULATION_QT_H
