#include "MVTUtils.h"
#include "QGVLayerShape.h"

#include <QtMath>

#include <fstream>

QList<QGVDrawItem*> MVTUtils::buildFromFile(const QGV::GeoTilePos& tile, const QString& fileName, const QString& tileType)
{
    const auto fileContent = readFile(fileName);
    return buildShapes(tile, fileContent, tileType);
}

QList<QGVDrawItem*> MVTUtils::buildFromContent(const QGV::GeoTilePos& tile, const std::string& content, const QString& tileType)
{
    return buildShapes(tile, content, tileType);
}

std::string MVTUtils::readFile(const QString& fileName)
{
    const auto path = fileName.toStdString();

    std::ifstream stream(path.c_str(),std::ios_base::in|std::ios_base::binary);
    if (!stream.is_open())
    {
        throw std::runtime_error("could not open: '" + path + "'");
    }
    std::string message(std::istreambuf_iterator<char>(stream.rdbuf()),(std::istreambuf_iterator<char>()));
    stream.close();
    return message;

}

QList<QGVDrawItem*> MVTUtils::buildShapes(const QGV::GeoTilePos& tile, const std::string& fileContent, const QString& tileType)
{
    QList<QGVDrawItem*> shapes{};

    try {
        MVTBuffer buffer{fileContent};
        qDebug() << "[MVT] Buffer Size:" << buffer.getLength();

        for (const auto& layerName : buffer.getLayerNames()) {
            const MVTLayer layer{buffer.getLayer(layerName)};
            if (!layer.isValid()) {
                qDebug() << "[MVT] Layer" << layerName << "not valid. Skipping.";
                continue;
            }

            qDebug() << "[MVT] Parsing layer:" << layer.getName();

            if (layer.getName().toLower() != tileType.toLower()) {
                qDebug() << "[MVT] Layer" << layer.getName() << "to skip.";
                continue;
            }

            const auto featureCount = layer.getFeatureCount();
            if (featureCount == 0) { qDebug() << "[MVT]" << layer.getName() << "empty"; continue; }

            for (int i = 0; i < featureCount; ++i) {
                const MVTFeature feature{layer.getFeature(i), layer};
                const auto featureId = feature.getIdentifier();
                qDebug() << "[MVT] Parsing feature id:" << featureId;

                if (feature.getType() == GeomType::UNKNOWN) {
                    qDebug() << "[MVT] Feature type is UNKNOWN";
                    continue;
                }

                const float scale{1.0f};
                const auto paths = feature.getGeometries(scale);
                for (const auto &path: paths) {
                    QGVLayerItemData::GeoCoordinates coordinates{};
                    QGVLayerItemData::Properties properties{};

                    const auto shapeType{toLayerShapeType(feature.getType())};
                    for (const auto& point : path) {
                        const QGV::GeoPos geoPoint = toLatLong(tile, point, feature.getExtent());
                        coordinates.append(geoPoint);
                    }

                    auto shapeItemData = QGVLayerItemData(coordinates, properties, shapeType);
                    auto shape = QGVLayerFile::createNewShape(nullptr, shapeItemData);
                    shapes.append(shape);
                }
            }
        }
    } catch (const std::exception& exception ) {
        qDebug() << "[MVT] STD EXCEPTION:" << exception.what();
    } catch (const char* exception) {
        qDebug() << "[MVT] GENERIC EXCEPTION:" << exception;
    }


    return shapes;
}

QGV::GeoPos MVTUtils::toLatLong(const QGV::GeoTilePos& tile, const QPoint& point, const std::int32_t& extent)
{

    double size = (double)extent * qPow(2, (double)tile.zoom());
    double x0 = (double)extent * (double)tile.pos().x();
    double y0 = (double)extent * (double)tile.pos().y();

    double dblY = (double)point.y();
    double dblX = (double) point.x();

    double y2 = 180 - (dblY + y0) * 360 / size;
    double lng = (dblX + x0) * 360 / size - 180;
    double lat = 360 / M_PI * qAtan(qExp(y2 * M_PI / 180)) - 90;

    return QGV::GeoPos{lat, lng};
}

QGVLayerShapeType MVTUtils::toLayerShapeType(const GeomType& geomType)
{
    if (geomType == GeomType::POLYGON) {
        return QGVLayerShapeType::Polygon;
    } else if (geomType == GeomType::LINESTRING) {
        return QGVLayerShapeType::Line;
    } else {
        return QGVLayerShapeType::Point;
    }
}

MVTBuffer::MVTBuffer(const std::string& data) :
    mLayers{}
{
    protozero::pbf_reader layersReader{data};
    mContentLength = layersReader.length();

    while (layersReader.next(TileType::LAYERS)) {
        const protozero::data_view layerView = layersReader.get_view();
        protozero::pbf_reader layerReader{layerView};
        QString layerName{};
        bool layerHasName{false};

        while (layerReader.next(LayerType::NAME)) {
            layerName = QString::fromStdString(layerReader.get_string());
            layerHasName = true;
        }

        if (layerHasName) {
            mLayers.insert(layerName, layerView);
        }
    }
}

QList<QString> MVTBuffer::getLayerNames() const
{
    QList<QString> layerNames;
    layerNames.reserve(mLayers.size());

    for (const auto &layer : mLayers.keys()) {
        layerNames.push_back(layer);
    }

    return layerNames;
}

MVTLayer MVTBuffer::getLayer(const QString& layerName)
{
    const auto layerView = mLayers.find(layerName);
    if (layerView == mLayers.end()) {
        return MVTLayer{};
    }

    return MVTLayer{layerView.value()};
}

