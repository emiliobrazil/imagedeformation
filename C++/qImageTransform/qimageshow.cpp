
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
        _drawMasks( painter );
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

//    painter.setPen( QPen( QBrush( Qt::white ), 2.0f ) );
//    if (_lineC.points()!=NULL && _lineC.pointCount()>0) {
//        painter.drawPolyline( _lineC.points() , _lineC.pointCount());
//    }
//    painter.setPen( QPen( QBrush( Qt::cyan ), 2.0f ) );
//    if (_lineD.points()!=NULL && _lineD.pointCount()>0) {
//        painter.drawPolyline( _lineD.points() , _lineD.pointCount());
//        painter.setPen( QPen( QBrush( Qt::darkCyan ), 4.0f ) );
//
//        for ( uint32 i=0 ; i < _lineB.pointCount() ; ++i )
//        {
//            painter.drawPoint( _lineD.points()[i] );
//        }
//    }
//
//    painter.setPen( QPen( QBrush( Qt::green ), 1.0f ) );
//    if ( this->_showVectors ) {
//        painter.drawPolyline( _lineD.points() , _lineD.pointCount());
//        for ( uint32 i=0 ; i < _lineB.pointCount() ; ++i )
//        {
//            painter.drawLine( this->_lineB.at(i) , _lineD.at(i)  );
//        }
//    }

}



void qImageShow::_drawMasks( QPainter &painter )
{
    if(this->_showImageFinal) painter.drawImage( 0 , 0  , this->_finalImage );
    if(this->_showMaskF) painter.drawImage( 0 , 0  , this->_maskF );
}

void qImageShow::builField()
{
    uint32 numberOfA = this->_lineA.pointCount() ;
    uint32 numberOfB = this->_lineB.pointCount() ;
    uint32 numberOfsamples = numberOfA + numberOfB - 2 ;
    real* points = new real[ 2 * numberOfsamples ];
    real* vectors = new real[ 2 * numberOfsamples ];

    this->_field.setRadius( 80.0f );

    for (register unsigned int i = 0; i < numberOfA ; ++i)
    {
        points[2*i  ] = this->_lineA.at(i).x();
        points[2*i+1] = this->_lineA.at(i).y();
        vectors[2*i  ] = 0.0f;
        vectors[2*i+1] = 0.0f;
    }
    for (register unsigned int i = 1 ; i < ( numberOfB - 1 ) ; ++i)
    {
        points[2*i  ] = this->_lineB.at(i).x();
        points[2*i+1] = this->_lineB.at(i).y();
        vectors[2*i  ] = this->_lineD.at(i).x() - this->_lineB.at(i).x();
        vectors[2*i+1] = this->_lineD.at(i).y() - this->_lineB.at(i).y();
    }

    this->_field.setSamples( numberOfsamples , points , vectors );
    delete[] vectors;
    delete[] points;
}

void qImageShow::keyPressEvent ( QKeyEvent * event )
{
            std::pair< uint32,QPointF > pairTeste ;
    switch ( event->key() )
    {
    case Qt::Key_Q:
        qApp->quit();
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
        this->_showMaskF = false;
        this->_showImageFinal = true;
        this->_finalImage = QImage( this->_image.size() , QImage::Format_ARGB32 );
        this->_finalImage.setAlphaChannel( this->_maskF );
        this->builField();
        transformImage( this->_image.toImage() , this->_finalImage , this->_maskF , this->_lineC , this->_field );
        break;
    case Qt::Key_M:
        this->_showMaskF = !this->_showMaskF;
        break;
    case Qt::Key_F:
        this->_showImageFinal = !this->_showImageFinal;
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
