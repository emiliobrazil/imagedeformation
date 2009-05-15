#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QWidget>
#include <QKeyEvent>
#include <QtGui>

#include <QImage>

#include "distancefield.h"
#include "cubiccurvefitter.h"

class DrawArea : public QWidget
{
public:
    DrawArea(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent ( QKeyEvent * event );

private:
    QImage _image;
    QPointF _lastPoint;
    DistanceField _distance;
    uint32 _radius;

    QVector<CurvePath> _path;
    QVector<QPolygonF> _polyline;
    QVector<QPolygonF> _corner;
    QVector<QPolygonF> _tan;
    QVector<QPolygonF> _pTan;
    QVector<QPolygonF> _vTeste;



    CubicCurveFitter _cubicCurve;
    real _erroTol;


    bool _showDistanceFieldRGB;
    bool _showDistanceFieldDx;
    bool _showDistanceFieldDy;
    bool _showDistanceFieldD;
    bool _showTan;
    bool _showPol;
    bool _showDataIn;
    bool _showCurve;
    bool _showCorner;
    bool _showAngles;
    bool _showBb;

    real factor;

};


#endif // DRAWAREA_H