MVTLayer::MVTLayer() :
    bIsValid{false},
    mName{},
    mVersion{},
    mExtent{},
    mFeatures{}
{

}

MVTLayer::MVTLayer(const protozero::data_view& layerView) :
    MVTLayer()
{
    bIsValid = true;

    protozero::pbf_reader layerReader{layerView};
    while (layerReader.next()) {
        switch (layerReader.tag()) {
        case LayerType::NAME:
            {
                mName = QString::fromStdString(layerReader.get_string());
            }
            break;
        case LayerType::FEATURES:
            {
                mFeatures.push_back(layerReader.get_view());
            }
            break;
        case LayerType::EXTENT:
            {
                mExtent = layerReader.get_uint32();
            }
            break;
        case LayerType::VERSION:
            {
                mVersion = layerReader.get_uint32();
            }
            break;
        default:
            {
                layerReader.skip();
            }
            break;
        }
    }
}

MVTFeature::MVTFeature(const protozero::data_view& featureView, const MVTLayer &layer) :
    mLayer{layer},
    mIdentifier{},
    mType{GeomType::UNKNOWN},
    mGeometries{}
{
    protozero::pbf_reader featureReader{featureView};
    while (featureReader.next()) {
        switch (featureReader.tag()) {
        case FeatureType::ID:
            mIdentifier = featureReader.get_uint64();
            break;
        case FeatureType::TAGS:
            featureReader.get_packed_uint32();
            break;
        case FeatureType::TYPE:
            mType = static_cast<GeomType>(featureReader.get_enum());
            break;
        case FeatureType::GEOMETRY:
            mGeometries = featureReader.get_packed_uint32();
            break;
        default:
            featureReader.skip();
            break;
        }
    }
}

inline quint32 MVTFeature::getVersion() const
{
    return mLayer.getVersion();
}

inline quint64 MVTFeature::getExtent() const
{
    return mLayer.getExtent();
}

std::vector<std::vector<QPoint>> MVTFeature::getGeometries(const float& scale) const
{
    std::uint8_t cmd = 1;
    std::uint32_t length = 0;
    std::int64_t x = 0;
    std::int64_t y = 0;

    std::vector<std::vector<QPoint>> paths;
    paths.emplace_back();

    auto start_itr = mGeometries.begin();
    const auto end_itr = mGeometries.end();
    bool first = true;
    std::uint32_t len_reserve = 0;
    std::size_t extra_coords = 0;
    if (mType == GeomType::LINESTRING) {
        extra_coords = 1;
    } else if (mType == GeomType::POLYGON) {
        extra_coords = 2;
    }
    bool is_point = mType == GeomType::POINT;


    while (start_itr != end_itr) {
        if (length == 0) {
            std::uint32_t cmd_length = static_cast<std::uint32_t>(*start_itr++);
            cmd = cmd_length & 0x7;
            length = len_reserve = cmd_length >> 3;
            // Prevents the creation of vector tiles that would cause
            // a denial of service from massive over allocation. Protection
            // limit is based on the assumption of an int64_t point which is
            // 16 bytes in size and wanting to have a maximum of 1 MB of memory
            // used.
            constexpr std::uint32_t MAX_LENGTH = (1024 * 1024) / 16;
            if (len_reserve > MAX_LENGTH) {
                len_reserve = MAX_LENGTH;
            }
        }

        if (cmd == CommandType::MOVE_TO || cmd == CommandType::LINE_TO) {
            if (length == 0) {
                // If length is still equal to zero after the preceding step, this
                // represents a command with an invalid command count, so we continue here to
                // exit appropriately rather than underflow when we decrement length
                continue;
            }

            --length;

            if (is_point) {
                if (first && cmd == CommandType::MOVE_TO) {
                    // note: this invalidates pointers. So we always
                    // dynamically get the path with paths.back()
                    paths.reserve(len_reserve);
                    first = false;
                }
            } else {
                if (first && cmd == CommandType::LINE_TO) {
                    paths.back().reserve(len_reserve + extra_coords);
                    first = false;
                }
            }

            if (cmd == CommandType::MOVE_TO && !paths.back().empty()) {
                if (paths.back().size() < paths.back().capacity()) {
                    // Assuming we had an invalid length before
                    // lets shrink to fit, just to make sure
                    // we don't have a large capacity vector
                    // just wasting memory
                    paths.back().shrink_to_fit();
                }
                paths.emplace_back();
                if (!is_point) {
                    first = true;
                }
            }

            x += protozero::decode_zigzag32(static_cast<std::uint32_t>(*start_itr++));
            y += protozero::decode_zigzag32(static_cast<std::uint32_t>(*start_itr++));
            float px = ::roundf(static_cast<float>(x) * scale);
            float py = ::roundf(static_cast<float>(y) * scale);
            static const float max_coord = static_cast<float>(std::numeric_limits<int>::max());
            static const float min_coord = static_cast<float>(std::numeric_limits<int>::min());

            if (px > max_coord ||
                px < min_coord ||
                py > max_coord ||
                py < min_coord
                ) {
                throw std::runtime_error("paths outside valid range of coordinate_type");
            } else {
                QPointF point(px, py);
                paths.back().emplace_back(point.toPoint());
            }
        } else if (cmd == CommandType::CLOSE) {
            if (!paths.back().empty()) {
                paths.back().push_back(paths.back()[0]);
            }
            length = 0;
        } else {
            throw std::runtime_error("unknown command");
        }
    }
    if (paths.size() < paths.capacity()) {
        // Assuming we had an invalid length before
        // lets shrink to fit, just to make sure
        // we don't have a large capacity vector
        // just wasting memory
        paths.shrink_to_fit();
    }

    return paths;
}
