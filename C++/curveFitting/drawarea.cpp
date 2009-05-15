#include "drawarea.h"

#include "distancefield.h"


#include <iostream>
#include <QPainter>

DrawArea::DrawArea(QWidget *parent)
    :QWidget(parent)
{
    uint32 w = 1024 , h = 900 ;
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
    this->_showPol = false;
    this->_showDataIn = false;
    this->_showCurve = true;
    this->_showCorner = false;
    this->_showAngles = false;
    this->_showBb = false;

    this->_erroTol = 1.0;
    this->factor = 1.0;

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);


}

void DrawArea::mouseReleaseEvent(QMouseEvent *event)
{
    if( event->button() == Qt::LeftButton )
    {
        this->_cubicCurve.finish();
        this->_corner.push_back( this->_cubicCurve.corner()) ;
        this->_polyline.push_back(this->_cubicCurve.polyline());
        this->_path.push_back(this->_cubicCurve.curve());

        this->_pTan.push_back( this->_cubicCurve.tanPoints());
        this->_tan.push_back( this->_cubicCurve.vectorTan());
        this->_vTeste.push_back( this->_cubicCurve.vectorTeste());

        this->_cubicCurve.clear();
        update();
    }
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

    //    painter.drawImage( 0 , 0 , this->_image) ;

    if( this->_showDistanceFieldRGB ) painter.drawImage( 0 , 0 , this->_cubicCurve.field().toImageRGBTest() );
    if( this->_showDistanceFieldDx ) painter.drawImage( 0 , 0 , this->_cubicCurve.field().toImageDx() );
    if( this->_showDistanceFieldDy ) painter.drawImage( 0 , 0 , this->_cubicCurve.field().toImageDy() );
    if( this->_showDistanceFieldD ) painter.drawImage( 0 , 0 , this->_cubicCurve.field().toImageD() );


    this->_cubicCurve.draw( painter , this->_showTan , this->_showPol );

    if( this->_showBb )
    {
        painter.setPen( QPen( QBrush( Qt::darkYellow ), 3.0f ) );
        for( int i = 0 ; i < this->_path.size() ; ++i )
        {
            QRectF tmp = this->_path[i].getBoudingBox();
            painter.drawRect( tmp );
        }
    }

    if( this->_showCurve )
    {
        painter.setPen( QPen( QBrush( Qt::darkCyan ), 4.0f ) );
        for( int i = 0 ; i < this->_path.size() ; ++i )
        {
            this->_path[i].draw( painter , this->_showTan , this->_showPol );
        }
    }

    if( this->_showDataIn )
    {
        painter.setPen( QPen( QBrush( Qt::black ), 4.0f ) );
        for( int i = 0 ; i < this->_polyline.size() ; ++i )
        {
            painter.drawPoints( this->_polyline[i] );
        }
    }
    if( this->_showCorner )
    {
        painter.setPen( QPen( QBrush( Qt::magenta ), 6.0f ) );
        for ( int i = 0 ; i < this->_corner.size() ; ++i )
        {
            painter.drawPoints( this->_corner[i] );
        }
    }

    if( this->_showAngles )
    {
        for ( int i = 0 ; i < this->_tan.size() ; ++i )
        {
            QPolygonF Tan = this->_tan[i];
            QPolygonF Teste = this->_vTeste[i];
            QPolygonF P = this->_pTan[i];

            for ( int j = 0 ; j < Tan.size() ; ++j )
            {

                painter.setPen( QPen( QBrush( Qt::green ), 1.0f ) );
                painter.drawLine( P[j], P[j] + this->factor*Tan[j] );

                painter.setPen( QPen( QBrush( Qt::blue ), 1.0f ) );
                painter.drawLine( P[j], P[j] + this->factor*Teste[j] );

                painter.setPen( QPen( QBrush( Qt::darkRed), 4.0f ) );
                painter.drawPoint(P[j]);
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
    case Qt::Key_Down:
        this->_erroTol-=.5;
        this->_cubicCurve.setErro(this->_erroTol);
        std::cerr << "ERROR TOL = " << this->_cubicCurve.getErro( ) << std::endl;
        break;
    case Qt::Key_Up:
        this->_erroTol+=.5;
        this->_cubicCurve.setErro(this->_erroTol);
        std::cerr << "ERROR TOL = " << this->_cubicCurve.getErro( ) << std::endl;
        break;
    case Qt::Key_1:
        this->_cubicCurve.setCornerAngle( 0.707106781); // 45 degre
        std::cerr << "CORNER TOL = 45 deg" << std::endl;
        break;
    case Qt::Key_2:
        this->_cubicCurve.setCornerAngle( 0.5); // 60 degre
        std::cerr << "CORNER TOL = 60 deg" << std::endl;
        break;
    case Qt::Key_3:
        this->_cubicCurve.setCornerAngle( 0.0 ); // 90 degre
        std::cerr << "CORNER TOL = 90 deg" << std::endl;
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
    case Qt::Key_R:
        this->_showPol = !this->_showPol;
        this->_showBb = !this->_showBb;
        break;
    case Qt::Key_O:
        this->_showCurve = !this->_showCurve;
        break;
    case Qt::Key_I:
        this->_showCorner = !this->_showCorner;
        break;
    case Qt::Key_P:
        this->_showDataIn = !this->_showDataIn;
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
        //        this->_distance.clear();
        this->_path.clear();
        this->_polyline.clear();
        this->_corner.clear();
        this->_tan.clear();
        this->_pTan.clear();
        this->_vTeste.clear();
        break;
    default:
        QWidget::keyPressEvent ( event );
    }
    update();
}
