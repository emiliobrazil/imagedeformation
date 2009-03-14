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
        void filterLineA( void ){ this->_imageWindow->filterLineA(); }
        void filterLineB( void ){ this->_imageWindow->filterLineB(); }
        void buildMaskA( void ) { this->_imageWindow->buidMaskA();}
        void buildMaskB( void ){ this->_imageWindow->buidMaskB();}
        void stateShowMaskA( int state ) { this->_imageWindow->changeShowMaskA( state==2 ); }
        void stateShowMaskB( int state ) { this->_imageWindow->changeShowMaskB( state==2 ); }

private slots:
	void drawImage( void );
	void loadImage(QString fileName);

private:

	QImage _image;
	qImageShow* _imageWindow;
};

#endif // QIMAGETRANSFORM_H
