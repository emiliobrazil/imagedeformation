#include "cubiccurvefitter.h"

#define _MAX_ERRO_ 1
#define _MAX_ITERATION_ 10
#define _N_SAMPLES_ 50


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
    this->_NewSegment = false;
    this->_poliline.push_back( p );
    CubicCurveFitter::RESULT rslt = this->_update( p );

    if( rslt != SUCCESS )
    {
        this->_path.addSegment( this->_segment) ;
        this->_segment.set( p , p , p , p );
        this->_field.clear();
        this->_field.putPoint( p );
        if( rslt == CORNER ) this->_G1 = false;
        else this->_G1 = true;
    }
}

void CubicCurveFitter::draw( QPainter &painter )
{
    this->_path.draw(painter);
    this->_segment.draw(painter);
}

CurvePath& CubicCurveFitter::curve( void )
{
    return this->_path;
}

CubicCurveFitter::RESULT CubicCurveFitter::_update( QPointF p )
{
    if( this->_testeCorner( p ) ) return CORNER;
    QPoint preview = this->_segment.getC3();
    this->_segment.setC3(p);
    this->_segment.setC2( this->_segment.getC2() + p - preview );
    this->_field.putPoint( preview );
    this->_field.putLine( preview , p );
    uint32 nInteration = 0;
    while ( ( this->_erro() < _MAX_ERRO_ ) && ( nInteration < _MAX_ITERATION_ ) )
    {

        ++nInteration;
    }
}

bool CubicCurveFitter::_testeCorner( QPointF p )
{

}

real CubicCurveFitter::_erro( void )
{

}
