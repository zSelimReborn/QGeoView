#ifndef QGVWIDGETMEASURE_H
#define QGVWIDGETMEASURE_H

#include "QGVWidget.h"
#include "utils/DistanceUnits.hpp"

class QGVIcon;

class QGV_LIB_DECL QGVWidgetMeasure : public QGVWidget
{
public:
    QGVWidgetMeasure();
    QGVWidgetMeasure(const DistanceUnits&, const quint8&);
    QGVWidgetMeasure(const QGV::GeoPos&, const QGV::GeoPos&);
    QGVWidgetMeasure(
            const DistanceUnits&,
            const quint8&,
            const QString&,
            const QSize&,
            const QGV::GeoPos&,
            const QGV::GeoPos&
    );

    void setUnit(const DistanceUnits&);
    DistanceUnits getUnit();

    void setAccuracy(const quint8&);
    quint8 getAccuracy();

    void setIconPin(const QString&);
    QString getIconPin();

    void setIconSize(const QSize&);
    QSize getIconSize();

    void setLeftPinStartingPoint(const QGV::GeoPos&);
    QGV::GeoPos getLeftPinStartingPoint();

    void setRightPinStartingPoint(const QGV::GeoPos&);
    QGV::GeoPos getRightPinStartingPoint();

    void addPinToMap();
private:
    QGVIcon* createNewPin(const QGV::GeoPos&);

    void updateDistanceLabel(const qreal&);

    void onPinMove(const QPointF&);

private:
    QGVIcon* leftPin;
    QGVIcon* rightPin;
    DistanceUnits mUnit;
    quint8 mAccuracy;

    QString mIconPin;
    QSize mIconSize;
    QGV::GeoPos mLeftPinStartingPoint;
    QGV::GeoPos mRightPinStartingPoint;
};

#endif // QGVWIDGETMEASURE_H
