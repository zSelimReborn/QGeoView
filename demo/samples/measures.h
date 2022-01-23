#ifndef MEASURES_H
#define MEASURES_H

#include "demoitem.h"

class QGVWidgetMeasure;

class MeasuresDemo : public DemoItem
{
    Q_OBJECT

public:
    explicit MeasuresDemo(QGVMap* geoMap, QObject* parent = 0);

    QString label() const override;
    QString comment() const override;

private:
    void onInit() override;
    void onStart() override;
    void onEnd() override;
    void setSelected(QGVWidget* widget, bool selected);

private:
    QGVWidgetMeasure* mWidgetMeasure;
};

#endif // MEASURES_H
