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

	void sDrawLineA( void );
	void sDrawLineB( void );
	void sClearLineA( void );
	void sClearLineB( void );
	void sFilterLineA( void ) ;
	void sFilterLineB( void) ;
        void sMaskA( void );
        void sMaskB( void );
        void sStateShowMaskA( int state ) ;
        void sStateShowMaskB( int state ) ;

private slots:
	void open( void );
	void drawLineA( void ) { emit sDrawLineA(); }
	void drawLineB( void ) { emit sDrawLineB(); }
	void clearLineA( void ) { emit sClearLineA() ; }
	void clearLineB( void ) { emit sClearLineB() ; }
	void filterLineA( void ) { emit sFilterLineA() ; }
        void filterLineB( void ) {emit sFilterLineB() ; }
        void maskA( void ) { emit sMaskA() ;}
        void maskB( void ) { emit sMaskB() ;}
        void stateShowMaskA(int state ) { emit sStateShowMaskA( state ) ;}
        void stateShowMaskB( int state ) { emit sStateShowMaskB( state ) ;}

private:
    Ui::ControlPainel_qtClass ui;
};

#endif // CONTROLPAINEL_QT_H
