#include "cubicsegment.h"

CubicSegment::CubicSegment()
{
    this->_C0 = QPointF( 0 , 0 ) ;
    this->_C1 = QPointF( 0 , 0 ) ;
    this->_C2 = QPointF( 0 , 0 ) ;
    this->_C0 = QPointF( 0 , 0 ) ;
}

CubicSegment::CubicSegment( QPointF C0 , QPointF C1 , QPointF C2 , QPointF C3 )
{
    this->_C0 = C0 ;
    this->_C1 = C1 ;
    this->_C2 = C2 ;
    this->_C0 = C3 ;
}

void CubicSegment::set( QPointF C0 , QPointF C1 , QPointF C2 , QPointF C3 )
{
    this->_C0 = C0 ;
    this->_C1 = C1 ;
    this->_C2 = C2 ;
    this->_C0 = C3 ;
}

void CubicSegment::draw( QPainter &painter )
{
    QPainterPath path;

    path.moveTo( this->_C0 );
    path.cubicTo( this->_C1 , this->_C2 , this->_C3);

    painter.drawPath(path);
}
