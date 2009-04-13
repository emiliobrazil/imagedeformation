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
    this->_showTan = false;
    this->_showPolyline = false;
    this->_showCurve = true;
    this->_showCorner = false;
    this->_showAngles = false;

    this->factor = 1.0;

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);


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
        this->_cubicCurve.addPoint( event->pos() );
        this->_lastPoint = event->pos();
    }
    update();
}

void DrawArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setBackground(QBrush( Qt::white ));

    painter.setBackgroundMode( Qt::OpaqueMode );
    //    painter.drawImage( 0 , 0 , this->_image) ;

    if( this->_showDistanceFieldRGB ) painter.drawImage(0, 0 , this->_cubicCurve.field().toImageRGBTest() );
    if( this->_showDistanceFieldDx ) painter.drawImage(0, 0 , this->_cubicCurve.field().toImageDx() );
    if( this->_showDistanceFieldDy ) painter.drawImage(0, 0 , this->_cubicCurve.field().toImageDy() );
    if( this->_showDistanceFieldD ) painter.drawImage(0, 0 , this->_cubicCurve.field().toImageD() );

    if( this->_showCurve )this->_cubicCurve.draw( painter , this->_showTan );

    painter.setPen( QPen( QBrush( Qt::darkGreen ), 1.0f ) );
    if( this->_showPolyline ) painter.drawPolyline( this->_cubicCurve.polyline() );

    if( this->_showCorner )
    {
        painter.setPen( QPen( QBrush( Qt::magenta ), 6.0f ) );
        QPolygonF tmp = this->_cubicCurve.corner();
        for ( uint32 i=0 ; i < (uint32)tmp.size() ; ++i )
        {
            painter.drawPoint( tmp[i] );
        }
    }

    if( this->_cubicCurve.polyline().size() == 4 )
    {
        painter.setPen( QPen( QBrush( Qt::darkRed ), 2.0f ) );

        QPolygonF ct = this->_cubicCurve.polyline();
        CubicSegment teste( ct[0] , ct[1] , ct[2] , ct[3] );
        teste.draw(painter,this->_showTan);

        uint32 nopTest = 20;
        painter.setPen( QPen( QBrush( Qt::red ), 1.0f ) );
        for ( uint32 i=0 ; i < nopTest ; ++i )
        {
            real t = (real)i/(real)nopTest;
            painter.drawPoint( teste.eval( t) );
        }
    }


    if( this->_showAngles )
    {
        QPolygonF Tan = this->_cubicCurve.vectorTan();
        QPolygonF Teste = this->_cubicCurve.vectorTeste();
        QPolygonF P = this->_cubicCurve.tanPoints();
        if( P.size() != Tan.size() ) std::cerr << "DrawArea::paintEvent size Problem" << std::endl;
        else{
            for ( uint32 i=0 ; i < (uint32)Tan.size() ; ++i )
            {
                painter.setPen( QPen( QBrush( Qt::green ), 1.0f ) );
                painter.drawLine( P[i], P[i] + this->factor*Tan[i] );

                painter.setPen( QPen( QBrush( Qt::blue ), 1.0f ) );
                painter.drawLine( P[i], P[i] + this->factor*Teste[i] );

                painter.setPen( QPen( QBrush( Qt::red), 4.0f ) );
                painter.drawPoint(P[i]);
            }
        }
    }
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
    case Qt::Key_Minus:
        this->factor*=.5;
        break;
    case Qt::Key_Plus:
        this->factor*= 2.0 ;
        break;
    case Qt::Key_0:
        this->factor=1.0;
        break;
    case Qt::Key_S:
        this->_showDistanceFieldRGB = !this->_showDistanceFieldRGB;
        break;
    case Qt::Key_A:
        this->_showAngles = !this->_showAngles;
        break;
    case Qt::Key_T:
        this->_showTan = !this->_showTan;
        break;
    case Qt::Key_O:
        this->_showCurve = !this->_showCurve;
        break;
    case Qt::Key_I:
        this->_showCorner = !this->_showCorner;
        break;
    case Qt::Key_P:
        this->_showPolyline = !this->_showPolyline;
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
        this->_cubicCurve.clear();
//        this->_distance.clear();
        break;
    default:
        QWidget::keyPressEvent ( event );
    }
    update();
}
