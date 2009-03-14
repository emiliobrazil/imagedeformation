#include "maskImage_qt.h"
#include <QPainter>
#include <QColor>
#include <QPolygonF>
#include <math.h>

QImage eBitMapMask( QSize imageSize,  QVector<QPointF> points  )
{
    QImage image( imageSize , QImage::Format_Mono ) ;
    image.fill(0);
    if( !(imageSize.isNull()) && !points.isEmpty() )
    {
        if( points.first() != points.last() ) points.push_back( points.last() );
        QPolygonF region(points);

        QPainter painterTMP( &image );
        painterTMP.setBrush( Qt::white );
        painterTMP.drawPolygon(region);

        fprintf( stderr , "mask OK!\n");
    }
    return image;
}
