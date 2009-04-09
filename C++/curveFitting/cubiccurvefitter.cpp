#include "cubiccurvefitter.h"
#include <math.h>
#include "primitive_const.h"

#define TOL_ERRO 5.0*1e-1
#define MAX_ITERATION 50
#define N_SAMPLES 200
//#define CORNER_ANGLE (30.0/180.0)*PI
//--> Cos(60)=0.5 => ( A.dot.B < 0.5 <=> theta(A,B) > 60 )
#define CORNER_ANGLE 0.5

CubicCurveFitter::CubicCurveFitter( void )
{
    this->_field      = DistanceField() ;
    this->_path       = CurvePath() ;
    this->_segment    = CubicSegment() ;
    this->_poliline   = QPolygonF() ;
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
    this->_Tan.clear() ;
    this->_Teste.clear() ;
    this->_TanPoints.clear() ;
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
        
//        this->_field.clear();
//
        this->_segment.set( preview , preview  , preview ,  preview );
//
//        this->_field.putPoint( preview );
//        this->_field.putLine( preview , p );

        if( rslt == CORNER )
        {
            this->_G1 = false ;
            this->_corners.push_back(preview);
        }
        else this->_G1 = true ;

        CubicCurveFitter::RESULT rsltN = this->_update( p , false );
        if( rsltN != SUCCESS )
        {
            std::cerr << "CubicCurveFitter::addPoint - rslt = " << rslt << "- rsltN = " << rsltN << std::endl;
        }

    }
}

CubicCurveFitter::RESULT CubicCurveFitter::_update( QPointF p , bool firstTry )
{
    if( this->_isCorner( p ) )
    {
        if( !firstTry )
        {
            std::cerr << "CubicCurveFitter::_update -- CORNER" << std::endl;
        }
        return CORNER;
    }

    CubicSegment previewSegment = this->_segment;

    this->_segment.setC3( p );
    this->_segment.setC2( this->_segment.getC2() + ( p - previewSegment.getC3() ) );

    this->_field.putPoint( previewSegment.getC3() );
    this->_field.putLine( previewSegment.getC3() , p );

    uint32 nInteration = 0;
    real error = this->_erro();

    QPolygonF evalPointsVector;
    QPolygonF evalVector;

    while ( ( error > TOL_ERRO ) && ( nInteration < MAX_ITERATION ) )
    {
        QPointF f1( 0 , 0 ) , f2( 0 , 0 ) ;
        real delta = 1.0/(real)N_SAMPLES;

        real t ;
        QPointF Bti ;
        real di ;

        evalPointsVector.clear();
        evalVector.clear();

        for( uint32 i = 1 ; i < N_SAMPLES ;++i )
        {
            t = (real)i*delta;
            QPointF evalPoint =  this->_segment.eval( t ) ;
            Bti = this->_field.dxdy( evalPoint ) ;

            evalVector.append( Bti );
            evalPointsVector.append( evalPoint );

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

    if ( error < TOL_ERRO )
    {
        return SUCCESS ;
    }
//    if( !firstTry )
    {
        std::cerr << "CubicCurveFitter::_update - FAILURE " << std::endl;
    }
    this->_segment = previewSegment ;
    return FAILURE;
}

bool CubicCurveFitter::_isCorner( QPointF p )
{
    if( this->_segment.getC3() == this->_segment.getC2() ) return false;

    QPointF tan = this->_segment.tanC3();
    if(this->_poliline.size()-2 > 0 ) tan = p - this->_poliline[ this->_poliline.size()-2 ] ;

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

    this->_Tan.push_back(tan);
    this->_Teste.push_back(pTest);
    this->_TanPoints.push_back(this->_segment.getC3());

    real dot = tan.x()*pTest.x() + tan.y()*pTest.y();

//    std::cerr << "CubicCurveFitter::_isCorner theta = " << dot  << " //  CORNER_ANGLE = " << CORNER_ANGLE << " is corner " << ( dot < CORNER_ANGLE ) << std::endl;

    return ( dot < CORNER_ANGLE );
}




real CubicCurveFitter::_erro( void )
{
    real error = 0.0;
    real delta = 1.0/N_SAMPLES;
    real infLocal = INF*delta*0.5;

    for( uint32 i = 1 ; i < N_SAMPLES ;++i )
        {
            real t = i*delta ;
            QPointF Bti = this->_segment.eval( t ) ;

            real dix = this->_field.dx( Bti ), diy = this->_field.dy( Bti) , di = infLocal ;
            if(  dix < INF ) di = dix*dix + diy*diy;
            error += di;

        }
               error/=(real)N_SAMPLES;
    return error ;
}
