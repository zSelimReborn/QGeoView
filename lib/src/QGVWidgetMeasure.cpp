#include "QGVWidgetMeasure.h"
#include "QGVIcon.h"
#include "QGVUtils.h"
#include "QGVWidgetText.h"

#include <QHBoxLayout>
#include <QPaintEvent>
#include <QPainter>

QGVWidgetMeasure::QGVWidgetMeasure() :
    mUnit(DistanceUnits::Kilometers),
    mAccuracy(2),
    mIconPin(":/resources/pin-icon.png"),
    mIconSize(32, 32),
    mLeftPinStartingPoint(0, 0),
    mRightPinStartingPoint(0, 1),
    mDistanceLabelPrefix("Distance: "),
    mDistanceAnchorEdges({Qt::TopEdge, Qt::LeftEdge}),
    mDistanceLabelAnchor(5, 5)
{
    setMouseTracking(true);
    setAnchor(QPoint(10, 10), { Qt::LeftEdge, Qt::TopEdge });
    setMaximumSize(QSize(100, 100));
    setMinimumSize(QSize(100, 100));
}

QGVWidgetMeasure::QGVWidgetMeasure(const DistanceUnits& unit, const quint8& accuracy) :
    QGVWidgetMeasure()
{
    setUnit(unit);
    setAccuracy(accuracy);
}

QGVWidgetMeasure::QGVWidgetMeasure(const QGV::GeoPos& leftPinStartingPoint, const QGV::GeoPos& rightPinStartingPoint) :
    QGVWidgetMeasure()
{
    setLeftPinStartingPoint(leftPinStartingPoint);
    setRightPinStartingPoint(rightPinStartingPoint);
}

QGVWidgetMeasure::QGVWidgetMeasure(const DistanceUnits& unit,
    const quint8& accuracy,
    const QString& iconPin,
    const QSize& iconSize,
    const QGV::GeoPos& leftPinStartingPoint,
    const QGV::GeoPos& rightPinStartingPoint
) : QGVWidgetMeasure(unit, accuracy)
{
    setIconPin(iconPin);
    setIconSize(iconSize);
    setLeftPinStartingPoint(leftPinStartingPoint);
    setRightPinStartingPoint(rightPinStartingPoint);
}

void QGVWidgetMeasure::setUnit(const DistanceUnits &unit)
{
    mUnit = unit;
}

DistanceUnits QGVWidgetMeasure::getUnit()
{
    return mUnit;
}

void QGVWidgetMeasure::setAccuracy(const quint8 &accuracy)
{
    mAccuracy = accuracy;
}

quint8 QGVWidgetMeasure::getAccuracy()
{
    return mAccuracy;
}

void QGVWidgetMeasure::setIconPin(const QString &iconPin)
{
    mIconPin = iconPin;
}

QString QGVWidgetMeasure::getIconPin()
{
    return mIconPin;
}

void QGVWidgetMeasure::setIconSize(const QSize &iconSize)
{
    mIconSize = iconSize;
}

QSize QGVWidgetMeasure::getIconSize()
{
    return mIconSize;
}

void QGVWidgetMeasure::setLeftPinStartingPoint(const QGV::GeoPos &pos)
{
    mLeftPinStartingPoint = pos;
}

QGV::GeoPos QGVWidgetMeasure::getLeftPinStartingPoint()
{
    return mLeftPinStartingPoint;
}

void QGVWidgetMeasure::setRightPinStartingPoint(const QGV::GeoPos &pos)
{
    mRightPinStartingPoint = pos;
}

QGV::GeoPos QGVWidgetMeasure::getRightPinStartingPoint()
{
    return mRightPinStartingPoint;
}

void QGVWidgetMeasure::setDistanceLabelPrefix(const QString& distanceLabelPrefix)
{
    mDistanceLabelPrefix = distanceLabelPrefix;
}

QString QGVWidgetMeasure::getDistanceLabelPrefix()
{
    return mDistanceLabelPrefix;
}

