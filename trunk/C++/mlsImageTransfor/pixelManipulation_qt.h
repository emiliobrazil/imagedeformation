#ifndef PIXELMANIPULATION_QT_H
#define PIXELMANIPULATION_QT_H

#include <math.h>

#include <primitive_types.h>
#include <Vector2D.h>
#include "qMyLine.h"

#include <mlsvf.hpp>

#include <QPainter>
#include <QImage>
#include <QVector>
#include <QPolygonF>

#include <vector>

//typedef Wendland31<real,2> kernel;
//typedef MLSVF<real,2,kernel> vector_field;
typedef Wendland31<real,2> kernel;
typedef LinearMLSVF<real,2,kernel> vector_field;


enum interpolationKernel{ HAAR, BILINEAR, CUBIC };

QRgb getValue( const QImage& image , uint32 iIndex , uint32 jIndex );
real kernelHaar( real x );
real kernelBilinear( real x );
real kernelCubic( real x );
QRgb pixelValue(const QImage& image , QPointF P , interpolationKernel kernel =  BILINEAR );
void transformImage( const QImage& image , QImage& finalImage , const std::vector< std::pair<Vector2D,Vector2D> >& vectorField );
void transformImageNormal( const QImage& image , QImage& finalImage , const std::vector< std::pair<Vector2D,Vector2D> >& vectorField, std::vector< std::pair<Vector2D,Vector2D > > jacobian );

QImage eBitMapMask( QSize imageSize ,  QVector<QPointF> points  );

real maximum( real x , real y);
real minimum( real x , real y);

Vector2D evalField( real x , real y , vector_field& field );

void normalToShade( const QImage& normalImage , QImage& finalImage );
void fromGradientToColor( QRgb& normal, real dx, real dy );


#endif // PIXELMANIPULATION_QT_H
