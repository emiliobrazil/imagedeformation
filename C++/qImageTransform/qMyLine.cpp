/*
 * qMyLine.cpp
 *
 *  Created on: Mar 2, 2009
 *      Author: emilio
 */

#include <iostream>

#include "qMyLine.h"
#include <primitive_types.h>
#include <primitive_const.h>

qMyLine::qMyLine()
{
    this->_pointCount = 0;
    this->_points = NULL;
    this->_lineType = UNKNOWN;
    this->_markedIndex = 0;
}

qMyLine::~qMyLine()
{
    this->clear();
}

qMyLine &qMyLine::operator=( const qMyLine &rLine )
{
    if( this != &rLine)
    {
        this->clear();
        for( uint32 i = 0 ; i < rLine.pointCount() ; ++i )
        {
            this->insertPoint( rLine.at(i) );
        }
    }
    return *this;
}

void qMyLine::clear( void )
{
    if (_points != NULL) {
        delete[] _points;
        _points = NULL;
    }
    _pointCount = 0;
}

void qMyLine::insertPoint( QPointF p )
{
    if( this->_pointCount == 0 )
    {
        this->clear();
        _maxPoints = 1024;
        this-> _points = new QPointF[ _maxPoints ];
    }

    if( this->_pointCount == this->_maxPoints )
    {
        QPointF * tmp;
        this->_maxPoints += 1024;
        tmp = new QPointF[ this->_maxPoints ];
        uint32 numberOfPoints = this->_pointCount;
        for(uint32 i = 0 ; i < numberOfPoints ; ++i )
        {
            tmp[ i ] = _points[ i ] ;
        }
        this->clear();
        this->_points = tmp;
        this->_pointCount = numberOfPoints;
    }
    this->_points[ this->_pointCount ] = p ;
    ++(this->_pointCount);
}

void qMyLine::insertPoint( QPointF p , uint32 d )
{
    if( d == this->_pointCount ) this->insertPoint( p );
    else
    {
        QPointF * tmp;
        uint32 numberOfPoints = (this->_pointCount) + 1;
        tmp = new QPointF[ numberOfPoints ];
        for( uint32 i = 0 ; i < d ; ++i )
        {
            tmp[i] = this->_points[i];
        }
        tmp[d] = p ;
        for( uint32 i = d+1 ; i < numberOfPoints ; ++i )
        {
            tmp[i] = this->_points[i-1];
        }
        this->clear();
        this->_points = tmp;
        this->_pointCount = numberOfPoints;
        this->_maxPoints = this->_pointCount ;
    }
}

void qMyLine::chaikinFilter( uint16 nOfsimplify )
{

    for( uint16 n = 0 ; n < nOfsimplify ; ++n )
    {
        // make sure we do not loose any points!!
        if (this->_pointCount <= 8) return;

        QPointF * tmp;
        _maxPoints  = _pointCount ;
        tmp = new QPointF[ _maxPoints ];
        uint32 sizeTmp = 0;

        // keep the first point
        tmp[0] = _points[0];
        ++sizeTmp;

        // step over every 2 points
        for( uint32 i = 1 ; i < ( _pointCount - 2 ) ; i += 2 )
        {
            // get original points
            const QPointF p0 = this->_points[i-1];
            const QPointF p1 = this->_points[i  ];
            const QPointF p2 = this->_points[i+1];
            const QPointF p3 = this->_points[i+2];

            // calculate the original point
            real x = -0.25f*p0.x() + 0.75f*p1.x() + 0.75f*p2.x() - 0.25f*p3.x();
            real y = -0.25f*p0.y() + 0.75f*p1.y() + 0.75f*p2.y() - 0.25f*p3.y();
            QPointF Q( x , y ) ;

            // add to new curve
            tmp[ sizeTmp ] = Q;
            ++sizeTmp;
        }
        tmp[ sizeTmp ] = _points[ _pointCount-1 ];
        ++sizeTmp;

        // copy over _points
        this->clear();
        _points = tmp ;
        _pointCount = sizeTmp;
    }
}

