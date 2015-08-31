#include "audioitem.h"


void AudioItem::read(const QJsonObject &json)
{
    setId(json["id"].toInt());
    setOwnerId(json["owner_id"].toInt());
    setArtist(json["artist"].toString());
    setTitle(json["title"].toString());
    setDuration(json["duration"].toInt());
    setUrl(QUrl(json["url"].toString()));
    setLyricsId(json["lyrics_id"].toInt());
}

void AudioItem::write(QJsonObject &json) const
{

}
