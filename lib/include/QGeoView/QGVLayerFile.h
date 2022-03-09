#ifndef QGVLAYERFILE_H
#define QGVLAYERFILE_H

#include <QList>
#include <QMap>
#include <QVariant>
#include <QTemporaryDir>

#include "QGVLayer.h"

enum class QGVLayerShapeType
{
    Point,
    Line,
    Polygon
};

struct QGV_LIB_DECL QGVLayerItemData
{
    QList<QGV::GeoPos> mCoords;
    QMap<QString, QVariant> mProps;
    QGVLayerShapeType mType;


    using GeoCoordinates = QList<QGV::GeoPos>;
    using Properties = QMap<QString, QVariant>;

    QGVLayerItemData(const GeoCoordinates&, const Properties&, const QGVLayerShapeType&);
    GeoCoordinates getCoordinates();
    Properties getProperties();
    QGVLayerShapeType getType();
    QVariant getProperty(const QString&);
    void setProperty(const QString&, const QVariant&);
};

class QGV_LIB_DECL QGVLayerFile : public QGVLayer
{
public:
    QGVLayerFile(QGVItem*, const QString&);

    void setSourceFileName(const QString&);
    QString getSourceFileName();

    void activate();

    static QGVDrawItem* createNewShape(QGVItem*, QGVLayerItemData&);
    static QGVDrawItem* createNewShape(QGVItem*, QGVLayerItemData&, const QString&, const QColor&, const QColor&);

    static bool resourceToDisk(const QString&, QString&);
    static char* stringToCharArr(const QString&);

protected:
    void addShape(QGVDrawItem*);
    void clearShapes();

    virtual void buildShapes() = 0;
    void addShapesToMap();

private:
    QString mSourceFileName;
    QList<QGVDrawItem*> mShapes;

private:
    static QTemporaryDir internalTempDir;
};

#endif // QGVLAYERFILE_H
