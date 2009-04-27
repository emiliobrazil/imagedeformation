#ifndef CUBICCURVEFITTER_H
#define CUBICCURVEFITTER_H

#include <QPolygonF>

#include "cubicsegment.h"
#include "curvepath.h"
#include "distancefield.h"

class CubicCurveFitter
{
public:
    CubicCurveFitter( void );
    CubicCurveFitter( uint32 w , uint32 h , uint32 radius , real erro = 2.0 , real cornerAngle = 0.5 );
    CubicCurveFitter( const CubicSegment &segment );
    ~CubicCurveFitter( void ){}

    CubicCurveFitter& operator=( const CubicCurveFitter &curve );

    void clear( void );

    void initialize( uint32 w , uint32 h , uint32 radius , real erro = 2.0 , real cornerAngle = 0.5);

    void addPoint( QPointF p );
    void draw( QPainter &painter , bool drawTan = false , bool drawPol = false );
    CurvePath& curve( void );
    void finish(void);
    QPolygonF& polyline( void ){ return this->_poliline;}
    QPolygonF& corner( void ){ return this->_corners;}

    QPolygonF& vectorTan( void ){ return this->_Tan;}
    QPolygonF& vectorTeste( void ){ return this->_Teste;}
    QPolygonF& tanPoints( void ){ return this->_TanPoints;}

    void setErro( real erro ){ this->_erroTol = erro ;}
    real getErro( void ){ return this->_erroTol ;}
    void setCornerAngle( real cornerAngle ){ this->_cornerAngle = cornerAngle ;}
    real getCornerAngle( void ){ return this->_cornerAngle ;}

    DistanceField& field( void ){ return this->_field; }

protected:
    enum RESULT{ CORNER , SUCCESS , FAILURE , } ;

    RESULT _update( QPointF p , bool firstTry = true ) ;
    bool _isCorner( QPointF p ) ;
    real _erro( void ) ;


private:
    DistanceField _field;
    CurvePath _path;
    CubicSegment _segment;
    real _erroTol;
    uint32 _radius;
    real _cornerAngle;


    QPolygonF _poliline;
    QPolygonF _corners;
    QPointF  _tmpTan , _tmpTeste , _tmpTanPoints  ;
    QPolygonF  _Tan , _Teste , _TanPoints ;
    bool _G1;
    bool _NewPath;
};

#endif // CUBICCURVEFITTER_H
