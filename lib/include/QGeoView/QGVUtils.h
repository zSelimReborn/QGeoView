#ifndef QGVUTILS_H
#define QGVUTILS_H

#include "QGVGlobal.h"

class QGV_LIB_DECL QGVUtils : public QObject
{
    Q_OBJECT

public:
    static qreal getDistanceBetweenGeoPos(const QGV::GeoPos&, const QGV::GeoPos&);
};

#endif // QGVUTILS_H
