#include "qimagetransform.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qImageTransform w;
    w.show();
    return a.exec();
}
