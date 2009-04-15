#ifndef QIMAGETRANSFORM_H
#define QIMAGETRANSFORM_H

#include <QtGui/QMainWindow>
#include <QImage>
#include "qimageshow.h"



class qImageTransform : public QMainWindow
{
    Q_OBJECT

public:
    qImageTransform( QWidget *parent = 0 );
    ~qImageTransform();

public slots:
        void drawLineA( void ){ this->_imageWindow->drawLineA(); }
        void drawLineB( void ){ this->_imageWindow->drawLineB(); }
        void clearLineA( void ){ this->_imageWindow->clearLineA(); }
        void clearLineB( void ){ this->_imageWindow->clearLineB(); }

private slots:
	void drawImage( void );
	void loadImage(QString fileName);
        void saveImage( QString fileName );

private:

	QImage _image;
	qImageShow* _imageWindow;
};

#endif // QIMAGETRANSFORM_H
