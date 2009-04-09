#ifndef CUBICSEGMENT_H
#define CUBICSEGMENT_H

#include <QPoint>
#include <QPainter>
#include "primitive_types.h"


class CubicSegment
{
public:
    CubicSegment( void );
    CubicSegment( QPointF C0 , QPointF C1 , QPointF C2 , QPointF C3 );
    CubicSegment( const CubicSegment &segment );
    ~CubicSegment( void ){}

    CubicSegment& operator=( const CubicSegment &segment );

    void set( QPointF C0 , QPointF C1 , QPointF C2 , QPointF C3 );

    void setC0( QPointF C0 ){ this->_C[0] = C0 ;}
    void setC1( QPointF C1 ){ this->_C[1] = C1 ;}
    void setC2( QPointF C2 ){ this->_C[2] = C2 ;}
    void setC3( QPointF C3 ){ this->_C[3] = C3 ;}

    inline QPointF eval( real t ){ return this->_C[0]*( (1.0-t)*(1.0-t)*(1.0-t) ) +
                                          this->_C[1]*(   3.0*t*(1.0-t)*(1.0-t) ) +
                                          this->_C[2]*(   3.0*t*   t   *(1.0-t) ) +
                                          this->_C[3]*(    t   *   t   *   t    ) ;}

    QPointF getC0( void ) const { return this->_C[0] ;}
    QPointF getC1( void ) const { return this->_C[1] ;}
    QPointF getC2( void ) const { return this->_C[2] ;}
    QPointF getC3( void ) const { return this->_C[3] ;}

    void draw( QPainter &painter , bool drawTan = false );

    QPointF tanC3( void );

private:
    QPointF _C[4];

};

#endif // CUBICSEGMENT_H
