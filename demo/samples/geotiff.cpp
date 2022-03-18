#include "geotiff.h"
#include "QGeoView/QGVGeoTiffParser.h"
#include "QGeoView/QGVLayerFile.h"

#include "QGeoView/QGVImage.h"

GeoTiffDemo::GeoTiffDemo(QGVMap* geoMap, QObject* parent)
    : DemoItem(geoMap, SelectorDialog::Multi, parent)
{
    mParser = new QGVGeoTiffParser();
}

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
        qDebug() << "[GTiff] Loading tiff:" << tiffTemp;
        const auto geoImg = mParser->buildFromFile(tiffTemp);
        if (geoImg != nullptr) {
            geoMap()->addItem(geoImg);
        }
    }
}

void GeoTiffDemo::onStart()
{
    selector()->show();
}

void GeoTiffDemo::onEnd()
{
    selector()->hide();
}
