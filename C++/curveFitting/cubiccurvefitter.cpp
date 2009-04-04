#include "cubiccurvefitter.h"
#include <math.h>
#include <primitive_const.h>

#define _MAX_ERRO_ 1
#define _MAX_ITERATION_ 10
#define _N_SAMPLES_ 50
#define _CORNER_ANGLE_ (60.0/180.0)*PI

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

void CubicCurveFitter::initialize( uint32 w , uint32 h , uint32 radius )
{
    this->_field.initialize(  w ,  h ,  radius );
    this->_G1 = false;
    this->_NewSegment = true;
}


void CubicCurveFitter::addPoint( QPointF p )
{
    if( this->_NewSegment )
    {
        this->_segment = CubicSegment( p , p , p , p );
        this->_NewSegment = false;
        this->_poliline.push_back( p );
        return;
    }
    this->_poliline.push_back( p );
    uint32 iEnd = this->_poliline.size()-1;
    QPointF preview = this->_poliline[ iEnd - 1 ];
    CubicCurveFitter::RESULT rslt = this->_update( p );

    if( rslt != SUCCESS )
    {
        this->_path.addSegment( this->_segment) ;
        this->_segment = CubicSegment( preview , preview , preview , preview );
        this->_field.clear();
        this->_update( p ) ;
        if( rslt == CORNER ) this->_G1 = false ;
        else this->_G1 = true ;
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
    if( this->_isCorner( p ) ) return CORNER;

    std::cerr << "CubicCurveFitter::_update 01" << std::endl;

    QPointF previewC3 = this->_segment.getC3();
    QPointF previewC2 = this->_segment.getC2();
    QPointF previewC1 = this->_segment.getC1();
    QPointF previewC0 = this->_segment.getC0();

    this->_segment.setC3(p);
    this->_segment.setC2( this->_segment.getC2() + p - previewC3 );
    this->_field.putPoint( previewC3 );
    this->_field.putLine( previewC3 , p );
    uint32 nInteration = 0;
    real error = this->_erro();
    while ( ( error < _MAX_ERRO_ ) && ( nInteration < _MAX_ITERATION_ ) )
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
        if(this->_G1)
        {
            QPointF tan = this->_path.tanC3last();
            f1 = tan * ( ( tan.x()*f1.x() + tan.y()*f1.y() ) );
        }
        this->_segment.setC1( this->_segment.getC1() + f1 );
        this->_segment.setC2( this->_segment.getC2() + f2 );
        error = this->_erro();
        ++nInteration;
        if (error < _MAX_ERRO_ ) return SUCCESS ;
    }
    this->_segment.set( previewC0 , previewC1 , previewC2, previewC3 ) ;
    return FAILURE;
}

bool CubicCurveFitter::_isCorner( QPointF p )
{
    if( this->_segment.getC3() == this->_segment.getC2() ) return false;
        std::cerr << "CubicCurveFitter::_isCorner 01" << std::endl;

    QPointF tan = this->_segment.tanC3();
    QPointF pTest = p - this->_segment.getC3();
    pTest /= sqrt( pTest.x()*pTest.x() + pTest.y()*pTest.y() ) ;
    real theta = acos(tan.x()*pTest.x() + tan.y()*pTest.y()) ;
            std::cerr << "CubicCurveFitter::_isCorner 02 -- theta = " << theta << " " << _CORNER_ANGLE_ << std::endl;
    return ( theta > _CORNER_ANGLE_ );
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
