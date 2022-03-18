#include "QGVGeoTiffParser.h"
#include "QGVImage.h"
#include "QGVLayerFile.h"

#include <gdal_priv.h>

#include <QtMath>

QGVGeoTiffParser::QGVGeoTiffParser() :
    mDestSpatialRefName{"WGS84"}
{
    GDALAllRegister();
}

void QGVGeoTiffParser::setDestSpatialRefName(const QString& spatialRef)
{
    mDestSpatialRefName = spatialRef;
}

QString QGVGeoTiffParser::getDestSpatialRefName() const
{
    return mDestSpatialRefName;
}

bool QGVGeoTiffParser::loadGeometryFromFile(const QString& fileName, QGV::GeoRect& geometry, const QString& spatialReference)
{
    GDALDataset* tiffDataset;
    const char* realFileName = QGVLayerFile::stringToCharArr(fileName);
    tiffDataset = (GDALDataset*) GDALOpen(realFileName, GA_ReadOnly);
    if (tiffDataset == nullptr) {
        return false;
    }

    qDebug() << QString("[GTiff] Load Geometry Driver: %1").arg(tiffDataset->GetDriver()->GetDescription());

    double geoTransformParameters[6];
    if (tiffDataset->GetGeoTransform(geoTransformParameters) != CE_None) {
        qDebug() << "[GTiff] Error in loading Geometry.";
        return false;
    }

    if (tiffDataset->GetProjectionRef() != NULL) {
        qDebug() << "[GTiff] Projecion detected:" << tiffDataset->GetProjectionRef();
    }

    const auto destSpatialReferenceName = QGVLayerFile::stringToCharArr(spatialReference);
    const auto sourceSpatialRef = tiffDataset->GetSpatialRef();
    OGRSpatialReference destSpatialRef{};
    destSpatialRef.SetWellKnownGeogCS(destSpatialReferenceName);
    OGRCoordinateTransformation *coordinateTransformer = OGRCreateCoordinateTransformation(sourceSpatialRef, &destSpatialRef);
    if (coordinateTransformer == nullptr) {
        qDebug() << "[GTiff] Failed transform coordinates. Invalid Spatial Reference.";
        return false;
    }

    /*
     * Affine transform formula (from GDAL doc):
     * X_geo = GT(0) + X_pixel * GT(1) + Y_line * GT(2)
     * Y_geo = GT(3) + X_pixel * GT(4) + Y_line * GT(5)
    */

    const auto rasterWidth = tiffDataset->GetRasterXSize();
    const auto rasterHeight = tiffDataset->GetRasterYSize();
    const QPointF origin{geoTransformParameters[0], geoTransformParameters[3]};
    const QSizeF pixelSize{geoTransformParameters[1], (geoTransformParameters[5])};
    const auto rowRotation = geoTransformParameters[2];
    const auto columnRotation = geoTransformParameters[4];

    const auto xTopLeftCorner = (origin.x() + 0.f * pixelSize.width() + 0.f * rowRotation);
    const auto yTopLeftCorner = (origin.y() + 0.f * columnRotation + 0.f * pixelSize.height());
    const auto xBottomRightCorner = (origin.x() + rasterWidth * pixelSize.width() + rasterHeight * rowRotation);
    const auto yBottomRightCorner = (origin.y() + rasterWidth * columnRotation + rasterHeight * pixelSize.height());

    double xPoints[] = {xTopLeftCorner, xBottomRightCorner};
    double yPoints[] = {yTopLeftCorner, yBottomRightCorner};

    if (coordinateTransformer->Transform(2, xPoints, yPoints)) {
        const QGV::GeoPos topLeft{xPoints[0], yPoints[0]};
        const QGV::GeoPos bottomRight{xPoints[1], yPoints[1]};
        geometry = QGV::GeoRect(topLeft, bottomRight);
        qDebug() << "[GTiff] Geometry loaded:" << geometry;
    } else {
        qDebug() << "[GTiff] Unable to transform coordinates from" << sourceSpatialRef->GetName() << "to" << destSpatialReferenceName;
        return false;
    }

    return true;
}

QGVImage* QGVGeoTiffParser::buildFromFile(const QString& fileName)
{
    QGV::GeoRect imgGeometry{};
    if (!loadGeometryFromFile(fileName, imgGeometry, getDestSpatialRefName())) {
        return nullptr;
    }

    const QImage img{fileName};

    auto geoImg = new QGVImage();
    geoImg->setGeometry(imgGeometry);
    geoImg->loadImage(img);
    geoImg->setFlags(QGV::ItemFlag::Transformed);

    return geoImg;
}
