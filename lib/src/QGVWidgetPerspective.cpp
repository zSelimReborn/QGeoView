#include "QGVWidgetPerspective.h"

#include "QGVMapQGView.h"

#include <QHBoxLayout>

QGVWidgetPerspective::QGVWidgetPerspective() :
    mCurrentRotation(0)
{
    initializeLayout();
    initializeSlider();
}

void QGVWidgetPerspective::onSliderChange(int value)
{
    rotateMap(value);
}

void QGVWidgetPerspective::rotateMap(const int& degrees)
{
    if (getMap() == nullptr) { return; }
    if (degrees < getSliderMin()) { return; }
    if (degrees > getSliderMax()) { return; }

    const auto rotationToApply = (degrees - mCurrentRotation);
    QTransform pitchTransform{};
    pitchTransform.rotate(rotationToApply, Qt::Axis::XAxis);

    qDebug() << "[Perspective] Map Pitch To Apply" << pitchTransform;

    qDebug() << "[Perspective] Map Transform Pre rotation" << getMap()->geoView()->transform();
    getMap()->geoView()->setTransform(pitchTransform, true);
    // getMap()->geoView()->cameraTo(QGVCameraActions(getMap()).rotateBy(0), true);
    qDebug() << "[Perspective] Map Transform Post rotation" << getMap()->geoView()->transform();

    mCurrentRotation = degrees;
}

void QGVWidgetPerspective::initializeLayout()
{
    setAnchor(QPoint(50, 50), QSet<Qt::Edge>{Qt::Edge::RightEdge, Qt::Edge::TopEdge});

    setLayout(new QHBoxLayout());
    layout()->setSpacing(10);
    layout()->setSizeConstraint(QLayout::SetMinimumSize);
    layout()->setContentsMargins(0, 0, 0, 0);
}

void QGVWidgetPerspective::initializeSlider()
{
    mSlider = new QSlider(Qt::Orientation::Vertical, this);
    mSlider->setMinimum(0);
    mSlider->setMaximum(45);
    mSlider->setSingleStep(5);
    mSlider->setTickPosition(QSlider::TickPosition::TicksLeft);

    if (layout()) {
        layout()->addWidget(mSlider);
    }

    connect(mSlider, &QSlider::valueChanged, this, &QGVWidgetPerspective::onSliderChange);
}

void QGVWidgetPerspective::setSliderMax(const int& max)
{
    mSlider->setMaximum(max);
}

int QGVWidgetPerspective::getSliderMax() const
{
    return mSlider->maximum();
}

void QGVWidgetPerspective::setSliderMin(const int& min)
{
    mSlider->setMinimum(min);
}

int QGVWidgetPerspective::getSliderMin() const
{
    return mSlider->minimum();
}

void QGVWidgetPerspective::setSliderStep(const int& step)
{
    mSlider->setSingleStep(step);
}

int QGVWidgetPerspective::getSliderStep() const
{
    return mSlider->singleStep();
}

void QGVWidgetPerspective::setSliderTickPosition(const QSlider::TickPosition& position)
{
    mSlider->setTickPosition(position);
}

QSlider::TickPosition QGVWidgetPerspective::getSliderTickPosition() const
{
    return mSlider->tickPosition();
}

void QGVWidgetPerspective::setSliderOrientation(const Qt::Orientation& orientation)
{
    mSlider->setOrientation(orientation);
}

Qt::Orientation QGVWidgetPerspective::getSliderOrientation() const
{
    return mSlider->orientation();
}
