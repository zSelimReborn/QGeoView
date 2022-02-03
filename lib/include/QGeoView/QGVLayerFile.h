#ifndef QGVLAYERFILE_H
#define QGVLAYERFILE_H

#include <QVector>
#include <QMap>
#include <QVariant>

#include "QGVLayer.h"

enum class QGVLayerShapeType
{
    Point,
    Line,
    Polygon
};

struct QGV_LIB_DECL QGVLayerItemData
{
    QVector<QGV::GeoPos> mCoords;
    QMap<QString, QVariant> mProps;
    QGVLayerShapeType mType;


    using GeoCoordinates = QVector<QGV::GeoPos>;
    using Properties = QMap<QString, QVariant>;

    QGVLayerItemData(const GeoCoordinates&, const Properties&, const QGVLayerShapeType&);
    GeoCoordinates getCoordinates();
    Properties getProperties();
    QGVLayerShapeType getType();
    QVariant getProperty(const QString&);
};

class QGV_LIB_DECL QGVLayerFile : public QGVLayer
{
public:
    QGVLayerFile(QGVItem*, const QString&);

    void setSourceFileName(const QString&);
    QString getSourceFileName();

    void activate();

    static QGVDrawItem* createNewShape(QGVItem*, QGVLayerItemData&);

protected:
    void addShape(QGVDrawItem*);
    void clearShapes();

    virtual void buildShapes() = 0;
    void addShapesToMap();

private:
    QString mSourceFileName;
    QVector<QGVDrawItem*> mShapes;
};

#endif // QGVLAYERFILE_H
