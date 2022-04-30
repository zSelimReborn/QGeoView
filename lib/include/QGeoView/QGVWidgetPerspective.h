#ifndef QGVWIDGETPERSPECTIVE_H
#define QGVWIDGETPERSPECTIVE_H

#include "QGVWidget.h"

#include <QSlider>

class QGV_LIB_DECL QGVWidgetPerspective : public QGVWidget
{
public:
    QGVWidgetPerspective();

    void setSliderMax(const int&);
    int getSliderMax() const;

    void setSliderMin(const int&);
    int getSliderMin() const;

    void setSliderStep(const int&);
    int getSliderStep() const;

    void setSliderTickPosition(const QSlider::TickPosition&);
    QSlider::TickPosition getSliderTickPosition() const;

    void setSliderOrientation(const Qt::Orientation&);
    Qt::Orientation getSliderOrientation() const;

    void rotateMap(const int&);

// Helper methods
private:
    void initializeLayout();
    void initializeSlider();

// Events
private:
    void onSliderChange(int);

private:
    QSlider *mSlider;
    int mCurrentRotation;
};

#endif // QGVWIDGETPERSPECTIVE_H
