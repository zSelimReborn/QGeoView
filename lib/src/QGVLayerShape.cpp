#include "QGVLayerShape.h"

QGVLayerShape::QGVLayerShape(const QGVLayerItemData& itemData) :
    mShapeData(itemData)
{

}

QGVLayerItemData QGVLayerShape::getShapeData()
{
    return mShapeData;
}

QVariant QGVLayerShape::getProperty(const QString& property)
{
    return mShapeData.getProperty(property);
}

bool QGVLayerShape::hasProperty(const QString& property)
{
    return mShapeData.getProperties().contains(property);
}

QGVLayerItemData::GeoCoordinates QGVLayerShape::getCoordinates()
{
    return mShapeData.getCoordinates();
}

QGVLayerShapeType QGVLayerShape::getType()
{
    return mShapeData.getType();
}
