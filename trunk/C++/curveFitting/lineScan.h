#ifndef LINESCAN_H
#define LINESCAN_H

#include "primitive_types.h"

#include <QImage>

void dda( QImage &image , QPointF a , QPointF b , real ddx , real ddy );

void dda( QImage &image , QPointF a , QPointF b , uint32 radius );

void pBox( QImage &image, QPointF x , uint32 radius);


#endif // LINESCAN_H
