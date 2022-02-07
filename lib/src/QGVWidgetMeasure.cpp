#include "QGVWidgetMeasure.h"
#include "QGVIcon.h"
#include "QGVUtils.h"
#include "QGVLine.h"
#include "QGVBallon.h"

#include <QPaintEvent>
#include <QPainter>
#include <QHBoxLayout>
#include <QToolButton>

QGVWidgetMeasure::QGVWidgetMeasure() :
    bIsActive(false),
    mUnit(DistanceUnits::Kilometers),
    mAccuracy(2),
    mIconPin(":/resources/pin-icon.png"),
    mIconPinMovement(mIconPin),
    mIconSize(32, 32),
    mIconAnchor(mIconSize.width() / 2, mIconSize.height()),
    mLeftPinStartingPoint(0, 0),
    mRightPinStartingPoint(0, 1),
    mPinStartingPointMetersOffset(5000),
    mLeftPinAzimuthOffset(60),
    mRightPinAzimuthOffset(240),
    mDistanceLabelPrefix("Distance: "),
    mBearingLabelPrefix("Bearing: "),
    mBallonValueSeparator("|"),
    mBallonBackgroundColor(Qt::blue),
    mBallonTextColor(Qt::white),
    mBallonTextPadding(5),
    mLineColor(Qt::blue),
    mLineWidth(1500),
    mWidgetAnchorEdges({Qt::RightEdge, Qt::TopEdge}),
    mWidgetBtnIcon(":/resources/compass.png"),
    mWidgetBtnSize(40, 40),
    mBtnExternalRectColor(Qt::white),
    mBtnExternalRectBorderColor(Qt::blue),
    mBtnInternalRectColor(Qt::white),
    mBtnActiveInternalRectColor(Qt::blue)
{
    Q_INIT_RESOURCE(resources);
    setAnchor(QPoint(15, 15), mWidgetAnchorEdges);
    /* setMaximumSize(QSize(100, 100));
    setMinimumSize(QSize(100, 100)); */

    // Layout build
    initializeLayout();

    // Crea pulsante
    initializeWidgetButton();
}

QGVWidgetMeasure::QGVWidgetMeasure(const DistanceUnits& unit, const quint8& accuracy) :
    QGVWidgetMeasure()
{
    setUnit(unit);
    setAccuracy(accuracy);
}

