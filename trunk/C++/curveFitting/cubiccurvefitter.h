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
    CubicCurveFitter( const CubicSegment &segment );
    ~CubicCurveFitter( void ){}

    CubicCurveFitter& operator=( const CubicCurveFitter &curve );

    void clear( void );

    void initialize( uint32 w , uint32 h , uint32 radius );

    void addPoint( QPointF p );
    void draw( QPainter &painter );
    CurvePath& curve( void );
    QPolygonF& polyline( void ){ return this->_poliline;}

    DistanceField& field( void ){ return this->_field; }

protected:
    enum RESULT{ CORNER , SUCCESS , FAILURE , } ;

    RESULT _update( QPointF p ) ;
    bool _isCorner( QPointF p ) ;
    real _erro( void ) ;


private:
    DistanceField _field;
    CurvePath _path;
    CubicSegment _segment;
    QPolygonF _poliline;
    QPointF _continun;
    bool _G1;
    bool _NewPath;
};

#endif // CUBICCURVEFITTER_H
