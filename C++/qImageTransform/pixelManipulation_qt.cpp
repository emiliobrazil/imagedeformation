#include "pixelManipulation_qt.h"

#include <iostream>

real maximum( real x , real y){ return ( x > y ) ? x : y ; }
real minimum( real x , real y){ return ( x < y ) ? x : y ; }

QImage eBitMapMask( QSize imageSize,  QVector<QPointF> points  )
{
    QImage mask( imageSize , QImage::Format_Mono ) ;
    mask.fill( Qt::black );
    if( !(imageSize.isNull()) && !points.isEmpty() )
    {
        if( points.first() != points.last() ) points.push_back( points.last() );
        QPolygonF region(points);

        QPainter painterTMP( &mask );
        painterTMP.setBrush( Qt::white );
        painterTMP.setPen( QPen( QBrush( Qt::white ), 4.0f ) );

        painterTMP.drawPolygon(region);

//        fprintf( stderr , "mask OK!\n");
    }
    return mask;
}

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
    else if (x<-1.0f) return maximum( 4.0f+8.0f*x+5.0f*x*x+x*x*x , 0.0f );
    else if (x< 0.0f) return maximum( 1.0f-2.0f*x*x-x*x*x , 0.0f );
    else if (x< 1.0f) return maximum( 1.0f-2.0f*x*x+x*x*x , 0.0f );
    else if (x< 2.0f) return maximum( 4.0f-8.0f*x+5.0f*x*x-x*x*x , 0.0f );
    return 0.0f;
}

QRgb pixelValue(const QImage& image , QPointF P , interpolationKernel kernel )
{
    real x = P.x();
    real y = P.y();

    int x1 = (int)floor(x)   , x2 = x1 + 1 ;
//    int x3 = (int)floor(x)-1 , x4 = (int)ceil(x) + 1 ;
    int y1 = (int)floor(y)   , y2 = y1 +1 ;
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
            vR += (int)( (float)r*(tmpV*tmpH) );
            vG += (int)( (float)g*(tmpV*tmpH) );
            vB += (int)( (float)b*(tmpV*tmpH) );

            colorTmp = getValue( image, x1 , y2 );
            r = qRed(colorTmp);
            g = qGreen(colorTmp);
            b = qBlue(colorTmp);
            tmpV = kernelBilinear(x-x1);
            tmpH = kernelBilinear(y-y2);
            vR += (int)( (float)r*(tmpV*tmpH) );
            vG += (int)( (float)g*(tmpV*tmpH) );
            vB += (int)( (float)b*(tmpV*tmpH) );

            colorTmp = getValue( image, x2 , y1 );
            r = qRed(colorTmp);
            g = qGreen(colorTmp);
            b = qBlue(colorTmp);
            tmpV = kernelBilinear(x-x2);
            tmpH = kernelBilinear(y-y1);
            vR += (int)( (float)r*(tmpV*tmpH) );
            vG += (int)( (float)g*(tmpV*tmpH) );
            vB += (int)( (float)b*(tmpV*tmpH) );

            colorTmp = getValue( image, x2 , y2 );
            r = qRed(colorTmp);
            g = qGreen(colorTmp);
            b = qBlue(colorTmp);
            tmpV = kernelBilinear(x-x2);
            tmpH = kernelBilinear(y-y2);
            vR += (int)( (float)r*(tmpV*tmpH) );
            vG += (int)( (float)g*(tmpV*tmpH) );
            vB += (int)( (float)b*(tmpV*tmpH) );
            break;
// =======================================================
        case HAAR:
            colorTmp = getValue( image, x1 , y1 );
            r = qRed(colorTmp);
            g = qGreen(colorTmp);
            b = qBlue(colorTmp);
            tmpV = kernelHaar(x-x1);
            tmpH = kernelHaar(y-y1);
            vR += (int)( (float)r*(tmpV*tmpH) );
            vG += (int)( (float)g*(tmpV*tmpH) );
            vB += (int)( (float)b*(tmpV*tmpH) );

            colorTmp = getValue( image, x1 , y2 );
            r = qRed(colorTmp);
            g = qGreen(colorTmp);
            b = qBlue(colorTmp);
            tmpV = kernelHaar(x-x1);
            tmpH = kernelHaar(y-y2);
            vR += (int)( (float)r*(tmpV*tmpH) );
            vG += (int)( (float)g*(tmpV*tmpH) );
            vB += (int)( (float)b*(tmpV*tmpH) );

            colorTmp = getValue( image, x2 , y1 );
            r = qRed(colorTmp);
            g = qGreen(colorTmp);
            b = qBlue(colorTmp);
            tmpV = kernelHaar(x-x2);
            tmpH = kernelHaar(y-y1);
            vR += (int)( (float)r*(tmpV*tmpH) );
            vG += (int)( (float)g*(tmpV*tmpH) );
            vB += (int)( (float)b*(tmpV*tmpH) );

            colorTmp = getValue( image, x2 , y2 );
            r = qRed(colorTmp);
            g = qGreen(colorTmp);
            b = qBlue(colorTmp);
            tmpV = kernelHaar(x-x2);
            tmpH = kernelHaar(y-y2);
            vR += (int)( (float)r*(tmpV*tmpH) );
            vG += (int)( (float)g*(tmpV*tmpH) );
            vB += (int)( (float)b*(tmpV*tmpH) );
            break;
// =======================================================
        case CUBIC:
            // TODO
            break;
        default:
            vR = 0; vG = 0; vB = 0;
        }
    QRgb color = qRgb( vR, vG, vB );
//    std::cerr << color << " " << qAlpha(color)<< " " << qRed(color)<< " "<< qGreen(color)<< " " << qBlue(color)<< " " << std::endl;

    return color;
}

void transformImage( const QImage& image , QImage& finalImage , const QImage& maskF , qMyLine& lineC , vector_field& field )
{
    QPolygonF poli( lineC.toVector() );
    QRectF bBox = poli.boundingRect();
    uint32 i0, i1 , j0 , j1;
    i0 = maximum( 0 , (uint32)floor( bBox.left() ) ) ;
    i1 = minimum( finalImage.width() , (uint32)floor( bBox.right() ) );
    j0 = maximum( 0 , (uint32)floor( bBox.top() ) ) ;
    j1 = minimum( finalImage.height() , (uint32)floor( bBox.bottom() ) );

    for( uint32 i = i0  ; i < i1 ; i++ )
    {
        for( uint32 j = j0 ; j < j1 ; j++ )
        {
            if( qGray( maskF.pixel( i , j ) ) > 0  )
            {
                Vector2D v = evalField( (float)i , (float)j , field );
                QRgb color = pixelValue( image , QPointF( (float)i + v.x()  , (float)j + v.y() ) );
                finalImage.setPixel( i , j , color ) ;
            }
        }
    }
}

Vector2D evalField( real x , real y , vector_field& field )
{
    real point[] = { x , y }, vector[2];
    field.evaluate( point , vector);
    return Vector2D( vector[0],vector[1] );
}
