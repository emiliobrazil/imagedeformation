#ifndef LINESCAN_H
#define LINESCAN_H

#include <QPainter>

void dda( QPainter &painter , QPointF a , QPointF b );

void dda( QPainter &painter , QPointF a , QPointF b , uint32 radius );


#endif // LINESCAN_H
