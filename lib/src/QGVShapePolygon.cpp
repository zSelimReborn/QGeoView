#include "QGVShapePolygon.h"

#include <QPainter>
#include <QPainterPath>

namespace  {
    const auto fillColorProp        = "fill"; // Fill color
    const auto fillOpacityProp      = "fill-opacity"; // Fill opacity
}

QGVShapePolygon::QGVShapePolygon(QGVItem* parent, const QGVLayerItemData& itemData)
    : QGVShapeLine(parent, itemData)
{
    mGeoCoordinates = getCoordinates();
}

void QGVShapePolygon::projPaint(QPainter* painter)
{
    QGVShapeLine::projPaint(painter);
    if (painter == nullptr) {
        return;
    }

    const QColor shapeColor = QColor(getProperty(fillColorProp).toString());

    painter->setOpacity(getProperty(fillOpacityProp).toDouble());

    painter->setPen(QPen(QBrush(shapeColor), 1));
    painter->setBrush(QBrush(shapeColor));
    painter->drawPolygon(getProjPolygon());
}
