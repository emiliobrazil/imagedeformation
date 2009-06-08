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
//        painterTMP.setPen( QPen( QBrush( Qt::white ), 4.0f ) );

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

real byteToReal( unsigned char c, int offset, int scale )
{
        return ( (int)c - offset ) / (real) scale;
}

unsigned char realToByte( real d, int offset, int scale, real max_value )
{
        int i = offset + (int) ( scale * ( d / max_value ) );
        if ( i >= 255 ) return 255;
        else if ( i <= 0 ) return 0;
        return (unsigned char) i;
}

void fromNormalToGradient( QRgb normal, real& dx, real& dy )
{
        real nx = byteToReal( qRed(normal), 128, 128 );
        real ny = -1 * byteToReal( qGreen(normal), 128, 128 );
        real nz = byteToReal( qBlue(normal), 128, 128 );

        real norm = sqrt( nx*nx + ny*ny + nz*nz );
        nx /= norm; ny /= norm; nz /= norm;

        dx = - nx / nz;
        dy = - ny / nz;
}

void fromGradientToNormal( QRgb& normal, real dx, real dy )
{
        real nx = -dx, ny = -dy, nz = 1;

        real norm = sqrt( nx*nx + ny*ny + nz*nz );
        nx /= norm; ny /= norm; nz /= norm;

        normal = qRgb( realToByte( nx, 128, 128, 1 ),
                       -1 * realToByte( ny, 128, 128, 1 ),
                       realToByte( nz, 128, 128, 1 ) );
}

void fromGradientToShading( QRgb& shade, real dx, real dy, real lx, real ly, real lz )
{
        real nx = -dx, ny = -dy, nz = 1;

        real norm = sqrt( nx*nx + ny*ny + nz*nz );
        nx /= norm; ny /= norm; nz /= norm;

        real d = nx * lx + ny * ly + nz * lz;
        //if ( d < 0 ) d = 0;

        shade = qRgb( realToByte( d, 0, 255, 1 ),
                       realToByte( d, 0, 255, 1 ),
                       realToByte( d, 0, 255, 1 ) );
}

void fromGradientToColor( QRgb& normal, real dx, real dy )
{
        normal = qRgb( realToByte( -1, 128, 128, 0.35 ),
                       realToByte( dy-0.3, 128, 128, 0.15),
                       realToByte( -1, 128, 128, 1 ) );
}
/*
void getJacobian( const std::vector< std::pair<Vector2D,Vector2D> >& vectorField, int i, real& dg1dx, real& dg1dy, real& dg2dx, real& dg2dy )
{
        real x = vectorField[i].first.x();
        real y = vectorField[i].first.y();

        real u = vectorField[i].second.x();
        real v = vectorField[i].second.y();

        real uy = vectorField[i+1].second.x();
        real vy = vectorField[i+1].second.y();

        dg1dy = ( x + uy ) - ( x + u );
        dg2dy = ( y + 1 + vy ) - ( y + v );

        // i+1 is wrong, which one is the neighbour on top?
        real ux = vectorField[i+1].second.x();
        real vx = vectorField[i+1].second.y();

        dg1dx = ( x + 1 + ux ) - ( x + u );
        dg2dx = ( y + vx ) - ( y + v );

        printf("%lf %lf\n", dg1dx, dg1dy);
        printf("%lf %lf\n\n", dg2dx, dg2dy);
}
*/
void transformImageNormal( const QImage& image , QImage& finalImage , const std::vector< std::pair<Vector2D,Vector2D> >& vectorField, std::vector< std::pair<Vector2D,Vector2D> > jacobian )
{
    uint32 numberOfVectors = vectorField.size();
    for ( uint32 i=0 ; i < numberOfVectors ;++i)
    {
        real x = vectorField[i].first.x();
        real y = vectorField[i].first.y();

        real u = vectorField[i].second.x();
        real v = vectorField[i].second.y();

        real dg1dx = jacobian[i].first.x()+1;
        real dg2dx = jacobian[i].first.y();

        real dg1dy = jacobian[i].second.x();
        real dg2dy = jacobian[i].second.y()+1;

        //printf("%lf %lf\n", dg1dx, dg1dy);
        //printf("%lf %lf\n\n", dg2dx, dg2dy);

        QRgb normal = pixelValue( image , QPointF( x + u  , y + v ) );

        real dx, dy;
        fromNormalToGradient( normal, dx, dy );
        //getJacobian( vectorField, i, dg1dx, dg1dy, dg2dx, dg2dy );

        //real dx2 = dx;
        //real dy2 = dy;

        real dx2 = dx * dg1dx + dy * dg2dx;
        real dy2 = dx * dg1dy + dy * dg2dy;

        //fromGradientToColor( normal, dg1dy, dg2dy );
        fromGradientToNormal( normal, dx2, dy2 );
        //fromGradientToShading( normal, dx2, dy2, 1, 0, 0 );

        finalImage.setPixel( (uint32)x , (uint32)y , normal ) ;
    }
}

void normalToShade( const QImage& normalImage , QImage& finalImage )
{
    QSize s = normalImage.size();
    for ( uint32 i=0 ; i < s.width() ;++i)
    {
        for ( uint32 j=0 ; j < s.height() ;++j)
        {
            QRgb normal =  normalImage.pixel( i , j );

            real dx, dy;
            fromNormalToGradient( normal, dx, dy );
            fromGradientToShading( normal, dx, dy, 1, 0, 0 );

            finalImage.setPixel( i , j , normal ) ;
        }
    }
}

void transformImage( const QImage& image , QImage& finalImage , const std::vector< std::pair<Vector2D,Vector2D> >& vectorField )
{
    uint32 numberOfVectors = vectorField.size();
    for ( uint32 i=0 ; i < numberOfVectors ;++i)
    {
        real x = vectorField[i].first.x();
        real y = vectorField[i].first.y();

        real u = vectorField[i].second.x();
        real v = vectorField[i].second.y();

        QRgb color = pixelValue( image , QPointF( x + u  , y + v ) );
        finalImage.setPixel( (uint32)x , (uint32)y , color ) ;
    }
}

Vector2D evalField( real x , real y , vector_field& field )
{
    real point[] = { x , y }, vector[2];
    field.evaluate( point , vector);
    return Vector2D( vector[0],vector[1] );
}
