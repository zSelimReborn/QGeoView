#ifndef MVTVECTORLAYER_H
#define MVTVECTORLAYER_H

#include "demoitem.h"

class QGVMvtLayerTiles;

class MVTVectorLayerDemo : public DemoItem
{
    Q_OBJECT

public:

    explicit MVTVectorLayerDemo(QGVMap* geoMap, QObject* parent = 0);

    QString label() const override;

    QString comment() const override;

private:
    void onInit() override;

    void onStart() override;

    void onEnd() override;

private:
    QGVMvtLayerTiles* mMvtLayer;
};

#endif // MVTVECTORLAYER_H
