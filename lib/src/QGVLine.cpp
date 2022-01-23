#include "QGVLine.h"

#include <QPainter>

QGVLine::QGVLine(QGVItem* parent,
                 const QGV::GeoPos& firstPoint,
                 const QGV::GeoPos& secondPoint,
                 const QColor& color) :
    mGeoFirstPoint(firstPoint),
    mGeoSecondPoint(secondPoint),
    mColor(color)
{
    setSelectable(true);
    auto flags = QGV::ItemFlag::Transformed | QGV::ItemFlag::IgnoreAzimuth | QGV::ItemFlag::IgnoreScale;
    setFlags(flags);
    setParent(parent);
}

QGV::GeoPos QGVLine::getGeoFirstPoint() const
{
    return mGeoFirstPoint;
}

QGV::GeoPos QGVLine::getGeoSecondPoint() const
{
    return mGeoSecondPoint;
}

QLineF QGVLine::line() const
{
    return mLine;
}

QColor QGVLine::getColor() const
{
    return mColor;
}

void QGVLine::onProjection(QGVMap* geoMap)
{
    QGVDrawItem::onProjection(geoMap);
    const auto firstPoint = geoMap->getProjection()->geoToProj(mGeoFirstPoint);
    const auto secondPoint = geoMap->getProjection()->geoToProj(mGeoSecondPoint);

    const auto firstRectPoint = QPointF(firstPoint.x() - 15, firstPoint.y() - 15);
    const auto secondRectPoint = QPointF(secondPoint.x() + 15, secondPoint.y() + 15);

    mLine = QLineF(firstPoint, secondPoint);
    mRect = QRectF(firstRectPoint, secondRectPoint);
    qDebug() << "lenght: " << mLine.length();
    mRect.moveCenter(mLine.center());
    resetBoundary();
}

QPainterPath QGVLine::projShape() const
{
    QPainterPath path;

    //const auto firstPoint = getMap()->getProjection()->geoToProj(mGeoFirstPoint);
    //const auto secondPoint = getMap()->getProjection()->geoToProj(mGeoSecondPoint);

    path.addRect(mRect);
    return path;
}

void QGVLine::projPaint(QPainter* painter)
{
    if (painter == nullptr) {
        return;
    }

    painter->setPen(QPen(QBrush(mColor), 1));
    painter->setBrush(QBrush(mColor));
    painter->drawLine(mLine);
}

QString QGVLine::projTooltip(const QPointF& projPos) const
{
    if (getMap() == nullptr) {
        return QString("");
    }

    const auto geo = getMap()->getProjection()->projToGeo(projPos);
    return "Line with color " + mColor.name() + "\nPosition " + geo.latToString() + " " + geo.lonToString();
}
