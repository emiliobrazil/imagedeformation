#include "curvepath.h"
#include <primitive_types.h>

void CurvePath::draw( QPainter &painter )
{
    for(uint32 i = 0 ; i < this->_segment.size() ; ++i)
    {
        this->_segment[i].draw( painter );
    }
}
