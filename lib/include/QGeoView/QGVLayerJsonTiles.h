#ifndef QGVLAYERJSONTILES_H
#define QGVLAYERJSONTILES_H

#include "QGVVectorTilesOnline.h"

class QGVJsonTileParser;

class QGV_LIB_DECL QGVLayerJsonTiles : public QGVVectorTilesOnline
{
    Q_OBJECT

public:
    QGVLayerJsonTiles(const quint32&);
    QGVLayerJsonTiles(const quint32&, const QString&);

    void setUrl(const QString& url);
    QString getUrl() const;

    void setTileSize(const quint32&);
    quint32 getTileSize() const;

    void setTileType(const QString&);
    QString getTileType() const;

    void setPointsIcon(const QString&);
    QString getPointsIcon() const;

    void setLinesColor(const QColor&);
    QColor getLinesColor() const;

    void setPolygonsColor(const QColor&);
    QColor getPolygonsColor() const;

protected:
    QList<QGVDrawItem*> buildShapes(const QGV::GeoTilePos&, const QByteArray&) override;

private:
    int minZoomlevel() const override;
    int maxZoomlevel() const override;
    QString tilePosToUrl(const QGV::GeoTilePos& tilePos) const override;

private:
    QString mUrl;
    quint32 mTileSize;
    QString mTileType;

    QGVJsonTileParser* mParser;

};

#endif // QGVLAYERJSONTILES_H
