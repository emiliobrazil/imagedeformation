#include <QtGui>
#include "controlpainel_qt.h"

ControlPainel_qt::ControlPainel_qt(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);

	connect( ui.buttonQuit, SIGNAL( clicked() ), qApp, SLOT( quit() ) );
	connect( ui.buttonOpen, SIGNAL( clicked() ), this, SLOT( open() ) );

	connect( ui.buttonDrawLineA, SIGNAL( clicked() ), this, SLOT( drawLineA() ) );
	connect( ui.buttonDrawLineB, SIGNAL( clicked() ), this, SLOT( drawLineB() ) );
	connect( ui.buttonClearLineA, SIGNAL( clicked() ), this, SLOT( clearLineA() ) );
        connect( ui.buttonClearLineB, SIGNAL( clicked() ), this, SLOT( clearLineB() ) );
}

ControlPainel_qt::~ControlPainel_qt()
{

}

void ControlPainel_qt::open( void )
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                    tr("Open File"), QDir::currentPath());
    emit pressOpen( fileName );
}
