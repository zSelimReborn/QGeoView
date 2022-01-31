#include "QGVShapeIcon.h"

QGVShapeIcon::QGVShapeIcon(QGVItem* parent, const QGVLayerItemData& itemData, const QString& iconUrl) :
    QGVIcon(parent, QGV::GeoPos(),iconUrl, QSize(32, 32), {QGV::ItemFlag::IgnoreScale}),
    QGVLayerShape(itemData)
{
    const auto geoCoordinates = getCoordinates();
    const auto geoPoint = geoCoordinates.first();

    setGeometry(geoPoint, size(), anchor());
    refresh();
}