void qMyLine::chaikinSubDivide( uint16 nOfsimplify )
{
    if (this->_pointCount == 0) return;

    for( uint16 n = 0 ; n < nOfsimplify ; ++n )
    {

        QPointF * tmp;
        _maxPoints  = 2*_pointCount + 2 ;
        tmp = new QPointF[ _maxPoints ];
        uint32 sizeTmp = 0;

        // keep the first point
        tmp[0] = _points[0];
        ++sizeTmp;

        // step over every 2 points
        for( uint32 i = 1 ; i < _pointCount ; ++i )
        {
            // get original points
            const QPointF p0 = _points[i-1];
            const QPointF p1 = _points[i  ];

            // calculate the original point
            real x = 0.75f*p0.x() + 0.25f*p1.x() ;
            real y = 0.75f*p0.y() + 0.25f*p1.y() ;
            QPointF Q( x , y ) ;

            tmp[ sizeTmp ] = Q;
            ++sizeTmp;

            x = 0.25f*p0.x() + 0.75f*p1.x() ;
            y = 0.25f*p0.y() + 0.75f*p1.y() ;
            QPointF R( x , y ) ;

            tmp[ sizeTmp ] = R;
            ++sizeTmp;
        }
        tmp[ sizeTmp ] = _points[ _pointCount-1 ];
        ++sizeTmp;

        // copy over _points
        this->clear();
        _points = tmp ;
        _pointCount = sizeTmp;
    }
}

void qMyLine::superSample( real step )
{
    if (this->_pointCount == 0) return;

    qMyLine tmpLine;
    tmpLine.insertPoint( this->_points[0]);
    for( uint16 i = 0 ; i < this-> _pointCount - 1 ; ++i )
    {
        Vector2D tmpV( this->_points[i+1].x()-this->_points[i].x() ,
                       this->_points[i+1].y()-this->_points[i].y() ) ;
        real tmpNorm = tmpV.norm() ;
//        real step = 0.5f;
        if( tmpNorm > step )
        {
            Vector2D base( this->_points[i].x() , this->_points[i].y() );
            real invNorm = 1/tmpNorm;
            Vector2D unitV( tmpV * invNorm );
            uint32 j = 1;
            while( (j*step) < ( tmpNorm - ( step*0.25 ) ) )
            {
                Vector2D newP( base + (j*step)*unitV );
                tmpLine.insertPoint( QPointF( newP.x() , newP.y() ) );
                ++j;
            }
        }
        tmpLine.insertPoint( this->_points[i+1] );
    }
    *this = tmpLine;
    tmpLine.clear();
}

void qMyLine::lineFilter( real step )
{
    if (this->_pointCount == 0) return;
    uint32 nopOld = _pointCount;
    this->superSample( step );
    this->chaikinFilter( 5 );
    if ( _pointCount < (nopOld/4) ) this->chaikinSubDivide();
}

QVector<QPointF> qMyLine::toVector( void )
{
    register unsigned int numberOfPoints = this->_pointCount;
    QVector<QPointF> points(numberOfPoints);
    for( register unsigned int i = 0 ; i < numberOfPoints ; ++i )
    {
        points[i]= this->_points[i];
    }
    return points;
}

qMyLine& qMyLine::split( uint32 index0 , uint32 index1 )
{
    qMyLine *lineTmp1;
    lineTmp1 = new qMyLine;

    if( this->_pointCount == 0 ) return *lineTmp1;

    qMyLine *lineTmp2;
    lineTmp2 = new qMyLine;

    bool isNormal = ( index0 <= index1 ) ;
    uint32 indexI =  isNormal ? index0 : index1 ;
    uint32 indexF =  isNormal ? index1 : index0 ;
    this->close();
    uint32 end = this->_pointCount - 1 ;

    if( ( indexF > end )  ) indexF = end  ;
    if( ( indexI > end )  ) indexF = end  ;

    for( uint32 i = indexF ; i < end ; i++ )
    {
        lineTmp1->insertPoint( this->at(i) );
    }
    for( uint32 i = 0 ; i <= indexI ; i++ )
    {
        lineTmp1->insertPoint( this->at(i) );
    }

    for( uint32 i = indexI ; i <= indexF ; i++ )
    {
        lineTmp2->insertPoint( this->at(i) );
    }

    if( isNormal )
    {
       *this = *lineTmp1;
        return *lineTmp2;
    }
    else
    {
        *this = *lineTmp2;
        return *lineTmp1;
    }
}

