#ifndef QGVUTILS_H
#define QGVUTILS_H

#include "QGVGlobal.h"

#define OUT

/**
 * @brief The QGVUtils class is a static class which defines some utility methods for calculation in Geo Coordinate
 */
class QGV_LIB_DECL QGVUtils : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief getDistanceBetweenGeoPos returns the distance (in meters) between two positions (latitude, longitude)
     * @return qreal, double
     */
    static qreal getDistanceBetweenGeoPos(const QGV::GeoPos&, const QGV::GeoPos&);

    /**
     * @brief getBearingBetweenGeoPos returns the bearing (in degrees) between two positions (latitude, longitude)
     * @return qreal, double
     */
    static qreal getBearingBetweenGeoPos(const QGV::GeoPos&, const QGV::GeoPos&);

    /**
     * @brief getDistanceAndBearingBetweenGeoPos calculate the distance (in meters) and the bearing (in degrees) between two points (latitude, longitude).
     * It places the result in the third (distance) and fourth (bearing) parameter.
     */
    static void getDistanceAndBearingBetweenGeoPos(const QGV::GeoPos&, const QGV::GeoPos&, OUT qreal&, OUT qreal&);
};

#endif // QGVUTILS_H
