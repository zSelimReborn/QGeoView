#ifndef QGEOVIEW_MVTUTILS_H
#define QGEOVIEW_MVTUTILS_H

#include "QGVGlobal.h"

#include "protobuf/QGVMvtTypes.h"
#include "QGVLayerFile.h"
#include <protozero/pbf_reader.hpp>

#include <QList>

class QGVDrawItem;

class QGV_LIB_DECL MVTUtils
{
public:
    MVTUtils();
    QList<QGVDrawItem*> buildFromFile(const QGV::GeoTilePos&, const QString&, const QString&);
    QList<QGVDrawItem*> buildFromContent(const QGV::GeoTilePos&, const std::string&, const QString&);
    QGV::GeoPos toLatLong(const QGV::GeoTilePos&, const QPoint&, const std::int32_t&);
    QGVLayerShapeType toLayerShapeType(const GeomType&);

public:
    void setPointsIcon(const QString&);
    QString getPointsIcon() const;

    void setLinesColor(const QColor&);
    QColor getLinesColor() const;

    void setPolygonsColor(const QColor&);
    QColor getPolygonsColor() const;

private:
    std::string readFile(const QString&);
    QList<QGVDrawItem*> buildShapes(const QGV::GeoTilePos&, const std::string&, const QString&);

private:
    QString mPointsIcon;
    QColor mLinesColor;
    QColor mPolygonsColor;
};

using packed_iterator_type = protozero::iterator_range<protozero::pbf_reader::const_uint32_iterator>;

struct MVTLayer;

struct MVTFeature
{
    const struct MVTLayer& mLayer;
    quint64 mIdentifier;
    GeomType mType;
    packed_iterator_type mGeometries;

    MVTFeature(const protozero::data_view&, const struct MVTLayer&);
    inline quint64 getIdentifier() const { return mIdentifier; };
    inline GeomType getType() const { return mType; };
    std::vector<std::vector<QPoint>> getGeometries(const float&) const;
    inline quint32 getVersion() const;
    inline quint64 getExtent() const;
};

struct MVTLayer
{
    using Features = QList<protozero::data_view>;

    QString mName;
    quint32 mVersion;
    quint64 mExtent;
    Features mFeatures;
    bool bIsValid;

    MVTLayer();
    MVTLayer(const protozero::data_view&);
    inline QString getName() const { return mName; };
    inline quint32 getVersion() const { return mVersion; };
    inline quint64 getExtent() const { return mExtent; }
    inline int getFeatureCount() const { return mFeatures.count(); }
    inline Features getFeatures() const { return mFeatures; };
    inline protozero::data_view const& getFeature(const int& index) const { return mFeatures.at(index); };
    inline bool isValid() const { return bIsValid; };
};

struct MVTBuffer
{
    using LayersMap = QMap<QString, protozero::data_view>;

    std::size_t mContentLength;
    LayersMap mLayers;

    MVTBuffer(const std::string&);
    QList<QString> getLayerNames() const;
    inline LayersMap getLayers() const { return mLayers; };
    inline std::size_t getLength() const { return mContentLength; }
    MVTLayer getLayer(const QString&);
};

#endif // QGEOVIEW_MVTUTILS_H
