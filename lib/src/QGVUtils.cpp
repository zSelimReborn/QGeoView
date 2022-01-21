
#include "QGVUtils.h"

#include <QGeoCoordinate>

qreal QGVUtils::getDistanceBetweenGeoPos(const QGV::GeoPos& first, const QGV::GeoPos& second)
{
    const QGeoCoordinate firstGeo{first.latitude(), first.longitude()};
    const QGeoCoordinate secondGeo{second.latitude(), second.longitude()};

    return firstGeo.distanceTo(secondGeo);
}