QGVWidgetMeasure::QGVWidgetMeasure(const DistanceUnits& unit,
    const quint8& accuracy,
    const QString& iconPin,
    const QSize& iconSize,
    const QPoint& iconAnchor
) : QGVWidgetMeasure(unit, accuracy)
{
    setIconPin(iconPin);
    setIconPinMovement(iconPin);
    setIconSize(iconSize);
    setIconAnchor(iconAnchor);
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

void QGVWidgetMeasure::setIconPinMovement(const QString& iconPin)
{
    mIconPinMovement = iconPin;
}

QString QGVWidgetMeasure::getIconPinMovement()
{
    return mIconPinMovement;
}

void QGVWidgetMeasure::setIconSize(const QSize &iconSize)
{
    mIconSize = iconSize;
}

QSize QGVWidgetMeasure::getIconSize()
{
    return mIconSize;
}

void QGVWidgetMeasure::setIconAnchor(const QPoint &iconAnchor)
{
    mIconAnchor = iconAnchor;
}

QPoint QGVWidgetMeasure::getIconAnchor()
{
    return mIconAnchor;
}

QGV::GeoPos QGVWidgetMeasure::getLeftPinStartingPoint()
{
    const qreal metersOffset = getPinStartingPointMetersOffset(); // Meters
    const qreal azimuthOffset = getLeftPinAzimuthOffset(); // Degrees

    mLeftPinStartingPoint = calculateMiddlePosition(metersOffset, azimuthOffset);
    return mLeftPinStartingPoint;
}

QGV::GeoPos QGVWidgetMeasure::getRightPinStartingPoint()
{
    const qreal metersOffset = getPinStartingPointMetersOffset(); // Meters
    const qreal azimuthOffset = getRightPinAzimuthOffset(); // Degrees

    mRightPinStartingPoint = calculateMiddlePosition(metersOffset, azimuthOffset);
    return mRightPinStartingPoint;
}

void QGVWidgetMeasure::setPinStartingPointMetersOffset(const qreal& meters)
{
    mPinStartingPointMetersOffset = meters;
}

qreal QGVWidgetMeasure::getPinStartingPointMetersOffset()
{
    return mPinStartingPointMetersOffset;
}

void QGVWidgetMeasure::setLeftPinAzimuthOffset(const qreal& azimuth)
{
    mLeftPinAzimuthOffset = azimuth;
}

qreal QGVWidgetMeasure::getLeftPinAzimuthOffset()
{
    return mLeftPinAzimuthOffset;
}

void QGVWidgetMeasure::setRightPinAzimuthOffset(const qreal& azimuth)
{
    mRightPinAzimuthOffset = azimuth;
}

qreal QGVWidgetMeasure::getRightPinAzimuthOffset()
{
    return mRightPinAzimuthOffset;
}

void QGVWidgetMeasure::setDistanceLabelPrefix(const QString& distanceLabelPrefix)
{
    mDistanceLabelPrefix = distanceLabelPrefix;
}

QString QGVWidgetMeasure::getDistanceLabelPrefix()
{
    return mDistanceLabelPrefix;
}

void QGVWidgetMeasure::setBearingLabelPrefix(const QString& bearingLabelPrefix)
{
    mBearingLabelPrefix = bearingLabelPrefix;
}

QString QGVWidgetMeasure::getBearingLabelPrefix()
{
    return mBearingLabelPrefix;
}

void QGVWidgetMeasure::setBallonValueSeparator(const QString& ballonValueSeparator)
{
    mBallonValueSeparator = ballonValueSeparator;
}

QString QGVWidgetMeasure::getBallonValueSeparator()
{
    return mBallonValueSeparator;
}

void QGVWidgetMeasure::setBallonBackgroundColor(const QColor& background)
{
    mBallonBackgroundColor = background;
}

QColor QGVWidgetMeasure::getBallonBackgroundColor()
{
    return mBallonBackgroundColor;
}

void QGVWidgetMeasure::setBallonTextColor(const QColor& textColor)
{
    mBallonTextColor = textColor;
}

QColor QGVWidgetMeasure::getBallonTextColor()
{
    return mBallonTextColor;
}

void QGVWidgetMeasure::setBallonTextPadding(const int& textPadding)
{
    mBallonTextPadding = textPadding;
}

int QGVWidgetMeasure::getBallonTextPadding()
{
    return mBallonTextPadding;
}

void QGVWidgetMeasure::setLineColor(const QColor& lineColor)
{
    mLineColor = lineColor;
}

QColor QGVWidgetMeasure::getLineColor()
{
    return mLineColor;
}

void QGVWidgetMeasure::setLineWidth(const quint16& lineWidth)
{
    mLineWidth = lineWidth;
}

quint16 QGVWidgetMeasure::getLineWidth()
{
    return mLineWidth;
}

void QGVWidgetMeasure::showPinLine()
{
    if (mPinLine != nullptr) { mPinLine->showLine(); }
}

void QGVWidgetMeasure::hidePinLine()
{
    if (mPinLine != nullptr) { mPinLine->hideLine(); }
}

bool QGVWidgetMeasure::shouldShowPinLine()
{
    if (mPinLine != nullptr) { return mPinLine->shouldShowLine(); }
    return false;
}

QGVIcon* QGVWidgetMeasure::createNewPin(const QGV::GeoPos& pos)
{
    const int pinZValue = 20;
    auto iconFlags = QGV::ItemFlag::Movable | QGV::ItemFlag::Transformed | QGV::ItemFlag::IgnoreScale;

    QGVIcon* newIcon = new QGVIcon(getMap()->rootItem(), pos, getIconPin(), getIconSize(), getIconAnchor(), iconFlags);
    newIcon->setIconMovement(getIconPinMovement());
    newIcon->setZValue(pinZValue);

    return newIcon;
}

QGVBallon* QGVWidgetMeasure::createNewBallon(const QGV::GeoPos& pos)
{
    const int extraMargin = 20, ballonZValue = 30;

    QGVBallon* newBallon = new QGVBallon(getMap()->rootItem(), pos, getDistanceLabelPrefix());
    newBallon->setBallonBackground(getBallonBackgroundColor());
    newBallon->setBallonTextColor(getBallonTextColor());
    newBallon->setBallonTextPadding(getBallonTextPadding());
    newBallon->setMarginBottom(getIconSize().height() + extraMargin);
    newBallon->setZValue(ballonZValue);

    return newBallon;
}

void QGVWidgetMeasure::addPinToMap()
{
    if (getMap() == nullptr) {
        return;
    }

    leftPin = createNewPin(getLeftPinStartingPoint());
    rightPin = createNewPin(getRightPinStartingPoint());

    leftBallon = createNewBallon(getLeftPinStartingPoint());
    rightBallon = createNewBallon(getRightPinStartingPoint());
    rightBallon->hideBallon();

    getMap()->addItem(leftPin);
    getMap()->addItem(rightPin);

    getMap()->addItem(leftBallon);
    getMap()->addItem(rightBallon);

    initializePinLine();

    connect(leftPin, &QGVIcon::onMove, this, &QGVWidgetMeasure::onPinMove);
    connect(rightPin, &QGVIcon::onMove, this, &QGVWidgetMeasure::onPinMove);

    connect(leftPin, &QGVIcon::onStartMove, this, &QGVWidgetMeasure::onLeftPinStartMove);
    connect(rightPin, &QGVIcon::onStartMove, this, &QGVWidgetMeasure::onRightPinStartMove);

    onPinMove(QPointF());
}

void QGVWidgetMeasure::removePinFromMap()
{
    if (getMap() == nullptr) {
        return;
    }

    if (leftPin) {
        getMap()->removeItem(leftPin);
    }

    if (rightPin) {
        getMap()->removeItem(rightPin);
    }

    if (leftBallon) {
        getMap()->removeItem(leftBallon);
    }

    if (rightBallon) {
        getMap()->removeItem(rightBallon);
    }

    if (mPinLine) {
        getMap()->removeItem(mPinLine);
    }
}

void QGVWidgetMeasure::onPinMove(const QPointF &)
{
    const auto leftPinPos = leftPin->pos();
    const auto rightPinPos = rightPin->pos();

    const auto distance = QGVUtils::getDistanceBetweenGeoPos(leftPinPos, rightPinPos);

    const auto leftBallonBearing = QGVUtils::getBearingBetweenGeoPos(rightPinPos, leftPinPos);
    const auto rightBallonBearing = QGVUtils::getBearingBetweenGeoPos(leftPinPos, rightPinPos);

    updateBallons(distance, leftBallonBearing, rightBallonBearing);
    moveBallons();
    moveLine();
}

void QGVWidgetMeasure::onLeftPinStartMove(const QPointF &)
{
    leftBallon->showBallon();
    rightBallon->hideBallon();
}

void QGVWidgetMeasure::onRightPinStartMove(const QPointF &)
{
    leftBallon->hideBallon();
    rightBallon->showBallon();
}

void QGVWidgetMeasure::updateBallons(const qreal& distanceMeters, const qreal& leftBallonBearing, const qreal& rightBallonBearing)
{
    const auto distanceLabel = getDistanceLabel(distanceMeters);
    const auto leftBallonText = distanceLabel + " " + getBallonValueSeparator() + " " + getBearingLabel(leftBallonBearing);
    const auto rightBallonText = distanceLabel + " " + getBallonValueSeparator() + " "+ getBearingLabel(rightBallonBearing);

    leftBallon->setBallonText(leftBallonText);
    rightBallon->setBallonText(rightBallonText);

    leftBallon->repaint();
    rightBallon->repaint();
}

void QGVWidgetMeasure::moveBallons()
{
    const auto leftPinPos = (leftPin->pos());
    const auto rightPinPos = (rightPin->pos());

    if (leftBallon->shouldShowBallon()) {
        leftBallon->move(leftPinPos);
    } else if (rightBallon->shouldShowBallon()) {
        rightBallon->move(rightPinPos);
    }
}

void QGVWidgetMeasure::moveLine()
{
    const auto leftPinPos = (leftPin->pos());
    const auto rightPinPos = (rightPin->pos());

    mPinLine->move(leftPinPos, rightPinPos);
}

void QGVWidgetMeasure::initializePinLine()
{
    if (getMap() == nullptr) {
        return;
    }

    const int lineZValue = 10;

    mPinLine = new QGVLine(getMap()->rootItem(), getLeftPinStartingPoint(), getRightPinStartingPoint(), getLineColor());
    mPinLine->setWidth(getLineWidth());
    mPinLine->setZValue(lineZValue);

    getMap()->addItem(mPinLine);
}

QString QGVWidgetMeasure::getDistanceLabel(const qreal& meters)
{
    QString result;
    double miles, nauticalMiles = 0.f;

    const double milesFactor = 1609.0f;
    const double nauticalMilesFactor = 1852.0f;

    switch (mUnit) {
        case DistanceUnits::Kilometers:
            if (meters > 1000) {
                result = tr("%1 %2 km").arg(getDistanceLabelPrefix()).arg(QString::number(static_cast<double>(meters) / 1000, 'f', mAccuracy));
            } else {
                result = tr("%1 %2 m").arg(getDistanceLabelPrefix()).arg(QString::number(static_cast<double>(meters), 'f', mAccuracy));
            }
        break;
        case DistanceUnits::Miles:
            miles = meters / milesFactor;

            if (miles > 1) {
                result = tr("%1 %2 mi").arg(getDistanceLabelPrefix()).arg(QString::number(static_cast<double>(miles), 'f', mAccuracy));
            } else {
                result = tr("%1 %2 m").arg(getDistanceLabelPrefix()).arg(QString::number(static_cast<double>(meters), 'f', mAccuracy));
            }
        break;
        case DistanceUnits::NauticalMiles:
            nauticalMiles = meters / nauticalMilesFactor;

            if (nauticalMiles > 1) {
                result = tr("%1 %2 nm").arg(getDistanceLabelPrefix()).arg(QString::number(static_cast<double>(nauticalMiles), 'f', mAccuracy));
            } else {
                result = tr("%1 %2 m").arg(getDistanceLabelPrefix()).arg(QString::number(static_cast<double>(nauticalMiles), 'f', mAccuracy));
            }
        break;
    }

    return result;
}

QString QGVWidgetMeasure::getBearingLabel(const qreal& degrees)
{
    QString result;

    result = tr("%1 %2°").arg(getBearingLabelPrefix()).arg(QString::number(static_cast<double>(degrees), 'f', 0));
    return result;
}

void QGVWidgetMeasure::setWidgetAnchorEdges(const QSet<Qt::Edge>& edges)
{
    mWidgetAnchorEdges = edges;
    const auto oldPointAnchor = getAnchor();

    setAnchor(oldPointAnchor.toPoint(), mWidgetAnchorEdges);
}

QSet<Qt::Edge> QGVWidgetMeasure::getWidgetAnchorEdges()
{
    return mWidgetAnchorEdges;
}

void QGVWidgetMeasure::setWidgetBtnIcon(const QString& btnIcon)
{
    mWidgetBtnIcon = btnIcon;

    refreshWidgetButton();
}

QString QGVWidgetMeasure::getWidgetBtnIcon()
{
    return mWidgetBtnIcon;
}

void QGVWidgetMeasure::setWidgetBtnSize(const QSize& btnSize)
{
    mWidgetBtnSize = btnSize;

    refreshWidgetButton();
}

QSize QGVWidgetMeasure::getWidgetBtnSize()
{
    return mWidgetBtnSize;
}

void QGVWidgetMeasure::setBtnExternalRectColor(const QColor& rectColor)
{
    mBtnExternalRectColor = rectColor;
    repaint();
}

void QGVWidgetMeasure::setBtnExternalBorderColor(const QColor& borderColor)
{
    mBtnExternalRectBorderColor = borderColor;
    repaint();
}

void QGVWidgetMeasure::setBtnInternalRectColor(const QColor& rectColor)
{
    mBtnInternalRectColor = rectColor;
    repaint();
}

void QGVWidgetMeasure::setBtnActiveInternalRectColor(const QColor& rectColor)
{
    mBtnActiveInternalRectColor = rectColor;
    repaint();
}

QColor QGVWidgetMeasure::getBtnExternalRectColor()
{
    return mBtnExternalRectColor;
}

QColor QGVWidgetMeasure::getBtnExternalBorderColor()
{
    return mBtnExternalRectBorderColor;
}

QColor QGVWidgetMeasure::getBtnInternalRectColor()
{
    return mBtnInternalRectColor;
}

QColor QGVWidgetMeasure::getBtnActiveInternalRectColor()
{
    return mBtnActiveInternalRectColor;
}

void QGVWidgetMeasure::onWidgetBtnClick()
{
    if (!isActive()) {
        activateWidget();
    } else {
        deactivateWidget();
    }
}

void QGVWidgetMeasure::activateWidget()
{
    bIsActive = true;

    addPinToMap();
    repaint();
}

void QGVWidgetMeasure::deactivateWidget()
{
    bIsActive = false;

    removePinFromMap();
    repaint();
}

bool QGVWidgetMeasure::isActive()
{
    return bIsActive;
}

void QGVWidgetMeasure::initializeLayout()
{
    setLayout(new QHBoxLayout());
    layout()->setSpacing(10);
    layout()->setSizeConstraint(QLayout::SetMinimumSize);
    layout()->setContentsMargins(0, 0, 0, 0);
}

void QGVWidgetMeasure::initializeWidgetButton()
{
    // Tyler Durden will forgive me
    const auto customStylesheet = "QToolButton { background-color: transparent; border: 0; padding: 10px; }";

    mWidgetActivateBtn = new QToolButton(this);
    mWidgetActivateBtn->setAutoRepeat(true);
    mWidgetActivateBtn->setToolButtonStyle(Qt::ToolButtonIconOnly);
    mWidgetActivateBtn->setIcon(QIcon(mWidgetBtnIcon));
    mWidgetActivateBtn->setIconSize(mWidgetBtnSize);
    mWidgetActivateBtn->setStyleSheet(customStylesheet);
    mWidgetActivateBtn->setCursor(QCursor(Qt::PointingHandCursor));

    if (layout()) {
        layout()->addWidget(mWidgetActivateBtn);
        // Associa click ai pulsanti
        connect(mWidgetActivateBtn, &QToolButton::clicked, this, &QGVWidgetMeasure::onWidgetBtnClick);
    }
}

void QGVWidgetMeasure::refreshWidgetButton()
{
    if (mWidgetActivateBtn == nullptr) {
        return;
    }

    mWidgetActivateBtn->setIcon(QIcon(getWidgetBtnIcon()));
    mWidgetActivateBtn->setIconSize(getWidgetBtnSize());
}

QGV::GeoPos QGVWidgetMeasure::calculateMiddlePosition(const qreal& meters, const qreal& azimuth)
{
    const auto middleScreen = getMap()->getCamera().projCenter();
    const auto middleScreenGeo = getMap()->getProjection()->projToGeo(middleScreen);

    return QGVUtils::getPositionAtDistanceAndBearing(middleScreenGeo, meters, azimuth);
}

void QGVWidgetMeasure::paintEvent(QPaintEvent *event)
{
    const quint8 rectRoundedCorners = 50;

    const quint8 externalRectOffset = 2;
    const quint8 externalRectExtraSize = 20;
    const quint8 externalRectBorderSize = 2;

    const quint8 internalRectOffset = 7;
    const quint8 internalRectExtraSize = 10;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // External rounded rect
    QPainterPath externalRectPath;
    const QRect externalRect(externalRectOffset, externalRectOffset, getWidgetBtnSize().width() + externalRectExtraSize, getWidgetBtnSize().height() + externalRectExtraSize);
    externalRectPath.addRoundedRect(externalRect, rectRoundedCorners, rectRoundedCorners);

    // External border color
    QPen pen(getBtnExternalBorderColor(), externalRectBorderSize);
    // External rect color
    QBrush rectColor(getBtnExternalRectColor());

    // Draw external rect
    painter.setPen(pen);
    painter.fillPath(externalRectPath, rectColor);
    painter.drawPath(externalRectPath);

    QPainterPath internalRectPath;

    // Internal rounded rect
    const QRect internalRect(internalRectOffset, internalRectOffset, getWidgetBtnSize().width() + internalRectExtraSize, getWidgetBtnSize().height() + internalRectExtraSize);
    internalRectPath.addRoundedRect(internalRect, rectRoundedCorners, rectRoundedCorners);

    // Color based on widget status
    if (isActive()) {
        pen = QPen(getBtnActiveInternalRectColor());
        rectColor = QBrush(getBtnActiveInternalRectColor());
    } else {
        pen = QPen(getBtnInternalRectColor());
        rectColor = QBrush(getBtnInternalRectColor());
    }

    painter.setPen(pen);
    painter.setBrush(rectColor);
    painter.drawPath(internalRectPath);
}
