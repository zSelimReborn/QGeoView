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

    const QString layerJson = ":/resources/map.geojson";
    mLayerJson = new QGVLayerGeoJson(geoMap()->rootItem(), layerJson);
    // Uncomment here for geojson layer
    geoMap()->addItem(mLayerJson);
    mLayerJson->activate();

    const QString layerPointESRIShp = ":/resources/POINT.shp";
    const QString layerPointESRIShx = ":/resources/POINT.shx";

    const QString layerPolylineESRIShp = ":/resources/POLYLINE.shp";
    const QString layerPolylineESRIShx = ":/resources/POLYLINE.shx";

    const QString layerPolygonESRIShp = ":/resources/POLYGON.shp";
    const QString layerPolygonESRIShx = ":/resources/POLYGON.shx";

    QTemporaryDir tempDir;
    if (tempDir.isValid()) {
      const QString tempPointFile = tempDir.path() + "/point.shp";
      const QString tempPointShxFile = tempDir.path() + "/point.shx";
      const QString tempPolylineFile = tempDir.path() + "/polyline.shp";
      const QString tempPolylineShxFile = tempDir.path() + "/polyline.shx";
      const QString tempPolygonFile = tempDir.path() + "/polygon.shp";
      const QString tempPolygonShxFile = tempDir.path() + "/polygon.shx";

      if (QFile::copy(layerPointESRIShp, tempPointFile) &&
              QFile::copy(layerPointESRIShx, tempPointShxFile) &&
              QFile::copy(layerPolylineESRIShp, tempPolylineFile) &&
              QFile::copy(layerPolylineESRIShx, tempPolylineShxFile) &&
              QFile::copy(layerPolygonESRIShp, tempPolygonFile) &&
              QFile::copy(layerPolygonESRIShx, tempPolygonShxFile)) {

          // Source file must be an absolute path to a file (not qt resource)
          mLayerESRI = new QGVLayerESRI(geoMap()->rootItem(), tempPointFile);
          geoMap()->addItem(mLayerESRI);
          mLayerESRI->activate();

          mLayerESRI->setSourceFileName(tempPolylineFile);
          mLayerESRI->activate();

          mLayerESRI->setSourceFileName(tempPolygonFile);
          mLayerESRI->activate();
      }
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

