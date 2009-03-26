#include "mainwindow.h"
#include "drawarea.h"

#include <QPushButton>
#include <QGridLayout>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QPushButton *quit = new QPushButton(tr("&Quit"));
    quit->setFont(QFont("Times", 10, QFont::Bold));

    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));


    DrawArea *draw = new DrawArea;

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(quit, 0, 0);
    gridLayout->addWidget(draw, 1, 0, 1, 2);
    gridLayout->setColumnStretch(1, 10);
    setLayout(gridLayout);
    setWindowTitle(tr("Curve"));

}

MainWindow::~MainWindow()
{

}

