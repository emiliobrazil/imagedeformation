#include "curvepath.h"
#include "primitive_types.h"
#include <math.h>


void CurvePath::draw( QPainter &painter ,  bool drawTan , bool drawPol )
{
    for(uint32 i = 0 ; i < this->_segment.size() ; ++i)
    {
        this->_segment[i].draw( painter , drawTan , drawPol );
    }
}

QPointF CurvePath::tanC3last( void )
{
    uint32 d = this->_segment.size()-1 ;
    return this->_segment[d].tanC3();
}
