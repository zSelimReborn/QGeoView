#ifndef QGVWIDGETMEASURE_H
#define QGVWIDGETMEASURE_H

#include "QGVWidget.h"
#include "utils/DistanceUnits.hpp"

class QGVIcon;
class QGVWidgetText;
//class QGVLine;

class QGV_LIB_DECL QGVWidgetMeasure : public QGVWidget
{
public:
    QGVWidgetMeasure();
    QGVWidgetMeasure(const DistanceUnits&, const quint8&);
    QGVWidgetMeasure(const QGV::GeoPos&, const QGV::GeoPos&);
    QGVWidgetMeasure(const DistanceUnits&, const quint8&, const QGV::GeoPos&, const QGV::GeoPos&);
    QGVWidgetMeasure(
            const DistanceUnits&,
            const quint8&,
            const QString&,
            const QSize&,
            const QPoint&,
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

    void setIconAnchor(const QPoint&);
    QPoint getIconAnchor();

    void setLeftPinStartingPoint(const QGV::GeoPos&);
    QGV::GeoPos getLeftPinStartingPoint();

    void setRightPinStartingPoint(const QGV::GeoPos&);
    QGV::GeoPos getRightPinStartingPoint();

    void setDistanceLabelPrefix(const QString&);
    QString getDistanceLabelPrefix();

    void setDistanceAnchorEdges(const QSet<Qt::Edge>&);
    QSet<Qt::Edge> getDistanceAnchorEdges();

    void setDistanceLabelAnchor(const QPoint&);
    QPoint getDistanceLabelAnchor();

    void addPinToMap();
private:
    QGVIcon* createNewPin(const QGV::GeoPos&);

    void updateDistanceLabel(const qreal&);

    void onPinMove(const QPointF&);

    void initializeDistanceLabel();
    //void initializePinLine();

private:
    QGVIcon* leftPin;
    QGVIcon* rightPin;
    DistanceUnits mUnit;
    quint8 mAccuracy;

    QString mIconPin;
    QSize mIconSize;
    QPoint mIconAnchor;
    QGV::GeoPos mLeftPinStartingPoint;
    QGV::GeoPos mRightPinStartingPoint;

    QGVWidgetText* mDistanceLabel;
    QString mDistanceLabelPrefix;
    QSet<Qt::Edge> mDistanceAnchorEdges;
    QPoint mDistanceLabelAnchor;

    //QGVLine* mPinLine;
};

#endif // QGVWIDGETMEASURE_H
