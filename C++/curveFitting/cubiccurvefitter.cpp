#include "cubiccurvefitter.h"

CubicCurveFitter::CubicCurveFitter( void )
{
    this->_G1 = false;
    this->_NewSegment = true;
}

CubicCurveFitter::CubicCurveFitter( uint32 w , uint32 h , uint32 radius )
{
    this->_field.initialize(  w ,  h ,  radius );
    this->_G1 = false;
    this->_NewSegment = true;
}

void CubicCurveFitter::addPoint( QPointF p )
{
    if( this->_NewSegment ) this->_segment.set( p , p , p , p );
    this->_poliline.push_back( p );
    _results rslt = _update( p );

    if( rslt != SUCCESS )
    {

    }
}

void CubicCurveFitter::draw( QPainter &painter )
{

}

CurvePath CubicCurveFitter::curve( void )
{

}


//
//    _results _update( QPointF p ) ;
//    bool _testeCorner( QPointF p ) ;
//    real _erro( void ) ;
//
//
//private:
//    DistanceField _field;
//    CurvePath _path;
//    QPolygonF _poligon;
//    QPointF _continuit;
//    bool _G1;
