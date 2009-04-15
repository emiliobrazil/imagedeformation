#include <QGridLayout>
#include <QtGui>
#include "qimagetransform.h"
#include "controlpainel_qt.h"
#include "qimageshow.h"

qImageTransform::qImageTransform(QWidget *parent) : QMainWindow(parent)
{
    ControlPainel_qt *buttons = new ControlPainel_qt(this);
    connect(buttons, SIGNAL( pressOpen( QString ) ), this, SLOT( loadImage( QString ) ));
    connect(buttons, SIGNAL( pressSave( QString ) ), this, SLOT( saveImage( QString ) ));

    connect(buttons,SIGNAL( sDrawLineA( void ) ) , this , SLOT(drawLineA( void ) ) );
    connect(buttons,SIGNAL( sDrawLineB( void ) ) , this , SLOT(drawLineB( void ) ) );
    connect(buttons,SIGNAL( sClearLineA( void ) ) , this , SLOT(clearLineA( void ) ) );
    connect(buttons,SIGNAL( sClearLineB( void ) ) , this , SLOT(clearLineB( void ) ) );

    this->_imageWindow = new qImageShow();
    this->_imageWindow->show();

    QImage image("image_test/zebra.jpg");
    if (image.isNull())
    {
        QMessageBox::information(this, tr("Image Viewer"),
                                 tr("Cannot load %1.").arg("image_test/zebra.jpg"));
        return;
    }
    this->_image = image;
    drawImage( );


    setFixedSize(buttons->frameSize());
    setWindowTitle(tr("Tools"));
}

qImageTransform::~qImageTransform()
{

}

void qImageTransform::drawImage( void )
{
        this->_imageWindow->drawImage(this->_image);
}

void qImageTransform::loadImage(QString fileName)
{
    if (!fileName.isEmpty())
    {
        QImage image(fileName);
        if (image.isNull())
        {
            QMessageBox::information(this, tr("Image Viewer"),
                                     tr("Can not load %1.").arg(fileName));
            return;
        }
    this->_image = image;
    drawImage( );
    }
}

void qImageTransform::saveImage(QString fileName)
{
    QImage iTmp = this->_imageWindow->getImage();
    if (!fileName.isEmpty())
    {
        if( iTmp.isNull() )
        {
            QMessageBox::information(this, tr("Image Viewer"),
                                     tr("Cannot Save %1.").arg(fileName));
            return;
        }
        this->_image = iTmp;
        drawImage( );
        bool s = iTmp.save(fileName);
        if( !s )
        {
            QMessageBox::information(this, tr("Image Viewer"),
                                     tr("Cannot Save %1.").arg(fileName));
        }
    }
}
