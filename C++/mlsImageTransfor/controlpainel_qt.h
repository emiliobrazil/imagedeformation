#ifndef CONTROLPAINEL_QT_H
#define CONTROLPAINEL_QT_H

#include <QtGui/QWidget>
#include "ui_controlpainel_qt.h"

class ControlPainel_qt : public QWidget
{
    Q_OBJECT
public:
    ControlPainel_qt(QWidget *parent = 0);
    ~ControlPainel_qt();

signals:
        void pressOpen( QString fileName );
        void pressSave( QString fileName );

	void sDrawLineA( void );
	void sDrawLineB( void );
	void sClearLineA( void );
        void sClearLineB( void );

private slots:
        void open( void );
        void save( void );
        void drawLineA( void ) { emit sDrawLineA(); }
	void drawLineB( void ) { emit sDrawLineB(); }
	void clearLineA( void ) { emit sClearLineA() ; }
        void clearLineB( void ) { emit sClearLineB() ; }
private:
    Ui::ControlPainel_qtClass ui;
};

#endif // CONTROLPAINEL_QT_H
