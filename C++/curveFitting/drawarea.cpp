#include "drawarea.h"
#include "lineScan.h"

#include "distancefield.h"


#include <iostream>
#include <QPainter>

DrawArea::DrawArea(QWidget *parent)
    :QWidget(parent)
{
    uint32 w = 1024 , h = 900 ;
//    this->_image = QImage( w, h ,QImage::Format_ARGB32 );
    this->resize( w , h );
    this->setFocusPolicy(Qt::ClickFocus);
    this->_radius = 20;

    this->_distance.initialize( w , h , this->_radius  );

    this->_cubicCurve.initialize(  w ,  h ,  this->_radius );

    this->_showDistanceFieldRGB = false;
    this->_showDistanceFieldDx = false ;
    this->_showDistanceFieldDy = false ;
    this->_showDistanceFieldD = false ;

    void addPoint( QPointF p );
    void draw( QPainter &painter );

}

void DrawArea::mousePressEvent(QMouseEvent *event)
{
    if(  event->buttons() == Qt::LeftButton )
    {
        this->_lastPoint = event->pos();
        this->_cubicCurve.addPoint(event->pos());
    }
    update();
}

void DrawArea::mouseMoveEvent(QMouseEvent *event)
{
    if(  event->buttons() == Qt::LeftButton )
    {
//        this->_distance.putPoint( this->_lastPoint );
//        this->_distance.putLine(this->_lastPoint , event->pos() );
//        pBox( this->_image , this->_lastPoint , 20  );
//        dda( this->_image , this->_lastPoint , event->pos() , 20 );
        this->_cubicCurve.addPoint(event->pos() );
        this->_lastPoint = event->pos();
    }
    update();
}

void DrawArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

//    painter.drawImage( 0 , 0 , this->_image) ;

//    if( this->_showDistanceFieldRGB ) painter.drawImage(0, 0 , this->_distance.toImageRGBTest() );
//    if( this->_showDistanceFieldDx ) painter.drawImage(0, 0 , this->_distance.toImageDx() );
//    if( this->_showDistanceFieldDy ) painter.drawImage(0, 0 , this->_distance.toImageDy() );
//    if( this->_showDistanceFieldD ) painter.drawImage(0, 0 , this->_distance.toImageD() );

    this->_cubicCurve.draw( painter );

}

void DrawArea::resizeEvent(QResizeEvent *event)
{
    // todo
}

void DrawArea::keyPressEvent ( QKeyEvent * event )
{
    QString fileName;
    std::pair< uint32,QPointF > pairTeste ;
    switch ( event->key() )
    {
    case Qt::Key_Q:
        qApp->quit();
        break;
    case Qt::Key_S:
        this->_showDistanceFieldRGB = !this->_showDistanceFieldRGB;
        break;
    case Qt::Key_X:
        this->_showDistanceFieldDx = !this->_showDistanceFieldDx ;
        break;
    case Qt::Key_Y:
        this->_showDistanceFieldDy = !this->_showDistanceFieldDy ;
        break;
    case Qt::Key_D:
        this->_showDistanceFieldD = !this->_showDistanceFieldD ;
        break;
    case Qt::Key_C:
        //        this->_image = QImage( 1024, 780 ,QImage::Format_ARGB32 );
        this->_distance.clear();
        break;
    default:
        QWidget::keyPressEvent ( event );
    }
    update();
}
