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
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent ( QKeyEvent * event );

private:
    QImage _image;
    QPointF _lastPoint;
    DistanceField _distance;
    uint32 _radius;

    bool _showDistanceFieldRGB;
    bool _showDistanceFieldDx;
    bool _showDistanceFieldDy;
    bool _showDistanceFieldD;
    bool _showTan;
    bool _showPolyline;
    bool _showCurve;
    bool _showCorner;
    bool _showAngles;

    real factor;

    CubicCurveFitter _cubicCurve;
};


#endif // DRAWAREA_H