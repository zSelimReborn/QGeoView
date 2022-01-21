#include "QGVIcon.h"


QGVIcon::QGVIcon(QGVItem* parent, const QGV::GeoPos& geoPos, const QString& iconPath, const QGV::ItemFlags& iconFlags)
{
    setParent(parent);
    setFlag(QGV::ItemFlag::IgnoreScale);
    setFlag(QGV::ItemFlag::IgnoreAzimuth);
    setFlag(QGV::ItemFlag::Highlightable);
    setFlag(QGV::ItemFlag::HighlightCustom);
    setFlag(QGV::ItemFlag::Highlightable);
    setFlag(QGV::ItemFlag::Transformed);
    setFlags(iconFlags);

    setGeometry(geoPos, QSize(32, 32), QPoint(16, 32));

    const QImage icon(iconPath);
    if (icon.isNull()) {
        qDebug() << "Image null: " << iconPath;
    } else {
        qDebug() << "Image ok: " << icon.size();
    }
    loadImage(icon);

    refresh();

    qDebug() << "Position: " << pos();
}

QGV::GeoPos QGVIcon::pos()
{
    auto transform = projAnchor();
    if (getMap() == nullptr) {
        return QGV::GeoPos();
    }

    return getMap()->getProjection()->projToGeo(transform);
}

void QGVIcon::projOnObjectStartMove(const QPointF& pos)
{
    QGVImage::projOnObjectStartMove(pos);
    if (isFlag(QGV::ItemFlag::Movable)) {
        emit onStartMove(pos);
    }
}

void QGVIcon::projOnObjectMovePos(const QPointF& pos)
{
    QGVImage::projOnObjectMovePos(pos);

    if (getMap()) {
        auto geoPos = getMap()->getProjection()->projToGeo(pos);
        setGeometry(geoPos, QSize(32, 32), QPoint(16, 32));
        refresh();
    }

    if (isFlag(QGV::ItemFlag::Movable)) {
        emit onMove(pos);
    }
}

void QGVIcon::projOnObjectStopMove(const QPointF& pos)
{
    QGVImage::projOnObjectStopMove(pos);
    if (isFlag(QGV::ItemFlag::Movable)) {
        emit onStopMove(pos);
    }
}
