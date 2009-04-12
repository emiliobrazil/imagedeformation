
#include <QImage>
#include <QPoint>
#include <QPointF>
#include <QWidget>
#include <QKeyEvent>
#include <QtGui>
#include <QColor>

#include "qimageshow.h"
#include "pixelManipulation_qt.h"

#include <Vector2D.h>

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

    this->_vectorSamples = std::vector< std::pair<Vector2D,Vector2D > >();

    fprintf(stderr, "Seting Up Field ...\n");

    for ( uint32 i = 0 ; i < numberOfA ; ++i)
    {
        Vector2D p(this->_lineA.at(i).x(), this->_lineA.at(i).y());
        Vector2D v( 0 , 0 );
        this->_vectorSamples.push_back( std::pair<Vector2D,Vector2D> ( p , v ) );
    }

    real radiusTMP = 0 ;

    for (uint32 i = 1 ; i < ( numberOfB - 1 ) ; ++i)
    {
        Vector2D p( this->_lineB.at(i).x(),this->_lineB.at(i).y() );
        Vector2D v(  this->_lineD.at(i).x() - this->_lineB.at(i).x() , this->_lineD.at(i+1).y() - this->_lineB.at(i).y() );
        this->_vectorSamples.push_back( std::pair<Vector2D,Vector2D> ( p , v ) );
        real N = v.norm();
        radiusTMP = ( N > radiusTMP )? N : radiusTMP ;
    }


    //Creating more samples, just folling the vector using beta and alpha; p+beta * v , alpha * v
    real alpha[7] = { 1.00, 1.00, 0.75, 0.75, 0.50, 0.25, 0.00 };
    real beta[7]  = { 0.25, 0.50, 0.75, 1.00, 1.50, 2.00, 2.50 };

    for( uint32 j = 0 ; j < 7 ; ++j )
    {
        for (uint32 i = 1 ; i < ( numberOfB - 1 ) ; ++i)
        {
            Vector2D p( this->_lineB.at(i).x(), this->_lineB.at(i).y() );
            Vector2D v(  this->_lineD.at(i).x() - this->_lineB.at(i).x() , this->_lineD.at(i+1).y() - this->_lineB.at(i).y() );
            this->_vectorSamples.push_back( std::pair<Vector2D,Vector2D> ( p+beta[j] * v , alpha[j] * v ) );
        }
    }

    this->_MLSRadius = 2.0f*radiusTMP;

    uint32 numberOfsamples = this->_vectorSamples.size() ;

    real* points = new real[ 2 * numberOfsamples ];
    real* vectors = new real[ 2 * numberOfsamples ];


    for( uint32 i = 0 ; i < numberOfsamples ; ++i )
    {
        points[  2*i   ] = this->_vectorSamples[i].first.x();
        points[  2*i+1 ] = this->_vectorSamples[i].first.y();
        vectors[ 2*i   ] = this->_vectorSamples[i].second.x();
        vectors[ 2*i+1 ] = this->_vectorSamples[i].second.y();
    }

    this->_field.setSamples( numberOfsamples , points , vectors );
    delete[] vectors;
    delete[] points;
    fprintf(stderr, "Field Seted \n");

}


void qImageShow::_buildField( void )
{

    fprintf(stderr, "Building Field ...\n");

    this->_field.setRadius( this->_MLSRadius );

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
   fprintf(stderr, "Field builded\n");
}

void qImageShow::_drawVectorField( QPainter &painter )
{
    uint32 step = 32;
    if ( this->_showVectors )
    {
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
        step = 1;
        painter.setPen( QPen( QBrush( Qt::green ), 1.0f ) );
        uint32 numberOfSamples = this->_vectorSamples.size();
        for ( uint32 i=0 ; i < numberOfSamples ; i = i + step )
        {
            float x = this->_vectorSamples[i].first.x();
            float y = this->_vectorSamples[i].first.y();

            float u = this->_vectorSamples[i].second.x();
            float v = this->_vectorSamples[i].second.y();

            painter.drawLine( QPointF( x , y ) , QPointF( x + u , y + v ) );
        }
    }
}

void qImageShow::keyPressEvent ( QKeyEvent * event )
{
    QString fileName;
    std::pair< uint32,QPointF > pairTeste ;
    switch ( event->key() )
    {
    case Qt::Key_Q:
        qApp->quit();
        break;

    case Qt::Key_0:
        fileName = QFileDialog::getSaveFileName(this,tr("Export Lines"), QDir::currentPath()+"/lineNew.lin",tr("lines (*.lin)"));
        if(!fileName.isEmpty())
        {
            this->_lineA.save(fileName);
            this->_lineB.save(fileName);
        }
        break;
    case Qt::Key_9:
        fileName = QFileDialog::getOpenFileName(this,tr("Load Lines"), QDir::currentPath(),tr("lines (*.lin)\nall (*.*)"));
        if(!fileName.isEmpty())
        {
            this->_lineA.load( fileName , 1 );
            this->_lineB.load( fileName , 2 );
            this->_showLineA = true;
            this->_showLineB = true;
        }
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
//        this->_finalImage.setAlphaChannel( this->_maskF );
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
    case Qt::Key_C:
        this->clearLineA();
        this->clearLineB();
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
