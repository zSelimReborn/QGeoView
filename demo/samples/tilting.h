#ifndef TILTING_H
#define TILTING_H

#include "demoitem.h"

class QGVWidgetPerspective;

class TiltingDemo : public DemoItem
{
    Q_OBJECT

public:

    explicit TiltingDemo(QGVMap* geoMap, QObject* parent = 0);

    QString label() const override;

    QString comment() const override;

    void setSelected(QGVWidget* layer, bool selected);
private:
    void onInit() override;

    void onStart() override;

    void onEnd() override;

private:
    QGVWidgetPerspective* mWidget;
};

#endif // TILTING_H
