#ifndef QGVUTILS_H
#define QGVUTILS_H

#include "QGVGlobal.h"

#define OUT

class QGV_LIB_DECL QGVUtils : public QObject
{
    Q_OBJECT

public:
    static qreal getDistanceBetweenGeoPos(const QGV::GeoPos&, const QGV::GeoPos&);
    static qreal getBearingBetweenGeoPos(const QGV::GeoPos&, const QGV::GeoPos&);
    static void getDistanceAndBearingBetweenGeoPos(const QGV::GeoPos&, const QGV::GeoPos&, OUT qreal&, OUT qreal&);
};

#endif // QGVUTILS_H
