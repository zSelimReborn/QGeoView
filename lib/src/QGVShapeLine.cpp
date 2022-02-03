#include "QGVShapeLine.h"
#include <QPainter>

namespace  {
    const quint16 baseLineWidth = 1500;

    const auto strokeColorProp      = "stroke"; // Border color
    const auto strokeWidthProp      = "stroke-width"; // Border width
    const auto strokeOpacityProp    = "stroke-opacity"; // Border opacity
}

QGVShapeLine::QGVShapeLine(QGVItem* parent, const QGVLayerItemData& itemData) :
    QGVLayerShape(itemData)
{
    const auto flags = QGV::ItemFlag::Transformed;
    setFlags(flags);
    setParent(parent);
    mGeoCoordinates = getCoordinates();
}

void QGVShapeLine::onProjection(QGVMap* geoMap)
{
    QGVDrawItem::onProjection(geoMap);

    mProjPolygon.clear();
    for (const auto& geoCoord : qAsConst(mGeoCoordinates)) {
        const auto projCoord = geoMap->getProjection()->geoToProj(geoCoord);
        mProjPolygon.append(projCoord);
    }
}

QPainterPath QGVShapeLine::projShape() const
{
    QPainterPath path;

    path.addPolygon(mProjPolygon);
    return path;
}

QPointF QGVShapeLine::projAnchor() const
{
    return (mProjPolygon.size() > 0)? mProjPolygon.first() : QPointF();
}

void QGVShapeLine::projPaint(QPainter* painter)
{
    if (painter == nullptr) {
        return;
    }

    const auto projPolygon = getProjPolygon();
    const auto lineColor = hasProperty(strokeColorProp)? QColor(getProperty(strokeColorProp).toString()) : Qt::black;
    const auto lineOpacity = hasProperty(strokeOpacityProp)? getProperty(strokeOpacityProp).toDouble() : 1;

    const auto lineFactor = hasProperty(strokeWidthProp)? getProperty(strokeWidthProp).toInt() : 1;
    const auto lineWidth = baseLineWidth * lineFactor;

    painter->setOpacity(lineOpacity);
    painter->setPen(QPen(QBrush(lineColor), lineWidth));
    painter->setBrush(QBrush(lineColor));
    for (int i = 1; i < projPolygon.size(); ++i) {
        const auto p1 = projPolygon.at(i - 1);
        const auto p2 = projPolygon.at(i);
        painter->drawLine(p1, p2);
    }
}

QPolygonF QGVShapeLine::getProjPolygon()
{
    return mProjPolygon;
}
