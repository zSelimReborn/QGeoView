#include "QGVMvtLayerTiles.h"
#include "QGVMVTParser.h"

namespace {
// clang-format off
const QString DefaultUrlTemplate = "https://api.mapbox.com/v4/mapbox.country-boundaries-v1/${z}/${x}/${y}.mvt?access_token=${api_key}";
// clang-format on
}

QGVMvtLayerTiles::QGVMvtLayerTiles(const quint32& tileSize) :
    QGVVectorTilesOnline()
{
    setName("Tilezen vector tiles");
    setDescription("");

    mTileSize = tileSize;
    mUrl = DefaultUrlTemplate;
    mTileType = "all";

    mParser = new QGVMVTParser();
}

QGVMvtLayerTiles::QGVMvtLayerTiles(const quint32& tileSize, const QString& url) :
    QGVMvtLayerTiles(tileSize)
{
    setUrl(url);
}

void QGVMvtLayerTiles::setUrl(const QString &url)
{
    mUrl = url;
}

QString QGVMvtLayerTiles::getUrl() const
{
    return mUrl;
}

void QGVMvtLayerTiles::setTileSize(const quint32& tileSize)
{
    mTileSize = tileSize;
}

quint32 QGVMvtLayerTiles::getTileSize() const
{
    return mTileSize;
}

void QGVMvtLayerTiles::setTileType(const QString& tileType)
{
    /* Tile types of tilezen: {water, landuse, earth, boundaries}
     *
    */
    mTileType = tileType;
}

QString QGVMvtLayerTiles::getTileType() const
{
    return mTileType;
}

int QGVMvtLayerTiles::minZoomlevel() const
{
    return 0;
}

int QGVMvtLayerTiles::maxZoomlevel() const
{
    return 10;
}

QString QGVMvtLayerTiles::tilePosToUrl(const QGV::GeoTilePos &tilePos) const
{
    QString url = mUrl.toLower();
    url.replace("${tilesize}", QString::number(getTileSize()));

    url.replace("${z}", QString::number(tilePos.zoom()));
    url.replace("${x}", QString::number(tilePos.pos().x()));
    url.replace("${y}", QString::number(tilePos.pos().y()));

    if (hasApiKey()) {
        url.replace("${api_key}", getApiKey());
    }

    return url;
}

QList<QGVDrawItem*> QGVMvtLayerTiles::buildShapes(const QGV::GeoTilePos& tile, const QByteArray& data)
{
    return mParser->buildFromContent(tile, data, getTileType());
}

void QGVMvtLayerTiles::setPointsIcon(const QString& icon)
{
    mParser->setPointsIcon(icon);
}

QString QGVMvtLayerTiles::getPointsIcon() const
{
    return mParser->getPointsIcon();
}

void QGVMvtLayerTiles::setLinesColor(const QColor& color)
{
    mParser->setLinesColor(color);
}

QColor QGVMvtLayerTiles::getLinesColor() const
{
    return mParser->getLinesColor();
}

void QGVMvtLayerTiles::setPolygonsColor(const QColor& color)
{
    mParser->setPolygonsColor(color);
}

QColor QGVMvtLayerTiles::getPolygonsColor() const
{
    return mParser->getPolygonsColor();
}
