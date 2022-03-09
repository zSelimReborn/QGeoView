#include "QGVLayerFile.h"

#include "QGVDrawItem.h"
#include "QGVLayerShape.h"
#include "QGVShapeIcon.h"
#include "QGVShapePolygon.h"
#include "QGVShapeLine.h"

QTemporaryDir QGVLayerFile::internalTempDir{};

QGVLayerFile::QGVLayerFile(QGVItem* parent, const QString& sourceFileName) :
    mSourceFileName(sourceFileName)
{
    setParent(parent);
}

void QGVLayerFile::setSourceFileName(const QString& sourceFileName)
{
    mSourceFileName = sourceFileName;
}

QString QGVLayerFile::getSourceFileName()
{
    return mSourceFileName;
}

void QGVLayerFile::activate()
{
    buildShapes();
    addShapesToMap();
}

void QGVLayerFile::addShape(QGVDrawItem* shape)
{
    mShapes.append(shape);
}

void QGVLayerFile::clearShapes()
{
    for (const auto shape : qAsConst(mShapes)) {
        removeItem(shape);
    }

    mShapes.clear();
}

void QGVLayerFile::addShapesToMap()
{
    for (const auto shape : qAsConst(mShapes)) {
        removeItem(shape);
        addItem(shape);
    }
}

QGVLayerItemData::QGVLayerItemData(const GeoCoordinates& coords, const Properties& props, const QGVLayerShapeType& type) :
    mCoords(coords),
    mProps(props),
    mType(type)
{ }

QGVLayerItemData::GeoCoordinates QGVLayerItemData::getCoordinates()
{
    return mCoords;
}

QGVLayerItemData::Properties QGVLayerItemData::getProperties()
{
    return mProps;
}

QGVLayerShapeType QGVLayerItemData::getType()
{
    return mType;
}

QVariant QGVLayerItemData::getProperty(const QString& prop)
{
    return mProps.value(prop);
}

void QGVLayerItemData::setProperty(const QString& property, const QVariant& value)
{
    mProps.insert(property, value);
}

QGVDrawItem* QGVLayerFile::createNewShape(QGVItem* parent, QGVLayerItemData& itemData)
{
    const QString shapeIcon = ":/resources/pin-icon.png";

    switch (itemData.getType()) {
        case QGVLayerShapeType::Point:
            return new QGVShapeIcon(parent, itemData, shapeIcon);
            break;
        case QGVLayerShapeType::Line:
            return new QGVShapeLine(parent, itemData);
            break;
        case QGVLayerShapeType::Polygon:
            return new QGVShapePolygon(parent, itemData);
            break;
    }

    return nullptr;
}

QGVDrawItem* QGVLayerFile::createNewShape(QGVItem* parent, QGVLayerItemData& itemData, const QString& pointIcon, const QColor& lineColor, const QColor& polygonColor)
{
    switch (itemData.getType()) {
        case QGVLayerShapeType::Point:
            return new QGVShapeIcon(parent, itemData, pointIcon);
            break;
        case QGVLayerShapeType::Line:
            itemData.setProperty("stroke", lineColor);
            return new QGVShapeLine(parent, itemData);
            break;
        case QGVLayerShapeType::Polygon:
            itemData.setProperty("stroke", polygonColor);
            itemData.setProperty("fill", polygonColor);
            itemData.setProperty("fill-opacity", 0.5);
            return new QGVShapePolygon(parent, itemData);
            break;
    }

    return nullptr;
}

bool QGVLayerFile::resourceToDisk(const QString& resourceFile, QString& diskFile)
{
    if (!QGVLayerFile::internalTempDir.isValid()) { return false; }

    QFileInfo fileInfo{resourceFile};
    const auto fileName = fileInfo.fileName();

    if (fileName.isEmpty() || fileName.isNull()) { return false; }

    diskFile = QGVLayerFile::internalTempDir.path() + "/" + fileName;
    return QFile::copy(resourceFile, diskFile);
}

char* QGVLayerFile::stringToCharArr(const QString& str)
{
    const auto fileAsByte = str.toLocal8Bit();

    char* strAsArray = new char[str.length() + 1];
    snprintf(strAsArray, str.length() + 1, "%s", fileAsByte.data());

    return strAsArray;
}
