#include <QGridLayout>
#include <QtGui>
#include "qimagetransform.h"
#include "controlpainel_qt.h"
#include "qimageshow.h"

qImageTransform::qImageTransform(QWidget *parent) : QMainWindow(parent)
{
    ControlPainel_qt *buttons = new ControlPainel_qt(this);
    connect(buttons, SIGNAL( pressOpen( QString ) ), this, SLOT( loadImage( QString ) ));

    connect(buttons,SIGNAL( sDrawLineA( void ) ) , this , SLOT(drawLineA( void ) ) );
    connect(buttons,SIGNAL( sDrawLineB( void ) ) , this , SLOT(drawLineB( void ) ) );
    connect(buttons,SIGNAL( sClearLineA( void ) ) , this , SLOT(clearLineA( void ) ) );
    connect(buttons,SIGNAL( sClearLineB( void ) ) , this , SLOT(clearLineB( void ) ) );
    connect(buttons,SIGNAL( sFilterLineA( void ) ) , this , SLOT(filterLineA( void ) ) );
    connect(buttons,SIGNAL( sFilterLineB( void ) ) , this , SLOT(filterLineB( void ) ) );
    connect( buttons,SIGNAL( sMaskA( void ) ) , this , SLOT( buildMaskA( void ) ) );
    connect( buttons,SIGNAL( sMaskB( void ) ) , this , SLOT( buildMaskB( void ) ) );
    connect( buttons,SIGNAL( sStateShowMaskA( int ) ) , this , SLOT( stateShowMaskA( int ) ) );
    connect( buttons,SIGNAL( sStateShowMaskB( int ) ) , this , SLOT( stateShowMaskB( int ) ) );

    this->_imageWindow = new qImageShow();
    this->_imageWindow->show();

    setFixedSize(buttons->frameSize());
    setWindowTitle(tr("Tools"));
}

qImageTransform::~qImageTransform()
{

}

void qImageTransform::drawImage( void )
{
	_imageWindow->drawImage(this->_image);
}

void qImageTransform::loadImage(QString fileName)
{
    if (!fileName.isEmpty())
    {
        QImage image(fileName);
        if (image.isNull())
        {
            QMessageBox::information(this, tr("Image Viewer"),
                                     tr("Cannot load %1.").arg(fileName));
            return;
        }
    this->_image = image;
    drawImage( );
    }
}


