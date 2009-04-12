#include "cubiccurvefitter.h"
#include <math.h>
#include "primitive_const.h"

#define TOL_ERRO 1.0
#define MAX_ITERATION 100
#define N_SAMPLES 20
//#define CORNER_ANGLE (30.0/180.0)*PI
//--> Cos(60)=0.5 => ( A.dot.B < 0.5 <=> theta(A,B) > 60 )
#define CORNER_ANGLE 0.1

inline real dot( QPointF P , QPointF Q )
{
    return ( P.x()*Q.x() + P.y()*Q.y() );
}

inline real normQuad( QPointF P )
{
    return dot( P , P);
}

inline real norm( QPointF P )
{
    return sqrt( normQuad( P ) );
}



CubicCurveFitter::CubicCurveFitter( void )
{
    this->_field      = DistanceField() ;
    this->_path       = CurvePath() ;
    this->_segment    = CubicSegment() ;
    this->_poliline   = QPolygonF() ;
    this->_G1         = false;
    this->_NewPath    = true;
}

CubicCurveFitter::CubicCurveFitter( uint32 w , uint32 h , uint32 radius )
{
    this->_field.initialize(  w ,  h ,  radius );
    this->_G1 = false;
    this->_NewPath = true;
}

void CubicCurveFitter::initialize( uint32 w , uint32 h , uint32 radius )
{
    this->_field.initialize(  w ,  h ,  radius );
    this->_G1 = false;
    this->_NewPath = true;
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
        this->_field.putPoint( p );
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

        this->_field.putPoint( preview );
        this->_segment.set( preview , preview  , preview ,  preview );

        if( rslt == CORNER )
        {
            this->_G1 = false ;
            this->_corners.push_back(p);
        }
        else this->_G1 = true ;

        this->_Tan.push_back(this->_tmpTan);
        this->_Teste.push_back(this->_tmpTanPoints);
        this->_TanPoints.push_back(this->_tmpTeste);

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

    this->_field.putPoint( p );
    this->_field.putLine( previewSegment.getC3() , p );

    if( !firstTry )
    {
        QPointF median = ( this->_segment.getC3() + this->_segment.getC0() )*0.5;
        this->_segment.setC1( median );
        this->_segment.setC2( median );
    }

    uint32 nInteration = 0;
    real error = this->_erro();

    while ( ( error > TOL_ERRO ) && ( nInteration < MAX_ITERATION ) )
    {
        QPointF f1( 0 , 0 ) , f2( 0 , 0 ) ;
        real delta = 1.0/(real)N_SAMPLES;

        real t ;
        QPointF Bti ;
        real di ;

        for( uint32 i = 1 ; i < N_SAMPLES ;++i )
        {
            t = (real)i*delta;
            QPointF evalPoint =  this->_segment.eval( t ) ;
            Bti = this->_field.dxdy( evalPoint ) ;

            di = norm(Bti);
            if( Bti.x() < INF )
            {
                f1 += (t*(1.0-t)*(1.0-t)*di)*Bti;
                f2 += (t*  t    *(1.0-t)*di)*Bti;
            }
        }
        f1*= ( 6.0*delta );
        f2*= ( 6.0*delta );

        this->_segment.setC1( this->_segment.getC1() + f1 );
        this->_segment.setC2( this->_segment.getC2() + f2 );

        if(this->_G1)
        {
            QPointF tan = this->_path.tanC3last();
            QPointF P = this->_segment.tanC0();
            real normT = norm( tan ) ;
            if( normT > eps )
            {
                tan /= normT;
                P = tan * abs( dot( tan , P ) );
                this->_segment.setC1( ( P/3.0 ) + this->_segment.getC0() ) ;
            }
            else
            {
                std::cerr << "CubicCurveFitter::_update - normT < eps " << std::endl;
            }
        }
        error = this->_erro();
        ++nInteration;
    }

    if ( error < TOL_ERRO )
    {
        return SUCCESS ;
    }
    this->_segment = previewSegment ;
    return FAILURE;
}

bool CubicCurveFitter::_isCorner( QPointF p )
{
    if( this->_segment.getC3() == this->_segment.getC2() ) return false;

    QPointF tan = this->_segment.tanC3();

    QPointF pTest = p - this->_segment.getC3();


    real normP = norm( pTest ) ;
    real normT = norm( tan ) ;
    if( normP < eps || normT < eps )
    {
        std::cerr << "CubicCurveFitter::_isCorner " << normP  << " -- " << normT << std::endl;
        return false;
    }
    pTest /= normP;
    tan /= normT;

    this->_tmpTan = tan;
    this->_tmpTanPoints = pTest;
    this->_tmpTeste = p;

    real dotTP = dot( tan , pTest );

    return ( dotTP < CORNER_ANGLE );
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

        real dix = this->_field.dx( Bti ), diy = this->_field.dy( Bti) , di ;
        di = (  dix < INF )? dix*dix + diy*diy : infLocal ;
        error += di;
    }
    error/=(real)N_SAMPLES;
    return error ;
}
