

#include "geotiff.h"
#include "QGeoView/QGVRasterLayer.h"

GeoTiffDemo::GeoTiffDemo(QGVMap* geoMap, QObject* parent)
    : DemoItem(geoMap, SelectorDialog::Multi, parent)
{ }

QString GeoTiffDemo::label() const
{
    return "GeoTiff importer";
}

QString GeoTiffDemo::comment() const
{
    return "QGV now can import and show a geotiff file";
}

void GeoTiffDemo::onInit()
{
    const QString tiffResource = ":/resources/venice.tif";
    QString tiffTemp;

    if (QGVLayerFile::resourceToDisk(tiffResource, tiffTemp)) {
        mLayer = new QGVRasterLayer(nullptr, tiffTemp);
        qDebug() << "[GTiff] Loading tiff:" << tiffTemp;

        geoMap()->addItem(mLayer);
        mLayer->activate();

        selector()->addItem("GeoTiff Layer", std::bind(&GeoTiffDemo::setSelected, this, mLayer, std::placeholders::_1));
    }
}

void GeoTiffDemo::setSelected(QGVLayer* layer, bool selected)
{
    if (layer == nullptr) {
        return;
    }

    layer->setVisible(selected);
}

void GeoTiffDemo::onStart()
{
    selector()->show();
}

void GeoTiffDemo::onEnd()
{
    selector()->hide();
}