qMyLine& qMyLine::split( QPointF p0 , QPointF p1 )
{
    std::pair<uint32,QPointF> indexPoint0 = this->argDistTo( p0 );
    std::pair<uint32,QPointF> indexPoint1 = this->argDistTo( p1 );

    qMyLine *lineTmp2;
    lineTmp2 = new qMyLine;

    *lineTmp2 = this->split( indexPoint0.first , indexPoint1.first );
    QPointF P0 = indexPoint0.second;
    QPointF P1 = indexPoint1.second;
    lineTmp2->set( 0 , P0 );
    lineTmp2->insertPoint( P1 );
    this->set( 0 , P1 );
    this->insertPoint( P0 );
    return *lineTmp2;
}

qMyLine& qMyLine::join( const qMyLine& line ) const
{
    qMyLine *lineTmp;
    lineTmp = new qMyLine;

    uint32 start = 0 , end = line.pointCount();

    *lineTmp =  *this;

    if( this->_pointCount == 0 )
    {
        *lineTmp =  line;
        return  *lineTmp;
    }

    if( end == 0 ) return *lineTmp;

    while(   this->at( (this->pointCount())-1 ) == line.at( start ) ) ++start;
    while( ( this->at( 0 ) == line.at( end-1) ) && ( end > 0 ) ) --end;

    if( end < start ) return *lineTmp;

    for( uint32 i = start ; i < end ; ++i )
    {
        lineTmp->insertPoint( line.at(i) );
    }
    return *lineTmp;
}

std::pair<real,Vector2D> qMyLine::distToQuad( QPointF p0 )
{
    Vector2D P( p0.x() , p0.y() );

    std::pair<real,Vector2D> pairDistPoint;
    real distTmp = INF;
    for( uint32 i = 0 ; i < ( this->pointCount() )-1 ; ++i )
    {
        Vector2D S0( this->at(i).x() ,   this->at(i).y() );
        Vector2D S1( this->at(i+1).x() , this->at(i+1).y() );

        std::pair<real,Vector2D> pairDistPointTmp = P.distQuadToSeg( S0 , S1 );
        real distF = pairDistPointTmp.first;
        if( distF < distTmp )
        {
            distTmp = distF;
            pairDistPoint = pairDistPointTmp;
            this->_markedIndex = i;
        }
    }
    return pairDistPoint;
}

std::pair<uint32,QPointF> qMyLine::argDistTo( QPointF p0 )
{
    std::pair<real,Vector2D>    pairDistPoint = this->distToQuad( p0 );
    QPointF P( pairDistPoint.second.x() , pairDistPoint.second.y() );
    std::pair<uint32,QPointF>  pairIndexPoint( this->_markedIndex , P );
    return pairIndexPoint;
}

bool qMyLine::isClosed( void )
{
    if (this->_pointCount > 0)
    return ( this->at(0) == this->at( this->_pointCount-1 ) );
    return true;
}

void qMyLine::close( void )
{
    if( !( this->isClosed() ) ) this->insertPoint( this->at(0) );
}

void qMyLine::grow( void )
{
    uint32 indexB = this->argMaxSizeSeg();
    QPointF P;
    P = ( this->at(indexB) + this->at(indexB+1) ) * 0.5;
    this->insertPoint( P , indexB + 1 );
}

void qMyLine::grow( uint32 d)
{
    for( uint32 i = 0 ; i < d ; ++i )
    {
        this->grow();
    }
}

real qMyLine::maxSizeSeg( void )
{
    real distTmp = 0;
    for( uint32 i = 0 ; i < (this->_pointCount) - 1 ; ++i )
    {
        real distF = ( this->at(i).x() - this->at(i+1).x() )*( this->at(i).x() - this->at(i+1).x() ) +
                     ( this->at(i).y() - this->at(i+1).y() )*( this->at(i).y() - this->at(i+1).y() );
        if( distF > distTmp )
        {
            distTmp = distF;
            this->_markedIndex = i;
        }
    }
    return sqrt( distTmp );
}

uint32 qMyLine::argMaxSizeSeg( void )
{
    this->maxSizeSeg();
    return this->_markedIndex;
}

void qMyLine::reparametri( const  qMyLine& line )
{
    while( this->_pointCount > line.pointCount() )
        this->chaikinFilter( 1 );
    while( this->_pointCount < ( ( line.pointCount()*.5 ) - 2 ))
        this->chaikinSubDivide( 1 );
    uint32 count = line.pointCount() - this->pointCount();
    this->grow( count );
}
