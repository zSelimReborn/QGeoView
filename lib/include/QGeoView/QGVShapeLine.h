#ifndef QGVSHAPELINE_H
#define QGVSHAPELINE_H

#include "QGVLayerShape.h"
#include "QGVDrawItem.h"

class QGV_LIB_DECL QGVShapeLine : public QGVDrawItem, public QGVLayerShape
{
public:
    QGVShapeLine(QGVItem*, const QGVLayerItemData&);

protected:
    QPolygonF getProjPolygon();

protected:
    void onProjection(QGVMap*) override;

    QPainterPath projShape() const override;

    void projPaint(QPainter*) override;

    QPointF projAnchor() const override;

private:
    QList<QGV::GeoPos> mGeoCoordinates;
    QPolygonF mProjPolygon;
};

#endif // QGVSHAPELINE_H
