/*
 * qMyLine.h
 *
 *  Created on: Mar 2, 2009
 *      Author: emilio
 */

#ifndef QMYLINE_H_
#define QMYLINE_H_

#include <QPoint>
#include <QVector>
#include <Vector2D.h>
#include "primitive_types.h"

/**
	@author Emilio Ashton Vital Brazil <emilio@impa.br>
*/
enum EvbLineType
{
	UNKNOWN ,
	EREASE ,
	CRIATE ,
	MOVE ,
};

class qMyLine{
public:
    qMyLine();
    //    qMyLine(const MyLine &rLine);

    ~qMyLine();

    qMyLine &operator=( const qMyLine &rLine ) ;

    QPointF at( uint32 i ) const { return _points[i]; }
    QPointF atBegin( void ) const { return _points[0]; }
    QPointF atEnd( void ) const { return _points[ this->_pointCount - 1 ]; }
    void set( uint32 i , QPointF point ) const { _points[i] = point; }

    void clear( void );

    QPointF* points( void ) const { return this->_points; }
    uint32   pointCount( void ) const { return this->_pointCount; }

    void insertPoint( QPointF p ) ;
    void insertPoint( QPointF p , uint32 d ) ;

    void chaikinFilter( uint16 nOfsimplify = 1 );
    void chaikinSubDivide( uint16 nOfsimplify = 1 );
    void superSample( real step = 0.5f );
    void lineFilter( real step = 0.5f );

    QVector<QPointF> toVector( void );

    qMyLine& split( uint32 index0 , uint32 index1 );
    qMyLine& split( QPointF p0 , QPointF p1 );
    qMyLine& join ( const qMyLine& ) const ;

    std::pair<real,Vector2D>  distToQuad( QPointF p0 );
    std::pair<uint32,QPointF> argDistTo( QPointF p0 );

    bool isClosed( void ) ;
    void close( void ) ;

    void grow( void ) ;
    void grow( uint32 d) ;

    real    maxSizeSeg( void );
    uint32  argMaxSizeSeg( void );

    void reparametri( const qMyLine& line);

private:
    QPointF * _points ;
    uint32 _pointCount ;
    uint32 _maxPoints ;
    EvbLineType _lineType ;
    uint32 _markedIndex ;
};

real distToSeg( QPointF , QPointF , QPointF );

#endif /* QMYLINE_H_ */
