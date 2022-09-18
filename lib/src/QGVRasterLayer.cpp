

#include "QGVRasterLayer.h"
#include "QGVGeoTiffParser.h"
#include "QGVImage.h"

QGVRasterLayer::QGVRasterLayer(QGVItem* parent, const QString& sourceFile) :
    QGVLayerFile(parent, sourceFile)
{
    mParser = new QGVGeoTiffParser();
}

void QGVRasterLayer::buildShapes()
{
    const auto geoImg = mParser->buildFromFile(getSourceFileName());
    if (geoImg != nullptr) {
        addShape(geoImg);
    }
}


