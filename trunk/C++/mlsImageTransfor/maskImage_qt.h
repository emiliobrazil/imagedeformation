#ifndef MASKIMAGE_QT_H
#define MASKIMAGE_QT_H

#include <QVector>
#include <QPoint>
#include <QImage>

QImage eBitMapMask( QSize imageSize,  QVector<QPointF> points  );

#endif // MASKIMAGE_QT_H
