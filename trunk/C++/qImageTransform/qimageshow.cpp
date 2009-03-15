
#include <QImage>
#include <QPoint>
#include <QPointF>
#include <QWidget>
#include <QKeyEvent>
#include <QtGui>
#include <QColor>

#include "qimageshow.h"
#include "pixelManipulation_qt.h"

qImageShow::qImageShow( QWidget *parent) : QWidget(parent)
{
        this->_drawinglineA = false;
        this->_drawinglineB = false;
        this->_showMaskA = false;
        this->_showMaskB = false;
        this->setCursor(Qt::CrossCursor);
        this->_showVectors = false;
}

qImageShow::~qImageShow()
{

}

void qImageShow::drawImage( const QImage& image )
{
        this->_image = QPixmap::fromImage( image ) ;
	update();
}

void qImageShow::mousePressEvent( QMouseEvent *event )
{
	if( _drawinglineA && ( event->buttons() == Qt::LeftButton ))
	{
		_lastPoint = event->pos();
                _lineA.insertPoint( _lastPoint );
	}
	else if( _drawinglineB && ( event->buttons() == Qt::LeftButton ))
	{
		_lastPoint = event->pos();
                _lineB.insertPoint( _lastPoint );
	}
	update();
}

void qImageShow::mouseMoveEvent( QMouseEvent *event )
{
	if( _drawinglineA && ( event->buttons() == Qt::LeftButton ))
	{
		_lastPoint = event->pos();
                _lineA.insertPoint( _lastPoint );
	}
	else if( _drawinglineB && ( event->buttons() == Qt::LeftButton ))
	{
		_lastPoint = event->pos();
                _lineB.insertPoint( _lastPoint );
	}
	update();
}

void qImageShow::paintEvent( QPaintEvent *event )
{
	QPainter painter(this);
	painter.setBrush(Qt::black);
	painter.drawRect(QRect( 0 , 0 , 800 , 800) );
        painter.drawPixmap( 0 , 0 , this->_image);
        _drawMasks(painter);
        _drawLine( painter );
}

void qImageShow::_drawLine( QPainter &painter )
{
    painter.setPen( QPen( QBrush( Qt::green ), 4.0f ) );
    if (_lineA.points()!=NULL && _lineA.pointCount()>0) {
        painter.drawPolyline( _lineA.points() , _lineA.pointCount());
        painter.setPen( QPen( QBrush( Qt::darkGreen ), 6.0f ) );
        for ( uint32 i=0 ; i < _lineA.pointCount() ; ++i )
        {
            painter.drawPoint( _lineA.points()[i] );
        }
    }
    painter.setPen( QPen( QBrush( Qt::red ), 4.0f ) );
    if (_lineB.points()!=NULL && _lineB.pointCount()>0) {
        painter.drawPolyline( _lineB.points() , _lineB.pointCount());
        painter.setPen( QPen( QBrush( Qt::darkRed ), 6.0f ) );

        for ( uint32 i=0 ; i < _lineB.pointCount() ; ++i )
        {
            painter.drawPoint( _lineB.points()[i] );
        }
    }
    painter.setPen( QPen( QBrush( Qt::white ), 2.0f ) );
    if (_lineC.points()!=NULL && _lineC.pointCount()>0) {
        painter.drawPolyline( _lineC.points() , _lineC.pointCount());
    }
    painter.setPen( QPen( QBrush( Qt::cyan ), 2.0f ) );
    if (_lineD.points()!=NULL && _lineD.pointCount()>0) {
        painter.drawPolyline( _lineD.points() , _lineD.pointCount());
        painter.setPen( QPen( QBrush( Qt::darkCyan ), 4.0f ) );

        for ( uint32 i=0 ; i < _lineB.pointCount() ; ++i )
        {
            painter.drawPoint( _lineD.points()[i] );
        }
    }

    painter.setPen( QPen( QBrush( Qt::green ), 1.0f ) );
    if ( this->_showVectors ) {
        painter.drawPolyline( _lineD.points() , _lineD.pointCount());
        for ( uint32 i=0 ; i < _lineB.pointCount() ; ++i )
        {
            painter.drawLine( this->_lineB.at(i) , _lineD.at(i)  );
        }
    }


    painter.setPen( QPen( QBrush( Qt::cyan ), 6.0f ) );
    painter.drawPoint( this->_pointTesteA );
    painter.setPen( QPen( QBrush( Qt::yellow ), 6.0f ) );
    painter.drawPoint( this->_pointTesteB );
}


void qImageShow::_drawMasks( QPainter &painter )
{
    if(this->_showMaskA) painter.drawImage( 0 , 0  , this->_finalImage );
    if(this->_showMaskB) painter.drawImage( 0 , 0  , this->_maskB );
    if(this->_showMaskF) painter.drawImage( 0 , 0  , this->_maskF );
}


void qImageShow::keyPressEvent ( QKeyEvent * event )
{
            std::pair< uint32,QPointF > pairTeste ;
    switch ( event->key() )
    {
    case Qt::Key_S:
        this->_lineD = this->_lineB.split( 2 , 11 );
        break;
    case Qt::Key_J:
        this->_lineC = this->_lineA.join( this->_lineB );
        this->_lineC.close();
        break;
    case Qt::Key_C:
        this->_lineB.close();
        this->_lineA.close();
        break;
    case Qt::Key_A:
        this->_lineD = this->_lineA.split( this->_lineB.atBegin() , this->_lineB.atEnd() ) ;
        break;
    case Qt::Key_T:
        pairTeste = this->_lineA.argDistTo( this->_lineB.at( 0 ) ) ;
        this->_pointTesteA = pairTeste.second;
        this->_pointTesteB = this->_lineA.points()[ pairTeste.first ] ;
        break;
    case Qt::Key_G:
        this->_lineA.grow(50);
        break;
    case Qt::Key_R:
        this->_lineB.insertPoint( this->_lineD.atBegin() , 0 );
        this->_lineB.insertPoint( this->_lineD.atEnd() );
        this->_lineD.reparametri( this->_lineB );
        break;
    case Qt::Key_D:
        this->_lineA.lineFilter();
        this->_lineA.close();
        this->_lineB.lineFilter( 0.5 );
        this->_lineD = this->_lineA.split( this->_lineB.atBegin() , this->_lineB.atEnd() ) ;
        this->_lineB.insertPoint( this->_lineD.atBegin() , 0 );
        this->_lineB.insertPoint( this->_lineD.atEnd() );
        this->_lineD.reparametri( this->_lineB );
        this->_lineC = this->_lineA.join( this->_lineB );
        this->_lineC.close();
        this->_maskF = eBitMapMask( this->_image.size() , this->_lineC.toVector() );
        this->_showMaskF = true;
        this->_showVectors = true;
        this->_finalImage = QImage( this->_image.size() , QImage::Format_ARGB32 );
        this->_finalImage.setAlphaChannel( this->_maskF );
        transformImage( this->_image.toImage() , this->_finalImage , this->_maskF , this->_lineC );
        this->_showMaskA = true;
        break;
    case Qt::Key_M:
        this->_showMaskF = !this->_showMaskF;
        break;
    default:
        QWidget::keyPressEvent ( event );
    }
    update();
}


void qImageShow::resizeEvent( QResizeEvent *event )
{
	//TODO
}
