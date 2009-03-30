#include "drawarea.h"
#include "lineScan.h"

#include "distancefield.h"


#include <iostream>
#include <QPainter>

DrawArea::DrawArea(QWidget *parent)
    :QWidget(parent)
{
    this->_image = QImage( 1024, 780 ,QImage::Format_ARGB32 );
    this->setFocusPolicy(Qt::ClickFocus);
}

void DrawArea::mousePressEvent(QMouseEvent *event)
{
    if(  event->buttons() == Qt::LeftButton )
    {
        this->_lastPoint = event->pos();
    }

    update();
}

void DrawArea::mouseMoveEvent(QMouseEvent *event)
{
    if(  event->buttons() == Qt::LeftButton )
    {
        pBox( this->_image , this->_lastPoint , 20  );
        dda( this->_image , this->_lastPoint , event->pos() , 20 );
        this->_lastPoint = event->pos();
    }
    update();
}

void DrawArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawImage( 0 , 0 , this->_image) ;
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
    case Qt::Key_C:
        this->_image = QImage( 1024, 780 ,QImage::Format_ARGB32 );
        break;
    default:
        QWidget::keyPressEvent ( event );
    }
    update();
}
