#include "vectorlayers.h"

#include <QGeoView/QGVGlobal.h>
#include <QGeoView/QGVLayerGeoJson.h>
#include <QGeoView/QGVLayerESRI.h>

#include <QTemporaryDir>

VectorLayersDemo::VectorLayersDemo(QGVMap* geoMap, QObject* parent)
    : DemoItem(geoMap, SelectorDialog::Multi, parent)
{}

QString VectorLayersDemo::label() const
{
    return "Vectorial Layers";
}

QString VectorLayersDemo::comment() const
{
    return "QGV now can import vectorial layers. This includes:<br>"
           "- GeoJSON format<br>"
           "- Shapefile format<br>";
}

void VectorLayersDemo::onInit()
{

    const QString layerJson = ":/resources/italy.geojson";
    mLayerJson = new QGVLayerGeoJson(geoMap()->rootItem(), layerJson);

    geoMap()->addItem(mLayerJson);
    mLayerJson->activate();

    const QString layerPointESRIShp = ":/resources/POINT.shp";
    const QString layerPointESRIShx = ":/resources/POINT.shx";
    const QString layerPointESRIDbf = ":/resources/POINT.dbf";

    const QString layerPolylineESRIShp = ":/resources/POLYLINE.shp";
    const QString layerPolylineESRIShx = ":/resources/POLYLINE.shx";
    const QString layerPolylineESRIDbf = ":/resources/POLYLINE.dbf";

    const QString layerPolygonESRIShp = ":/resources/POLYGON.shp";
    const QString layerPolygonESRIShx = ":/resources/POLYGON.shx";
    const QString layerPolygonESRIDbf = ":/resources/POLYGON.dbf";

    QString tempPointFile;
    QString tempPointShxFile;
    QString tempPointDbfFile;

    QString tempPolylineFile;
    QString tempPolylineShxFile;
    QString tempPolylineDbfFile;

    QString tempPolygonFile;
    QString tempPolygonShxFile;
    QString tempPolygonDbfFile;

    if (QGVLayerFile::resourceToDisk(layerPointESRIShp, tempPointFile) &&
            QGVLayerFile::resourceToDisk(layerPointESRIShx, tempPointShxFile) &&
            QGVLayerFile::resourceToDisk(layerPointESRIDbf, tempPointDbfFile) &&
            QGVLayerFile::resourceToDisk(layerPolylineESRIShp, tempPolylineFile) &&
            QGVLayerFile::resourceToDisk(layerPolylineESRIShx, tempPolylineShxFile) &&
            QGVLayerFile::resourceToDisk(layerPolylineESRIDbf, tempPolylineDbfFile) &&
            QGVLayerFile::resourceToDisk(layerPolygonESRIShp, tempPolygonFile) &&
            QGVLayerFile::resourceToDisk(layerPolygonESRIShx, tempPolygonShxFile) &&
            QGVLayerFile::resourceToDisk(layerPolygonESRIDbf, tempPolygonDbfFile)) {
        // Source file must be an absolute path to a file (not qt resource)
        mLayerESRI = new QGVLayerESRI(geoMap()->rootItem(), tempPointFile);
        geoMap()->addItem(mLayerESRI);
        mLayerESRI->activate();

        mLayerESRI->setSourceFileName(tempPolylineFile);
        mLayerESRI->activate();

        mLayerESRI->setSourceFileName(tempPolygonFile);
        mLayerESRI->activate();
    }


    selector()->addItem("Geo JSON", std::bind(&VectorLayersDemo::setSelected, this, mLayerJson, std::placeholders::_1));
    selector()->addItem("ESRI Shapefile", std::bind(&VectorLayersDemo::setSelected, this, mLayerESRI, std::placeholders::_1));
}

void VectorLayersDemo::onStart()
{
    selector()->show();
}

void VectorLayersDemo::onEnd()
{
    selector()->hide();
}

void VectorLayersDemo::setSelected(QGVLayer* layer, bool selected)
{
    if (layer == nullptr) {
        return;
    }

    layer->setVisible(selected);
}

