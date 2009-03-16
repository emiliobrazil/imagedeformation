#ifndef QIMAGESHOW_H
#define QIMAGESHOW_H

#include <QtGui/QWidget>
#include "pixelManipulation_qt.h"
#include "qMyLine.h"

class qImageShow : public QWidget
{
    Q_OBJECT

public:
    qImageShow(QWidget *parent = 0);
    ~qImageShow();

    void drawImage(const QImage& image);

    void drawLineA( void ){this->_drawinglineA = true ; this->_drawinglineB = false ; update();}
    void drawLineB( void ){this->_drawinglineA = false ; this->_drawinglineB = true ; update();}
    void clearLineA( void ){this->_lineA.clear(); update();}
    void clearLineB( void ){this->_lineB.clear(); update();}

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

    void keyPressEvent ( QKeyEvent * event );

    void _drawLine( QPainter &painter );

    void _drawMasks( QPainter &painter );

    void builField( void );

private:
    QPixmap _image;

    QPointF _lastPoint;
    qMyLine _lineA;
    qMyLine _lineB;
    qMyLine _lineC;
    qMyLine _lineD;

    bool _drawinglineA;
    bool _drawinglineB;

    bool _showMaskF;
    bool _showImageFinal;

    bool _showVectors;

    QImage _maskF;

    QImage _finalImage;

    vector_field _field;
};

#endif // QIMAGESHOW_H
