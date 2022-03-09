#include "vectortileslayers.h"

#include "QGeoView/QGVMvtLayerTiles.h"
#include "QGeoView/QGVLayerJsonTiles.h"

#include "QGeoView/QGVDrawItem.h"

#include <QTemporaryDir>

VectorTilesOnlineDemo::VectorTilesOnlineDemo(QGVMap* geoMap, QObject* parent)
    : DemoItem(geoMap, SelectorDialog::Multi, parent)
{}

QString VectorTilesOnlineDemo::label() const
{
    return "Vectorial Layers Online";
}

QString VectorTilesOnlineDemo::comment() const
{
    return "QGV now can request vectorial layers online. This includes:<br>"
           "- MVT format<br>"
           "- PBF format<br>";
}

void VectorTilesOnlineDemo::onInit()
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
    const QString mvtApiUrl{"https://tile.nextzen.org/tilezen/vector/v1/${tilesize}/all/${z}/${x}/${y}.mvt?api_key=${api_key}"};
    const QString apiKey{"*****"};
    const QString tileType{"boundaries"};

    const QString pointsIcon{":/resources/pin-icon-highlight.png"};
    const QColor linesColor{Qt::red};
    const QColor polygonsColor{Qt::red};

    mMvtLayer = new QGVMvtLayerTiles(tileSize, mvtApiUrl);
    mMvtLayer->setApiKey(apiKey);
    mMvtLayer->setTileType(tileType);
    mMvtLayer->setPointsIcon(pointsIcon);
    mMvtLayer->setLinesColor(linesColor);
    mMvtLayer->setPolygonsColor(polygonsColor);

    const QString jsonApiUrl{"https://tile.nextzen.org/tilezen/vector/v1/all/${z}/${x}/${y}.json?api_key=${api_key}"};

    mJsonLayer = new QGVLayerJsonTiles(tileSize, jsonApiUrl);
    mJsonLayer->setApiKey(apiKey);
    mJsonLayer->setTileType("roads");
    mJsonLayer->setPointsIcon(pointsIcon);
    mJsonLayer->setLinesColor(linesColor);
    mJsonLayer->setPolygonsColor(polygonsColor);

    geoMap()->addItem(mMvtLayer);
    geoMap()->addItem(mJsonLayer);

    selector()->addItem("MVT Layer", std::bind(&VectorTilesOnlineDemo::setSelected, this, mMvtLayer, std::placeholders::_1));
    selector()->addItem("JSON Layer", std::bind(&VectorTilesOnlineDemo::setSelected, this, mJsonLayer, std::placeholders::_1));
}

void VectorTilesOnlineDemo::onStart()
{
    selector()->show();
}

void VectorTilesOnlineDemo::onEnd()
{
    selector()->hide();
}

void VectorTilesOnlineDemo::setSelected(QGVLayer* layer, bool selected)
{
    if (layer == nullptr) {
        return;
    }

    layer->setVisible(selected);
}
