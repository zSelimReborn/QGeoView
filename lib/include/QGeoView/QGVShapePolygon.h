#ifndef QGVSHAPEPOLYGON_H
#define QGVSHAPEPOLYGON_H

#include "QGVShapeLine.h"

#include <QList>
#include <QPainterPath>

class QGV_LIB_DECL QGVShapePolygon : public QGVShapeLine
{
public:
    QGVShapePolygon(QGVItem*, const QGVLayerItemData&);

protected:
    void projPaint(QPainter*) override;

private:
    QList<QGV::GeoPos> mGeoCoordinates;
};

#endif // QGVSHAPEPOLYGON_H
