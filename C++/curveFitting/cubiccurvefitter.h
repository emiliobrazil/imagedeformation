#ifndef CUBICCURVEFITTER_H
#define CUBICCURVEFITTER_H

#include <QPolygonF>

#include "cubicsegment.h"
#include "curvepath.h"
#include "distancefield.h"

class CubicCurveFitter
{
public:
    CubicCurveFitter( void );
    CubicCurveFitter( uint32 w , uint32 h , uint32 radius );

    void addPoint( QPointF p );
    void draw( QPainter &painter );
    CurvePath curve( void );

protected:
    enum _results{ CORNER , SUCCESS , FAILURE } ;

    _results _update( QPointF p ) ;
    bool _testeCorner( QPointF p ) ;
    real _erro( void ) ;


private:
    DistanceField _field;
    CurvePath _path;
    CubicSegment _segment;
    QPolygonF _poliline;
    QPointF _continun;
    bool _G1;
    bool _NewSegment;

};

#endif // CUBICCURVEFITTER_H