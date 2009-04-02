#ifndef CUBICSEGMENT_H
#define CUBICSEGMENT_H

#include <QPoint>
#include <QPainter>

class CubicSegment
{
public:
    CubicSegment( void );
    CubicSegment( QPointF C0 , QPointF C1 , QPointF C2 , QPointF C3 );

    void set( QPointF C0 , QPointF C1 , QPointF C2 , QPointF C3 );

    void setC0( QPointF C0 ){ this->_C0 = C0 ;}
    void setC1( QPointF C1 ){ this->_C1 = C1 ;}
    void setC2( QPointF C2 ){ this->_C2 = C2 ;}
    void setC3( QPointF C3 ){ this->_C0 = C3 ;}

    QPointF getC0( void ){ return this->_C0 ;}
    QPointF getC1( void ){ return this->_C1 ;}
    QPointF getC2( void ){ return this->_C2 ;}
    QPointF getC3( void ){ return this->_C0  ;}

    void draw( QPainter &painter );

private:
    QPointF _C0 , _C1 , _C2 , _C3;

};

#endif // CUBICSEGMENT_H