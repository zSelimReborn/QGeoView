#include "QGVLine.h"

#include <QPainter>

QGVLine::QGVLine(QGVItem* parent,
                 const QGV::GeoPos& firstPoint,
                 const QGV::GeoPos& secondPoint,
                 const QColor& color) :
    mGeoFirstPoint(firstPoint),
    mGeoSecondPoint(secondPoint),
    mColor(color),
    mWidth(1500),
    bShow(true)
{
    auto flags = QGV::ItemFlag::Transformed;
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

void QGVLine::setWidth(const quint16& width)
{
    mWidth = width;
}

quint16 QGVLine::getWidth() const
{
    return mWidth;
}

void QGVLine::showLine()
{
    bShow = true;
    refresh();
    repaint();
}

void QGVLine::hideLine()
{
    bShow = false;
    refresh();
    repaint();
}

bool QGVLine::shouldShowLine()
{
    return bShow;
}

void QGVLine::onProjection(QGVMap* geoMap)
{
    QGVDrawItem::onProjection(geoMap);

    mGeoRect = QGV::GeoRect(mGeoFirstPoint, mGeoSecondPoint);
    mRect = geoMap->getProjection()->geoToProj(mGeoRect);
}

QPainterPath QGVLine::projShape() const
{
    QPainterPath path;

    path.addRect(mRect);
    return path;
}

void QGVLine::projPaint(QPainter* painter)
{
    if (painter == nullptr) {
        return;
    }

    if (!shouldShowLine()) {
        return;
    }

    const auto firstProj = getMap()->getProjection()->geoToProj(mGeoFirstPoint);
    const auto secondProj = getMap()->getProjection()->geoToProj(mGeoSecondPoint);

    painter->setPen(QPen(QBrush(mColor), getWidth()));
    painter->setBrush(QBrush(mColor));
    painter->drawLine(firstProj, secondProj);
}

QPointF QGVLine::projAnchor() const
{
    return mRect.center();
}

QString QGVLine::projTooltip(const QPointF& projPos) const
{
    if (getMap() == nullptr) {
        return QString("");
    }

    const auto geo = getMap()->getProjection()->projToGeo(projPos);
    return "Line with color " + mColor.name() + "\nPosition " + geo.latToString() + " " + geo.lonToString();
}

QTransform QGVLine::projTransform() const
{
    return QGV::createTransfromAzimuth(projAnchor(), 0);
}

void QGVLine::move(const QGV::GeoPos& firstGeoPos, const QGV::GeoPos& secondGeoPos)
{
    mGeoFirstPoint = firstGeoPos;
    mGeoSecondPoint = secondGeoPos;

    mGeoRect = QGV::GeoRect(mGeoFirstPoint, mGeoSecondPoint);
    mRect = getMap()->getProjection()->geoToProj(mGeoRect);

    resetBoundary();
    refresh();
    repaint();
}
