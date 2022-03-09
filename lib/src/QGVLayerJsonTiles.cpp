#include "QGVLayerJsonTiles.h"
#include "QGVJsonTileParser.h"

namespace {
// clang-format off
const QString DefaultUrlTemplate = "https://api.mapbox.com/v4/mapbox.country-boundaries-v1/${z}/${x}/${y}.mvt?access_token=${api_key}";
// clang-format on
}

QGVLayerJsonTiles::QGVLayerJsonTiles(const quint32& tileSize) :
    QGVVectorTilesOnline()
{
    setName("Tilezen vector tiles from JSON");
    setDescription("");

    mTileSize = tileSize;
    mUrl = DefaultUrlTemplate;
    mTileType = "all";

    mParser = new QGVJsonTileParser();
}

QGVLayerJsonTiles::QGVLayerJsonTiles(const quint32& tileSize, const QString& url) :
    QGVLayerJsonTiles(tileSize)
{
    setUrl(url);
}

void QGVLayerJsonTiles::setUrl(const QString &url)
{
    mUrl = url;
}

QString QGVLayerJsonTiles::getUrl() const
{
    return mUrl;
}

void QGVLayerJsonTiles::setTileSize(const quint32& tileSize)
{
    mTileSize = tileSize;
}

quint32 QGVLayerJsonTiles::getTileSize() const
{
    return mTileSize;
}

void QGVLayerJsonTiles::setTileType(const QString& tileType)
{
    /* Tile types of tilezen: {water, landuse, earth, boundaries}
     *
    */
    mTileType = tileType;
}

QString QGVLayerJsonTiles::getTileType() const
{
    return mTileType;
}

int QGVLayerJsonTiles::minZoomlevel() const
{
    return 0;
}

int QGVLayerJsonTiles::maxZoomlevel() const
{
    return 10;
}

QString QGVLayerJsonTiles::tilePosToUrl(const QGV::GeoTilePos &tilePos) const
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

QList<QGVDrawItem*> QGVLayerJsonTiles::buildShapes(const QGV::GeoTilePos& tile, const QByteArray& data)
{
    return mParser->buildFromContent(tile, data, getTileType());
}

void QGVLayerJsonTiles::setPointsIcon(const QString& icon)
{
    mParser->setPointsIcon(icon);
}

QString QGVLayerJsonTiles::getPointsIcon() const
{
    return mParser->getPointsIcon();
}

void QGVLayerJsonTiles::setLinesColor(const QColor& color)
{
    mParser->setLinesColor(color);
}

QColor QGVLayerJsonTiles::getLinesColor() const
{
    return mParser->getLinesColor();
}

void QGVLayerJsonTiles::setPolygonsColor(const QColor& color)
{
    mParser->setPolygonsColor(color);
}

QColor QGVLayerJsonTiles::getPolygonsColor() const
{
    return mParser->getPolygonsColor();
}
