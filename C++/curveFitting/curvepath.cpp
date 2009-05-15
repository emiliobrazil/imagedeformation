#include "curvepath.h"
#include "primitive_types.h"
#include <math.h>


void CurvePath::draw( QPainter &painter ,  bool drawTan , bool drawPol )
{
    for(uint32 i = 0 ; i < this->pSegment.size() ; ++i)
    {
        this->pSegment[i].draw( painter , drawTan , drawPol );
    }
}

QPointF CurvePath::tanC3last( void )
{
    uint32 d = this->pSegment.size()-1 ;
    return this->pSegment[d].tanC3();
}

QPolygonF CurvePath::getAllControlPoints( void )
{
    QPolygonF points;
    for( uint32 i  = 0 ; i < this->pSegment.size() ; ++i )
    {
        points.push_back( this->pSegment.at(i).getC0() );
        points.push_back( this->pSegment.at(i).getC1() );
        points.push_back( this->pSegment.at(i).getC2() );
        points.push_back( this->pSegment.at(i).getC3() );
    }
    return points;
}

QRectF CurvePath::getBoudingBox( void )
{
    QPolygonF tmp = this->getAllControlPoints();
    return tmp.boundingRect();
}
