#include "mvtvectorlayer.h"

#include "QGeoView/MVTUtils.h"
#include "QGeoView/QGVMvtLayerTiles.h"

#include "QGeoView/QGVDrawItem.h"

#include <QTemporaryDir>

MVTVectorLayerDemo::MVTVectorLayerDemo(QGVMap* geoMap, QObject* parent)
    : DemoItem(geoMap, SelectorDialog::Multi, parent)
{}

QString MVTVectorLayerDemo::label() const
{
    return "Vectorial Layers Online";
}

QString MVTVectorLayerDemo::comment() const
{
    return "QGV now can request vectorial layers online. This includes:<br>"
           "- MVT format<br>"
           "- PBF format<br>";
}

void MVTVectorLayerDemo::onInit()
{

    QTemporaryDir tempDir;
    const QString mvtFile = ":/resources/shapes.mvt";
    const QString mvtTempFile = tempDir.path() + "/shapes.mvt";

    if (tempDir.isValid()) {
        if (QFile::copy(mvtFile, mvtTempFile)) {
            try {
                const QGV::GeoTilePos tile{6, QPoint(42, 17)};
                const auto shapes = MVTUtils::buildFromFile(tile, mvtTempFile, "boundaries");
                qDebug() << "Created" << shapes.size() << "shapes";
                for (const auto& shape : shapes) {
                    geoMap()->addItem(shape);
                }
            }  catch (const std::exception& exception) {
                qDebug() << "[MVT] ERROR READING FILE:" << exception.what();
            }
        }
    }

    /* QGV::setPrintDebug(true);
    const quint32 tileSize{256};
    const QString apiKey{"*****"};
    const QString tileType{"boundaries"};

    mMvtLayer = new QGVMvtLayerTiles(tileSize);
    mMvtLayer->setApiKey(apiKey);
    mMvtLayer->setTileType(tileType);

    geoMap()->addItem(mMvtLayer); */

    selector()->selectAll();
}

void MVTVectorLayerDemo::onStart()
{
    selector()->show();
}

void MVTVectorLayerDemo::onEnd()
{
    selector()->hide();
}
