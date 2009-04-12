#include "cubicsegment.h"
#include <math.h>

CubicSegment::CubicSegment()
{
    this->_C[0] = QPointF( 0 , 0 ) ;
    this->_C[1] = QPointF( 0 , 0 ) ;
    this->_C[2] = QPointF( 0 , 0 ) ;
    this->_C[3] = QPointF( 0 , 0 ) ;
}

CubicSegment::CubicSegment( QPointF C0 , QPointF C1 , QPointF C2 , QPointF C3 )
{
    this->_C[0] = C0 ;
    this->_C[1] = C1 ;
    this->_C[2] = C2 ;
    this->_C[3] = C3 ;
}

CubicSegment::CubicSegment( const CubicSegment &segment )
{
        (*this) = segment;
}


void CubicSegment::set( QPointF C0 , QPointF C1 , QPointF C2 , QPointF C3 )
{
    this->_C[0] = C0 ;
    this->_C[1] = C1 ;
    this->_C[2] = C2 ;
    this->_C[3] = C3 ;
}

void CubicSegment::draw( QPainter &painter , bool drawTan )
{
    QPainterPath path;

    path.moveTo( this->_C[0] );
    path.cubicTo( this->_C[1] , this->_C[2] , this->_C[3]);
    painter.drawPath(path);

    if(drawTan)
    {
        QPen oldPen = painter.pen();
        painter.setPen( QPen( QBrush( Qt::darkYellow ), 1.0f ) );
        painter.drawLine( this->_C[0] , this->_C[0] + this->tanC0() );
        painter.drawLine( this->_C[3] , this->_C[3] + this->tanC3() );
        painter.setPen( oldPen );
    }

}

QPointF CubicSegment::tanC3( void )
{
    return 3.0 * ( this->getC3() - this->getC2() );
}

QPointF CubicSegment::tanC0( void )
{
    return 3.0 * ( this->getC1() - this->getC0() );
}

CubicSegment& CubicSegment::operator=(const CubicSegment& segment)
{
    this->_C[0] = segment.getC0();
    this->_C[1] = segment.getC1();
    this->_C[2] = segment.getC2();
    this->_C[3] = segment.getC3();

    return (*this);
}