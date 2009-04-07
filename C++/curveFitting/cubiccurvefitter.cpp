#include "cubiccurvefitter.h"
#include <math.h>
#include <primitive_const.h>

#define _TOL_ERRO_ 5.0*1e-1
#define _MAX_ITERATION_ 50
#define _N_SAMPLES_ 200
#define _CORNER_ANGLE_ (60.0/180.0)*PI

CubicCurveFitter::CubicCurveFitter( void )
{
    this->_field      = DistanceField() ;
    this->_path       = CurvePath() ;
    this->_segment    = CubicSegment() ;
    this->_poliline   = QPolygonF() ;
    this->_continun   = QPointF() ;
    this->_G1         = false;
    this->_NewPath    = true;
    this->_lostTan    = 0.0;
    this->_totalTan   = 0.0;
}

CubicCurveFitter::CubicCurveFitter( uint32 w , uint32 h , uint32 radius )
{
    this->_field.initialize(  w ,  h ,  radius );
    this->_G1 = false;
    this->_NewPath = true;
    this->_lostTan    = 0.0;
    this->_totalTan   = 0.0;
}

void CubicCurveFitter::initialize( uint32 w , uint32 h , uint32 radius )
{
    this->_field.initialize(  w ,  h ,  radius );
    this->_G1 = false;
    this->_NewPath = true;
    this->_lostTan    = 0.0;
    this->_totalTan   = 0.0;
}

CubicCurveFitter::CubicCurveFitter( const CubicSegment &segment )
{
        (*this) = segment;
}

CubicCurveFitter& CubicCurveFitter::operator=( const CubicCurveFitter &curve )
{
    this->_field      =curve._field ;
    this->_path       =curve._path ;
    this->_segment    =curve._segment ;
    this->_poliline   =curve._poliline ;
    this->_continun   =curve._continun ;
    this->_G1         =curve._G1 ;
    this->_NewPath    =curve._NewPath ;
    this->_lostTan    = 0.0;
    this->_totalTan   = 0.0;
    return (*this) ;
}


void CubicCurveFitter::clear( void )
{
    this->_field.clear() ;
    this->_path.clear() ;
    this->_poliline.clear() ;
    this->_corners.clear() ;
    this->_segment.set( QPointF( 0 ,0 ) , QPointF( 0 ,0 ) , QPointF( 0 ,0 ) , QPointF( 0 ,0 ) );
    this->_G1         = false;
    this->_NewPath    = true;
}

void CubicCurveFitter::draw( QPainter &painter ,  bool drawTan )
{
    painter.setPen( QPen( QBrush( Qt::darkBlue ), 2.0f ) );
    this->_path.draw( painter , drawTan);
    painter.setPen( QPen( QBrush( Qt::red ), 2.0f ) );
    this->_segment.draw( painter, drawTan);
}

CurvePath& CubicCurveFitter::curve( void )
{
    return this->_path;
}

void CubicCurveFitter::addPoint( QPointF p )
{
    if( this->_NewPath )
    {
        this->_segment.set( p , p , p , p );
        this->_NewPath = false;
        this->_poliline.push_back( p );
        return;
    }

    this->_poliline.push_back( p );

    uint32 iEnd = this->_poliline.size()-1;
    QPointF preview = this->_poliline[ iEnd - 1 ];

    CubicCurveFitter::RESULT rslt = this->_update( p );

    if( rslt != SUCCESS )
    {
        CubicSegment tmpSeg = this->_segment;
        this->_path.addSegment( tmpSeg ) ;
        
        this->_field.clear();
        
        this->_segment.set( preview , preview , p ,  p );

        this->_field.putPoint( preview );
        this->_field.putLine( preview , p );

        if( rslt == CORNER )
        {
            this->_G1 = false ;
            this->_corners.push_back(preview);
        }
        else this->_G1 = true ;
    }
}

CubicCurveFitter::RESULT CubicCurveFitter::_update( QPointF p )
{
    if( this->_isCorner( p ) ) return CORNER;

    CubicSegment previewSegment = this->_segment;

    this->_segment.setC3( p );
    this->_segment.setC2( this->_segment.getC2() + ( p - previewSegment.getC3() ) );

    this->_field.putPoint( previewSegment.getC3() );
    this->_field.putLine( previewSegment.getC3() , p );

    uint32 nInteration = 0;
    real error = this->_erro();

    while ( ( error > _TOL_ERRO_ ) && ( nInteration < _MAX_ITERATION_ ) )
    {
        QPointF f1( 0 , 0 ) , f2( 0 , 0 ) ;
        real delta = 1.0/(real)_N_SAMPLES_;

        real t ;
        QPointF Bti ;
        real di ;

        for( uint32 i = 1 ; i < _N_SAMPLES_ ;++i )
        {
            t = (real)i*delta;
            Bti = this->_field.dxdy( this->_segment.eval( t ) ) ;
            di = sqrt( Bti.x()*Bti.x() + Bti.y()*Bti.y() );
            if( Bti.x() < INF )
            {
                if( di > 1e3 ){
                    std::cerr << di << std::endl;
                }
                f1 += (t*(1.0-t)*(1.0-t)*di)*Bti;
                f2 += (t*  t    *(1.0-t)*di)*Bti;
            }
        }
        f1*= ( 6.0*delta );
        f2*= ( 6.0*delta );

        if(this->_G1)
        {
            QPointF tan = this->_path.tanC3last();
            real normT = sqrt( tan.x()*tan.x() + tan.y()*tan.y() ) ;
            if( normT > eps )
            {
                tan /= normT;
                f1 = tan * ( ( tan.x()*f1.x() + tan.y()*f1.y() ) );
            }
        }
        this->_segment.setC1( this->_segment.getC1() + f1 );
        this->_segment.setC2( this->_segment.getC2() + f2 );

        error = this->_erro();
        ++nInteration;
    }

    if ( error < _TOL_ERRO_ )
    {
        return SUCCESS ;
    }
    this->_segment = previewSegment ;
    return FAILURE;
}

bool CubicCurveFitter::_isCorner( QPointF p )
{
//    if( this->_segment.getC3() == this->_segment.getC2() ) return false;

    QPointF tan = this->_segment.tanC3();
    QPointF pTest = p - this->_segment.getC3();

    real normP = sqrt( pTest.x()*pTest.x() + pTest.y()*pTest.y() ) ;
    real normT = sqrt( tan.x()*tan.x() + tan.y()*tan.y() ) ;
    if( normP < eps || normT < eps )
    {
        std::cerr << "CubicCurveFitter::_isCorner" << normP  << " -- " << normT << std::endl;
        return false;
    }
    pTest /= normP;
    tan /= normT;
    real theta = acos(tan.x()*pTest.x() + tan.y()*pTest.y()) ;
            std::cerr << "CubicCurveFitter::_isCorner theta = " << theta  << " _CORNER_ANGLE_ = " << _CORNER_ANGLE_ << std::endl;

    return ( theta < _CORNER_ANGLE_ );
}




real CubicCurveFitter::_erro( void )
{
    real error = 0.0;
    real delta = 1.0/_N_SAMPLES_;
    real infLocal = INF*delta*0.5;

    for( uint32 i = 1 ; i < _N_SAMPLES_ ;++i )
        {
            real t = i*delta ;
            QPointF Bti = this->_segment.eval( t ) ;

            real dix = this->_field.dx( Bti ), diy = this->_field.dy( Bti) , di = infLocal ;
            if(  dix < INF ) di = dix*dix + diy*diy;
            error += di;

        }
               error/=(real)_N_SAMPLES_;
    return error ;
}
