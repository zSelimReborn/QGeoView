#include "QGVIcon.h"


QGVIcon::QGVIcon(QGVItem* parent, const QGV::GeoPos& geoPos, const QString& iconPath, const QSize& iconSize, const QGV::ItemFlags& iconFlags) :
    mSize(iconSize), mAnchor(mSize.width() / 2, mSize.height() / 2)
{
    setParent(parent);
    setFlags(iconFlags);

    setGeometry(geoPos, mSize, mAnchor);

    const QImage icon(iconPath);
    loadImage(icon);

    refresh();
}

QGVIcon::QGVIcon(QGVItem* parent, const QGV::GeoPos& geoPos, const QString& iconPath, const QSize& iconSize, const QPoint& iconAnchor, const QGV::ItemFlags& iconFlags) :
    QGVIcon(parent, geoPos, iconPath, iconSize, iconFlags)
{
    mAnchor = iconAnchor;
    setGeometry(geoPos, mSize, mAnchor);
    refresh();
}

QGV::GeoPos QGVIcon::pos()
{
    auto transform = projAnchor();
    if (getMap() == nullptr) {
        return QGV::GeoPos();
    }

    return getMap()->getProjection()->projToGeo(transform);
}

QSize QGVIcon::size()
{
    return mSize;
}

QPoint QGVIcon::anchor()
{
    return mAnchor;
}

void QGVIcon::projOnObjectStartMove(const QPointF& pos)
{
    QGVImage::projOnObjectStartMove(pos);

    // Emit signal only if icon is movable
    if (isFlag(QGV::ItemFlag::Movable)) {
        emit onStartMove(pos);
    }
}

void QGVIcon::projOnObjectMovePos(const QPointF& pos)
{
    QGVImage::projOnObjectMovePos(pos);

    if (getMap()) {
        auto geoPos = getMap()->getProjection()->projToGeo(pos);
        setGeometry(geoPos, mSize, mAnchor);
        refresh();
    }

    // Emit signal only if icon is movable
    if (isFlag(QGV::ItemFlag::Movable)) {
        emit onMove(pos);
    }
}

void QGVIcon::projOnObjectStopMove(const QPointF& pos)
{
    QGVImage::projOnObjectStopMove(pos);

    // Emit signal only if icon is movable
    if (isFlag(QGV::ItemFlag::Movable)) {
        emit onStopMove(pos);
    }
}
