#ifndef CURVEPATH_H
#define CURVEPATH_H

#include "cubicsegment.h"
#include <vector>

class CurvePath
{
public:
    CurvePath( void ){}
    CurvePath( const CurvePath &curve ){ (*this) = curve ; }

    CurvePath &operator=( const CurvePath &curve ){ this->_segment = curve._segment; return (*this) ;}

    void addSegment( CubicSegment segment ){ this->_segment.push_back( segment );}

    QPointF tanC3last( void );

    void clear( void ) { this->_segment.clear(); }

    void draw( QPainter &painter , bool drawTan = false);

private:
    std::vector<CubicSegment> _segment;
};

#endif // CURVEPATH_H
