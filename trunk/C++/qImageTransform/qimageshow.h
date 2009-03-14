#ifndef QIMAGESHOW_H
#define QIMAGESHOW_H

#include <QtGui/QWidget>
#include "qMyLine.h"
#include "maskImage_qt.h"

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
    void filterLineA( void ){this->_lineA.lineFilter(); update();}
    void filterLineB( void ){this->_lineB.lineFilter(); update();}
    void buidMaskA( void ) { this->_maskA = eBitMapMask( this->_image.size() , this->_lineA.toVector() );  update(); }
    void buidMaskB( void ) { this->_maskB = eBitMapMask( this->_image.size() , this->_lineB.toVector() );  update(); }
    void changeShowMaskA( bool state ){ this->_showMaskA = state ;  update();}
    void changeShowMaskB( bool state ){ this->_showMaskB = state ;  update();}
    void changeShowMaskA( void ){ this->_showMaskA = !(this->_showMaskA);  update();}
    void changeShowMaskB( void ){ this->_showMaskB = !(this->_showMaskB);  update();}
    bool getShowMaskA( void ){ return this->_showMaskA ; }
    bool getShowMaskB( void ){ return this->_showMaskB ; }

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

    void keyPressEvent ( QKeyEvent * event );

    void _drawLine( QPainter &painter );

    void _drawMasks( QPainter &painter );

private:
    QPixmap _image;

    QPointF _lastPoint;
    qMyLine _lineA;
    qMyLine _lineB;
    qMyLine _lineC;
    qMyLine _lineD;

    bool _drawinglineA;
    bool _drawinglineB;
    bool _showMaskA;
    bool _showMaskB;
    bool _showMaskF;

    bool _showVectors;

    QImage _maskA;
    QImage _maskB;

    QImage _maskF;

    QPointF _pointTesteA;
    QPointF _pointTesteB;

};

#endif // QIMAGESHOW_H
