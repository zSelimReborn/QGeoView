
#include "QGVUtils.h"

#include <QGeoCoordinate>

qreal QGVUtils::getDistanceBetweenGeoPos(const QGV::GeoPos& first, const QGV::GeoPos& second)
{
    const QGeoCoordinate firstGeo{first.latitude(), first.longitude()};
    const QGeoCoordinate secondGeo{second.latitude(), second.longitude()};

    return firstGeo.distanceTo(secondGeo);
}

qreal QGVUtils::getBearingBetweenGeoPos(const QGV::GeoPos& first, const QGV::GeoPos& second)
{
    const QGeoCoordinate firstGeo{first.latitude(), first.longitude()};
    const QGeoCoordinate secondGeo{second.latitude(), second.longitude()};

    return firstGeo.azimuthTo(secondGeo);
}

void QGVUtils::getDistanceAndBearingBetweenGeoPos(const QGV::GeoPos& first, const QGV::GeoPos& second, qreal& distance, qreal& bearing)
{
    const QGeoCoordinate firstGeo{first.latitude(), first.longitude()};
    const QGeoCoordinate secondGeo{second.latitude(), second.longitude()};

    distance = firstGeo.distanceTo(secondGeo);
    bearing = firstGeo.azimuthTo(secondGeo);
}

QGV::GeoPos QGVUtils::getPositionAtDistanceAndBearing(const QGV::GeoPos& currentPosition, const qreal& meters, const qreal& azimuth)
{
    const QGeoCoordinate geoPos{currentPosition.latitude(), currentPosition.longitude()};
    const QGeoCoordinate newPos = geoPos.atDistanceAndAzimuth(meters, azimuth);

    return QGV::GeoPos(newPos.latitude(), newPos.longitude());
}
