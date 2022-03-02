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

    /* QTemporaryDir tempDir;
    const QString mvtFile = ":/resources/shapes.mvt";
    const QString mvtTempFile = tempDir.path() + "/shapes.mvt";

    if (tempDir.isValid()) {
        if (QFile::copy(mvtFile, mvtTempFile)) {
            try {
                const QGV::GeoTilePos tile{1, QPoint(0, 0)};
                const auto shapes = MVTUtils::buildFromFile(tile, mvtTempFile, "country_boundaries");
                qDebug() << "Created" << shapes.size() << "shapes";
                for (const auto& shape : shapes) {
                    geoMap()->addItem(shape);
                }
            }  catch (const std::exception& exception) {
                qDebug() << "[MVT] ERROR READING FILE:" << exception.what();
            }
        }
    } */

    //QGV::setPrintDebug(true);
    const quint32 tileSize{512};
    const QString apiUrl{"https://tile.nextzen.org/tilezen/vector/v1/${tilesize}/all/${z}/${x}/${y}.mvt?api_key=${api_key}"};
    const QString apiKey{"*****"};
    const QString tileType{"boundaries"};

    mMvtLayer = new QGVMvtLayerTiles(tileSize, apiUrl);
    mMvtLayer->setApiKey(apiKey);
    mMvtLayer->setTileType(tileType);

    geoMap()->addItem(mMvtLayer);

    selector()->addItem("MVT Layer", std::bind(&MVTVectorLayerDemo::setSelected, this, mMvtLayer, std::placeholders::_1));
}

void MVTVectorLayerDemo::onStart()
{
    selector()->show();
}

void MVTVectorLayerDemo::onEnd()
{
    selector()->hide();
}

void MVTVectorLayerDemo::setSelected(QGVLayer* layer, bool selected)
{
    if (layer == nullptr) {
        return;
    }

    layer->setVisible(selected);
}
