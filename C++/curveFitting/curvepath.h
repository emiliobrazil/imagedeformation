#ifndef CURVEPATH_H
#define CURVEPATH_H

#include "cubicsegment.h"
#include <vector>

class CurvePath
{
public:
    CurvePath( void ){}
    CurvePath( const CurvePath &curve ){ (*this) = curve ; }

    CurvePath &operator=( const CurvePath &curve ){ this->pSegment = curve.pSegment; return (*this) ;}

    void addSegment( CubicSegment segment ){ this->pSegment.push_back( segment );}

    QPointF tanC3last( void );

    void clear( void ) { this->pSegment.clear(); }

    void draw( QPainter &painter , bool drawTan = false , bool drawPol = false);

    QPolygonF getAllControlPoints( void );

    QRectF getBoudingBox( void );

private:
    std::vector<CubicSegment> pSegment;
};

#endif // CURVEPATH_H