void QGVWidgetMeasure::setDistanceAnchorEdges(const QSet<Qt::Edge>& edges)
{
    mDistanceAnchorEdges = edges;
}

QSet<Qt::Edge> QGVWidgetMeasure::getDistanceAnchorEdges()
{
    return mDistanceAnchorEdges;
}

void QGVWidgetMeasure::setDistanceLabelAnchor(const QPoint& anchor)
{
    mDistanceLabelAnchor = anchor;
}

QPoint QGVWidgetMeasure::getDistanceLabelAnchor()
{
    return mDistanceLabelAnchor;
}

QGVIcon* QGVWidgetMeasure::createNewPin(const QGV::GeoPos& pos)
{
    auto iconFlags = QGV::ItemFlag::Movable | QGV::ItemFlag::Transformed | QGV::ItemFlag::IgnoreScale;

    QGVIcon* newIcon = new QGVIcon(getMap()->rootItem(), pos, getIconPin(), getIconSize(), iconFlags);
    return newIcon;
}

void QGVWidgetMeasure::addPinToMap()
{
    if (getMap() == nullptr) {
        return;
    }

    leftPin = createNewPin(getLeftPinStartingPoint());
    rightPin = createNewPin(getRightPinStartingPoint());

    initializeDistanceLabel();

    getMap()->addItem(leftPin);
    getMap()->addItem(rightPin);

    connect(leftPin, &QGVIcon::onMove, this, &QGVWidgetMeasure::onPinMove);
    connect(rightPin, &QGVIcon::onMove, this, &QGVWidgetMeasure::onPinMove);

    onPinMove(QPointF());
}

void QGVWidgetMeasure::onPinMove(const QPointF &)
{
    const auto leftPinPos = leftPin->pos();
    const auto rightPinPos = rightPin->pos();

    const auto distance = QGVUtils::getDistanceBetweenGeoPos(leftPinPos, rightPinPos);
    updateDistanceLabel(distance);
}

void QGVWidgetMeasure::initializeDistanceLabel()
{
    if (getMap() == nullptr) {
        return;
    }

    mDistanceLabel = new QGVWidgetText();
    mDistanceLabel->setText(getDistanceLabelPrefix());
    const auto edges = getDistanceAnchorEdges();
    mDistanceLabel->setAnchor(getDistanceLabelAnchor(), edges);

    getMap()->addWidget(mDistanceLabel);
}

void QGVWidgetMeasure::updateDistanceLabel(const qreal &meters)
{
    QString result;
    double miles, nauticalMiles = 0.f;

    switch (mUnit) {
        case DistanceUnits::Kilometers:
            if (meters > 1000) {
                result = tr("%1: %2 km").arg(getDistanceLabelPrefix()).arg(QString::number(static_cast<double>(meters) / 1000, 'f', mAccuracy));
            } else {
                result = tr("%1: %2 m").arg(getDistanceLabelPrefix()).arg(QString::number(static_cast<double>(meters), 'f', mAccuracy));
            }
        break;
        case DistanceUnits::Miles:
            miles = meters / 1609.0;

            if (miles > 1) {
                result = tr("%1: %2 mi").arg(getDistanceLabelPrefix()).arg(QString::number(static_cast<double>(miles), 'f', mAccuracy));
            } else {
                result = tr("%1: %2 m").arg(getDistanceLabelPrefix()).arg(QString::number(static_cast<double>(meters), 'f', mAccuracy));
            }
        break;
        case DistanceUnits::NauticalMiles:
            nauticalMiles = meters / 1852.0;

            if (nauticalMiles > 1) {
                result = tr("%1: %2 nm").arg(getDistanceLabelPrefix()).arg(QString::number(static_cast<double>(nauticalMiles), 'f', mAccuracy));
            } else {
                result = tr("%1: %2 m").arg(getDistanceLabelPrefix()).arg(QString::number(static_cast<double>(nauticalMiles), 'f', mAccuracy));
            }
        break;
    }

    mDistanceLabel->setText(result);
}
