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
    QPointF previewC3 = this->_segment.getC3();
    QPointF previewC2 = this->_segment.getC2();
    this->_segment.setC3(p);
    this->_segment.setC2( this->_segment.getC2() + p - previewC3 );
    this->_field.putPoint( previewC3 );
    this->_field.putLine( previewC3 , p );
    uint32 nInteration = 0;
    while ( ( this->_erro() < _MAX_ERRO_ ) && ( nInteration < _MAX_ITERATION_ ) )
    {
        QPointF f1( 0 , 0 ) , f2( 0 , 0 ) ;
        for( uint32 i = 1 ; i < _N_SAMPLES_ ;++i )
        {
            real t = i/_N_SAMPLES_;
            QPointF Bti = this->_segment.eval( t ) ;
            real di = ( Bti.x()*Bti.x() + Bti.y()*Bti.y() );
            f1 += (t*(1-t)*(1-t)*di)*Bti;
            f2 += (t*  t  *(1-t)*di)*Bti;
        }
        f1*= 6.0/_N_SAMPLES_;
        f2*= 6.0/_N_SAMPLES_;
        ++nInteration;
    }
}

bool CubicCurveFitter::_testeCorner( QPointF p )
{
    return true;
}

real CubicCurveFitter::_erro( void )
{
    real error = 0.0;
    for( uint32 i = 1 ; i < _N_SAMPLES_ ;++i )
        {
            real t = i/_N_SAMPLES_;
            QPointF Bti = this->_segment.eval( t ) ;
            real di = ( Bti.x()*Bti.x() + Bti.y()*Bti.y() );
            error += di;
        }
    return error/_N_SAMPLES_;
}
