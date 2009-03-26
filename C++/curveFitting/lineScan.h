#ifndef LINESCAN_H
#define LINESCAN_H

#include <primitive_types.h>

#include <QImage>

void dda( QImage &image , QPointF a , QPointF b );

void dda( QImage &image , QPointF a , QPointF b , uint32 radius );


#endif // LINESCAN_H
