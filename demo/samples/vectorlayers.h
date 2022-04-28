#ifndef VECTORLAYERS_H
#define VECTORLAYERS_H

#include "demoitem.h"

class QGVWidgetMeasure;
class QGVLayerGeoJson;
class QGVLayerESRI;
class QGVLayer;

class VectorLayersDemo : public DemoItem
{
    Q_OBJECT

public:

    explicit VectorLayersDemo(QGVMap* geoMap, QObject* parent = 0);

    QString label() const override;

    QString comment() const override;

    void setSelected(QGVLayer* layer, bool selected);
private:
    void onInit() override;

    void onStart() override;

    void onEnd() override;

private:

    QGVLayerGeoJson* mLayerJson;
    QGVLayerESRI* mLayerESRI;
};

#endif // VECTORLAYERS_H
