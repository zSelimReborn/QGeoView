#include "MVTUtils.h"

#include <QtMath>

#include <fstream>

#include <protozero/pbf_reader.hpp>
#include "protobuf/QGVMvtTypes.h"

using packed_iterator_type = protozero::iterator_range<protozero::pbf_reader::const_uint32_iterator>;

QList<QGVDrawItem*> MVTUtils::buildFromFile(const QGV::GeoTilePos& tile, const QString& fileName)
{
    const auto fileContent = readFile(fileName);
    return buildShapes(tile, fileContent);
}

QList<QGVDrawItem*> MVTUtils::buildFromContent(const QGV::GeoTilePos& tile, const std::string& content)
{
    return buildShapes(tile, content);
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

QList<QGVDrawItem*> MVTUtils::buildShapes(const QGV::GeoTilePos& tile, const std::string& fileContent)
{
    QList<QGVDrawItem*> shapes{};

    protozero::pbf_reader pbfReader{fileContent};

    qDebug() << "File size: " << pbfReader.length();

    std::vector<protozero::data_view> features{};
    std::uint32_t extent{};
    std::uint32_t version{};

    try {
        // Start parsing layers
        while (pbfReader.next()) {
            if (pbfReader.tag() == TileType::LAYERS) {
                protozero::pbf_reader layerReader {pbfReader.get_view()};
                std::string layerName {};
                bool hasName = false;


                while (layerReader.next()) {
                    switch (layerReader.tag()) {
                    case LayerType::NAME:
                        {
                            layerName = layerReader.get_string();
                            hasName = true;
                            const auto name = QString::fromStdString(layerName);
                            qDebug() << "LAYER NAME: " << name;
                        }
                        break;
                    case LayerType::FEATURES:
                        {
                            features.push_back(layerReader.get_view());
                        }
                        break;
                    case LayerType::EXTENT:
                        {
                            extent = layerReader.get_uint32();
                        }
                        break;
                    case LayerType::VERSION:
                        {
                            version = layerReader.get_uint32();
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
        }

        // Start parsing features
        for (const auto& feature : features) {
            protozero::pbf_reader featureReader{feature};
            std::uint64_t featureId{};
            GeomType type{};
            packed_iterator_type geometryIterator{};
            packed_iterator_type tagsIterator{};

            while (featureReader.next()) {
                switch (featureReader.tag()) {
                case FeatureType::ID:
                    featureId = featureReader.get_uint64();
                    break;
                case FeatureType::TAGS:
                    tagsIterator = featureReader.get_packed_uint32();
                    break;
                case FeatureType::TYPE:
                    type = static_cast<GeomType>(featureReader.get_enum());
                    break;
                case FeatureType::GEOMETRY:
                    geometryIterator = featureReader.get_packed_uint32();
                    break;
                default:
                    featureReader.skip();
                    break;
                }
            }

            qDebug() << "Feature: ID:" << featureId << "Type:" << type;

            // Start parsing geometries
            std::uint8_t cmd = 1;
            std::uint32_t length = 0;
            std::int64_t x = 0;
            std::int64_t y = 0;
            const float scale = 1.0;

            std::vector<std::vector<QPoint>> paths;
            paths.emplace_back();

            auto start_itr = geometryIterator.begin();
            const auto end_itr = geometryIterator.end();
            bool first = true;
            std::uint32_t len_reserve = 0;
            std::size_t extra_coords = 0;
            if (type == GeomType::LINESTRING) {
                extra_coords = 1;
            } else if (type == GeomType::POLYGON) {
                extra_coords = 2;
            }
            bool is_point = type == GeomType::POINT;


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

            for (const auto& path: paths) {
                for (const auto& point: path) {
                    const auto geoPoint = toLatLong(tile, point, extent);
                    qDebug() << geoPoint;
                }
            }
        }
    } catch (const std::exception& exception ) {
        qDebug() << "ECCEZIONE: " << exception.what();
    } catch (const char* exception) {
        qDebug() << "ECCEZIONE: " << exception;
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
