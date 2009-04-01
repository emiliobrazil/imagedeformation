#ifndef CURVEPATH_H
#define CURVEPATH_H

#include "cubicsegment.h"
#include <vector>

class CurvePath
{
public:
    CurvePath(){}

    void addSegment( CubicSegment segment ){ this->_segment.push_back( segment );}

    void draw( QPainter &painter );

private:
    std::vector<CubicSegment> _segment;
};

#endif // CURVEPATH_H
