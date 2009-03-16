
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
        this->_showSetVectors = false;
        this->_size = QSize( 800 , 800 );

}

qImageShow::~qImageShow()
{

}

void qImageShow::drawImage( const QImage& image )
{
        this->_image = QPixmap::fromImage( image ) ;
        this->_size = this->_image.size();
        this->resize( this->_image.size());
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
        this->_showLineA = true ;
        this->_lastPoint = event->pos();
        this->_lineA.insertPoint( _lastPoint );
    }
    else if( _drawinglineB && ( event->buttons() == Qt::LeftButton ))
    {
        this->_showLineA = true ;
        this->_lastPoint = event->pos();
        this->_lineB.insertPoint( _lastPoint );
    }
    update();
}

void qImageShow::paintEvent( QPaintEvent *event )
{
	QPainter painter(this);
	painter.setBrush(Qt::black);
	painter.drawRect(QRect( 0 , 0 , 800 , 800) );
        painter.drawPixmap( 0 , 0 , this->_image);
        this-> _drawMasks( painter );
        this->_drawLine( painter );
        this->_drawVectorField( painter );
}

void qImageShow::_drawLine( QPainter &painter )
{
    painter.setPen( QPen( QBrush( Qt::green ), 4.0f ) );
    if (this->_lineA.points()!=NULL && this->_lineA.pointCount()>0 && this->_showLineA)
    {
        painter.drawPolyline( _lineA.points() , _lineA.pointCount());
        painter.setPen( QPen( QBrush( Qt::darkGreen ), 6.0f ) );
        for ( uint32 i=0 ; i < _lineA.pointCount() ; ++i )
        {
            painter.drawPoint( _lineA.points()[i] );
        }
    }
    painter.setPen( QPen( QBrush( Qt::red ), 4.0f ) );
    if (this->_lineB.points()!=NULL && this->_lineB.pointCount()>0 && this->_showLineB )
    {
        painter.drawPolyline( _lineB.points() , _lineB.pointCount());
        painter.setPen( QPen( QBrush( Qt::darkRed ), 6.0f ) );

        for ( uint32 i=0 ; i < _lineB.pointCount() ; ++i )
        {
            painter.drawPoint( _lineB.points()[i] );
        }
    }
}



void qImageShow::_drawMasks( QPainter &painter )
{
    if(this->_showImageFinal) painter.drawImage( 0 , 0  , this->_finalImage );
    if(this->_showMaskF) painter.drawImage( 0 , 0  , this->_maskF );
}

void qImageShow::_setField()
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


void qImageShow::_buildField( void )
{
    QPolygonF poli( this->_lineC.toVector() );
    QRectF bBox = poli.boundingRect();
    uint32 i0, i1 , j0 , j1;
    i0 = maximum( 0 , (uint32)floor( bBox.left() ) ) ;
    i1 = minimum( this->_finalImage.width() , (uint32)floor( bBox.right() ) );
    j0 = maximum( 0 , (uint32)floor( bBox.top() ) ) ;
    j1 = minimum( this->_finalImage.height() , (uint32)floor( bBox.bottom() ) );

    this->_vectorField = std::vector< std::pair<Vector2D,Vector2D > >();

    for( uint32 i = i0  ; i < i1 ; i++ )
    {
        for( uint32 j = j0 ; j < j1 ; j++ )
        {
            if( qGray( this->_maskF.pixel( i , j ) ) > 0  )
            {
                Vector2D p( (float)i , (float)j );
                Vector2D v = evalField( (float)i , (float)j , this->_field );
                this->_vectorField.push_back( std::pair<Vector2D,Vector2D> ( p , v ) );
            }
        }
    }
}

void qImageShow::_drawVectorField( QPainter &painter )
{
    if ( this->_showVectors )
    {
        uint32 step = 32;
        painter.setPen( QPen( QBrush( Qt::yellow ), 1.0f ) );
        uint32 numberOfVectors = this->_vectorField.size();
        for ( uint32 i=0 ; i < numberOfVectors ; i = i + step )
        {
            float x = this->_vectorField[i].first.x();
            float y = this->_vectorField[i].first.y();

            float u = this->_vectorField[i].second.x();
            float v = this->_vectorField[i].second.y();

            painter.drawLine( QPointF( x , y ) , QPointF( x + u , y + v ) );
        }
    }

    if ( this->_showSetVectors)
    {
        painter.setPen( QPen( QBrush( Qt::green ), 1.0f ) );
        for ( uint32 i=0 ; i < _lineB.pointCount() ; ++i )
        {
            painter.drawLine( this->_lineB.at(i) , _lineD.at(i)  );
        }
    }
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
        this->_finalImage = QImage( this->_size , QImage::Format_ARGB32 );
        this->_finalImage.setAlphaChannel( this->_maskF );
        this->_setField();
        this->_buildField();
        transformImage( this->_image.toImage() , this->_finalImage , this->_vectorField );
        break;
    case Qt::Key_M:
        this->_showMaskF = !this->_showMaskF;
        break;
    case Qt::Key_F:
        this->_showImageFinal = !this->_showImageFinal;
        break;
    case Qt::Key_V:
        this->_showVectors = !this->_showVectors;
        break;
    case Qt::Key_S:
        this->_showSetVectors = !this->_showSetVectors;
        break;
    case Qt::Key_A:
        this->_showLineA = !this->_showLineA;
        break;
    case Qt::Key_B:
        this->_showLineB = !this->_showLineB;
        break;
    case Qt::Key_1:
        this->drawLineA() ;
        break;
    case Qt::Key_2:
        this->drawLineB() ;
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
