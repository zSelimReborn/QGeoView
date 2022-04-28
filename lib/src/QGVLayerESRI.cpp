#include "QGVLayerESRI.h"
#include "QGVDBFParser.h"

#include "shapefil.h"
#include <cstring>

QGVLayerESRI::QGVLayerESRI(QGVItem* parent, const QString& sourceFile) :
    QGVLayerFile(parent, sourceFile)
{
    initializeMappingShapeTypes();

    mDbfParser = new QGVDBFParser();
    mDbfSourceFile = sourceFile;
}

QGVLayerESRI::QGVLayerESRI(QGVItem* parent, const QString& sourceFile, const QString& dbfSource) :
    QGVLayerESRI(parent, sourceFile)
{
    mDbfSourceFile = dbfSource;
}

QGVLayerShapeType QGVLayerESRI::getShapeTypeFromNumber(const quint8& shapeId)
{
    if (mMappingShapeTypes.contains(shapeId)) {
        return mMappingShapeTypes[shapeId];
    }

    return QGVLayerShapeType();
}

void QGVLayerESRI::initializeMappingShapeTypes()
{
    mMappingShapeTypes.clear();

    mMappingShapeTypes[SHPT_POINT]      = QGVLayerShapeType::Point;
    mMappingShapeTypes[SHPT_ARC]        = QGVLayerShapeType::Line;
    mMappingShapeTypes[SHPT_POLYGON]    = QGVLayerShapeType::Polygon;
}

void QGVLayerESRI::buildShapes()
{
    initializeSourceFileAsCharArray();
    initializeDbfParser();

    // Source file must be and absolute path to a file.
    const auto shpHandle = SHPOpen(mSourceFileNameAsCharArray, "rb");
    if (shpHandle == nullptr) {
        qDebug() << "QGVLayerESRI::buildShapes(): Unable to open" << mSourceFileNameAsCharArray;
        return;
    }

    int nEntities = 0, mShapeType = 0;
    SHPGetInfo(shpHandle, &nEntities, &mShapeType, nullptr, nullptr);
    qDebug() << "QGVLayerESRI::File" << mSourceFileNameAsCharArray << "QGVLayerESRI::Entities" << nEntities << "QGVLayerESRI::Shape_Type" << mShapeType;

    for (int i = 0; i < nEntities; ++i) {
        const auto shape = SHPReadObject(shpHandle, i);
        if (shape == nullptr) {
            continue;
        }

        QGVLayerItemData::GeoCoordinates shapeCoords;
        QGVLayerItemData::Properties shapeProperties = mDbfParser->parseProperties(i);
        const auto shapeType = getShapeTypeFromNumber(shape->nSHPType);

        if (shapeType != QGVLayerShapeType::Point
                && shapeType != QGVLayerShapeType::Line
                && shapeType != QGVLayerShapeType::Polygon) {
            qDebug() << "Shape type not allowed" << shape->nSHPType;
        }

        for (int j = 0; j < shape->nVertices; ++j) {
            const auto longitude = shape->padfX[j], latitude = shape->padfY[j];
            shapeCoords.append(QGV::GeoPos(latitude, longitude));
        }

        QGVLayerItemData itemData{shapeCoords, shapeProperties, shapeType};
        auto newShape = QGVLayerFile::createNewShape(getParent(), itemData);
        if (newShape != nullptr) {
            addShape(newShape);
        }
    }

    SHPClose(shpHandle);
    closeDbfParser();
}

void QGVLayerESRI::initializeSourceFileAsCharArray()
{
    mSourceFileNameAsCharArray = QGVLayerFile::stringToCharArr(getSourceFileName());
}

char* QGVLayerESRI::getSourceFileNameAsCharArray()
{
    return mSourceFileNameAsCharArray;
}

void QGVLayerESRI::setSourceFileName(const QString& fileName)
{
    QGVLayerFile::setSourceFileName(fileName);
    mDbfSourceFile = fileName;
}

QString QGVLayerESRI::getDbfSourceFile() const
{
    return mDbfSourceFile;
}

void QGVLayerESRI::initializeDbfParser()
{
    const auto sourceFile = getDbfSourceFile();
    if (sourceFile.isEmpty() || sourceFile.isNull()) {
        return;
    }

    mDbfParser->setSourceFile(sourceFile);
}

void QGVLayerESRI::closeDbfParser()
{
    mDbfParser->close();
}
