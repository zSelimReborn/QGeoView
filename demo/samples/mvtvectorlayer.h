#ifndef MVTVECTORLAYER_H
#define MVTVECTORLAYER_H

#include "demoitem.h"

class QGVLayer;
class QGVMvtLayerTiles;

class MVTVectorLayerDemo : public DemoItem
{
    Q_OBJECT

public:

    explicit MVTVectorLayerDemo(QGVMap* geoMap, QObject* parent = 0);

    QString label() const override;

    QString comment() const override;

    void setSelected(QGVLayer* layer, bool selected);

private:
    void onInit() override;

    void onStart() override;

    void onEnd() override;

private:
    QGVMvtLayerTiles* mMvtLayer;
};

#endif // MVTVECTORLAYER_H
