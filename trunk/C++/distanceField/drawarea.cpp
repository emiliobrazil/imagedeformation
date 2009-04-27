#include "drawarea.h"

#include <iostream>
#include <QPainter>

DrawArea::DrawArea(QWidget *parent)
    :QWidget(parent)
{
    uint32 w = 1024 , h = 900 ;
    this->resize( w , h );
    this->setFocusPolicy(Qt::ClickFocus);

    this->_distance.initialize( w , h , 25  );

    this->_showDistanceFieldRGB = false;
    this->_showDistanceFieldDx = false ;
    this->_showDistanceFieldDy = false ;
    this->_showDistanceFieldD = false ;

    this->_showPolyline = true;
    this->_showPoints = false;


    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

}

void DrawArea::mouseReleaseEvent(QMouseEvent *event)
{
    if( event->button() == Qt::LeftButton )
    {
        this->_polyline.push_back(event->pos());
        this->_distance.putPoint( event->pos() );
        this->_Vpolyline.push_back(this->_polyline);
        this->_polyline.clear();
    }
}

void DrawArea::mousePressEvent(QMouseEvent *event)
{
    if(  event->buttons() == Qt::LeftButton )
    {
        this->_distance.putPoint( event->pos() );
        this->_lastPoint = event->pos();
        this->_polyline.push_back(event->pos());
    }
    update();
}

void DrawArea::mouseMoveEvent(QMouseEvent *event)
{
    if(  event->buttons() == Qt::LeftButton )
    {
        this->_distance.putPoint( event->pos() );
        this->_distance.putLine(this->_lastPoint , event->pos() );
        this->_polyline.push_back(event->pos());
        this->_lastPoint = event->pos();
    }
    update();
}


void DrawArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if( this->_showDistanceFieldRGB ) painter.drawImage( 0 , 0 , this->_distance.toImageRGBTest());
    if( this->_showDistanceFieldDx ) painter.drawImage( 0 , 0 , this->_distance.toImageDx() );
    if( this->_showDistanceFieldDy ) painter.drawImage( 0 , 0 , this->_distance.toImageDy());
    if( this->_showDistanceFieldD ) painter.drawImage( 0 , 0 , this->_distance.toImageD());


    if(this->_showPoints)
    {
        painter.setPen( QPen( QBrush( Qt::darkMagenta ), 4.0f ) );

        painter.drawPoints(this->_polyline);
        for( int i = 0 ; i < this->_Vpolyline.size() ; ++i )
        {
            painter.drawPoints(this->_Vpolyline[i]);
        }
    }

    if(this->_showPolyline)
    {
        painter.setPen( QPen( QBrush( Qt::darkCyan ), 2.0f ) );

        painter.drawPolyline(this->_polyline);
        for( int i = 0 ; i < this->_Vpolyline.size() ; ++i )
        {
            painter.drawPolyline(this->_Vpolyline[i]);
        }
    }
}

void DrawArea::resizeEvent(QResizeEvent *event)
{
    // todo
}

void DrawArea::keyPressEvent ( QKeyEvent * event )
{
    switch ( event->key() )
    {
    case Qt::Key_Q:
        qApp->quit();
        break;
     case Qt::Key_P:
        this->_showPolyline = !this->_showPolyline ;
        break;
    case Qt::Key_O:
        this->_showPoints = !this->_showPoints ;
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
        this->_distance.clear();
        this->_polyline.clear();
        this->_Vpolyline.clear();
        break;
    default:
        QWidget::keyPressEvent ( event );
    }
    update();
}
