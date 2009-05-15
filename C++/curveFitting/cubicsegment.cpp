#include "cubicsegment.h"
#include <math.h>

CubicSegment::CubicSegment()
{
    this->pC[0] = QPointF( 0 , 0 ) ;
    this->pC[1] = QPointF( 0 , 0 ) ;
    this->pC[2] = QPointF( 0 , 0 ) ;
    this->pC[3] = QPointF( 0 , 0 ) ;
}

CubicSegment::CubicSegment( QPointF C0 , QPointF C1 , QPointF C2 , QPointF C3 )
{
    this->pC[0] = C0 ;
    this->pC[1] = C1 ;
    this->pC[2] = C2 ;
    this->pC[3] = C3 ;
}

CubicSegment::CubicSegment( const CubicSegment &segment )
{
        (*this) = segment;
}


void CubicSegment::set( QPointF C0 , QPointF C1 , QPointF C2 , QPointF C3 )
{
    this->pC[0] = C0 ;
    this->pC[1] = C1 ;
    this->pC[2] = C2 ;
    this->pC[3] = C3 ;
}

void CubicSegment::draw( QPainter &painter , bool drawTan , bool drawPol)
{
    QPainterPath path;

    path.moveTo( this->pC[0] );
    path.cubicTo( this->pC[1] , this->pC[2] , this->pC[3]);
    painter.drawPath(path);

    if(drawPol)
    {
        QPen oldPen = painter.pen();

        painter.setPen( QPen( QBrush( Qt::green ), 2.0f ) );
        QPolygonF tmp = this->toPolyline();
        painter.drawPolyline( tmp );
        painter.setPen( QPen( QBrush( Qt::darkGreen ), 5.0f ) );
        painter.drawPoints( tmp ) ;

        painter.setPen( oldPen );
    }

    if(drawTan)
    {
        QPen oldPen = painter.pen();

        painter.setPen( QPen( QBrush( Qt::yellow ), 2.0f ) );
        painter.drawLine( this->pC[3] , this->pC[3] + this->tanC3()/3.0 );
        painter.setPen( QPen( QBrush( Qt::darkYellow ), 1.0f ) );
        painter.drawLine( this->pC[0] , this->pC[0] + this->tanC0()/3.0 );

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
    this->pC[0] = segment.getC0();
    this->pC[1] = segment.getC1();
    this->pC[2] = segment.getC2();
    this->pC[3] = segment.getC3();

    return (*this);
}

QPolygonF CubicSegment::toPolyline( void )
{
    QPolygonF tmp ;
    for( int i = 0 ; i < 4 ; ++i )
    {
        tmp.push_back( this->pC[i] );
    }
    return tmp;
}
