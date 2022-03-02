#include "QGVMvtLayerTiles.h"
#include "MVTUtils.h"

namespace {
// clang-format off
const QString DefaultUrlTemplate = "https://api.mapbox.com/v4/mapbox.country-boundaries-v1/${z}/${x}/${y}.mvt?access_token=${api_key}";
// clang-format on
}

QGVMvtLayerTiles::QGVMvtLayerTiles(const quint32& tileSize) :
    mTileSize{tileSize},
    mUrl{DefaultUrlTemplate},
    mTileType{"all"}
{
    setName("Tilezen vector tiles");
    setDescription("");
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
    return MVTUtils::buildFromContent(tile, data.toStdString(), getTileType());
}
