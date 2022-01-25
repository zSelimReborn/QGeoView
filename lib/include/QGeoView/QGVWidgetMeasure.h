#ifndef QGVWIDGETMEASURE_H
#define QGVWIDGETMEASURE_H

#include "QGVWidget.h"
#include "utils/DistanceUnits.hpp"

class QGVIcon;
class QGVBallon;
class QGVLine;

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

    void setBearingLabelPrefix(const QString&);
    QString getBearingLabelPrefix();

    void setBallonValueSeparator(const QString&);
    QString getBallonValueSeparator();

    void setBallonBackgroundColor(const QColor&);
    QColor getBallonBackgroundColor();

    void setBallonTextColor(const QColor&);
    QColor getBallonTextColor();

    void setBallonTextPadding(const int&);
    int getBallonTextPadding();

    void setLineColor(const QColor&);
    QColor getLineColor();

    void setLineWidth(const quint16&);
    quint16 getLineWidth();

    void showPinLine();
    void hidePinLine();
    bool shouldShowPinLine();

    void addPinToMap();
private:
    QGVIcon* createNewPin(const QGV::GeoPos&);
    QGVBallon* createNewBallon(const QGV::GeoPos&);

    QString getDistanceLabel(const qreal&);
    QString getBearingLabel(const qreal&);

    void onPinMove(const QPointF&);
    void onLeftPinStartMove(const QPointF&);
    void onRightPinStartMove(const QPointF&);

    void updateBallons(const qreal&, const qreal&, const qreal&);
    void moveBallons();
    void moveLine();

    void initializePinLine();

private:
    // Widget functionality
    QGVIcon* leftPin;
    QGVIcon* rightPin;
    DistanceUnits mUnit;
    quint8 mAccuracy;
    QGVBallon* leftBallon;
    QGVBallon* rightBallon;

    // Pin settings
    QString mIconPin;
    QSize mIconSize;
    QPoint mIconAnchor;
    QGV::GeoPos mLeftPinStartingPoint;
    QGV::GeoPos mRightPinStartingPoint;

    // Ballon settings
    QString mDistanceLabelPrefix;
    QString mBearingLabelPrefix;
    QString mBallonValueSeparator;
    QColor mBallonBackgroundColor;
    QColor mBallonTextColor;
    int mBallonTextPadding;

    // Line settings
    QGVLine* mPinLine;
    QColor mLineColor;
    quint16 mLineWidth;
};

#endif // QGVWIDGETMEASURE_H
