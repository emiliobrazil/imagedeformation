#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QWidget>
#include <QKeyEvent>
#include <QtGui>

#include <QImage>


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

};

#endif // DRAWAREA_H
