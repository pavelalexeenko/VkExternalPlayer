#ifndef AUDIOITEM_H
#define AUDIOITEM_H

#include <QUrl>
#include <QJsonObject>
#include <QString>
#include <QSharedData>

class AudioItem
{
    class AudioItemData : public QSharedData {
    public:
        AudioItemData()
            : id(0)
            , ownerId(0)
            , duration(0)
            , lyricsId(0)
            , albumId(0)
        {
        }
        AudioItemData(const AudioItemData &o)
            : QSharedData()
            , id(o.id)
            , ownerId(o.ownerId)
            , artist(o.artist)
            , title(o.title)
            , duration(o.duration)
            , url(o.url)
            , lyricsId(o.lyricsId)
            , albumId(o.albumId)
        {
        }
        ~AudioItemData(){}

        int id;
        int ownerId;
        QString artist;
        QString title;
        int duration;
        QUrl url;
        int lyricsId;
        int albumId;
    };

public:
    AudioItem():data(new AudioItemData){}
    AudioItem(const AudioItem &audioItem):data(audioItem.data){}
    AudioItem &operator=(const AudioItem &audioItem)
    {
        if (this != &audioItem)
            data.operator=(audioItem.data);
        return *this;
    }

    void setId(int id){data->id = id;}
    void setOwnerId(int ownerId){data->ownerId = ownerId;}
    void setArtist(const QString &artist){data->artist = artist;}
    void setTitle(const QString &title){data->title = title;}
    void setDuration(int duration){data->duration = duration;}
    void setUrl(const QUrl &url){data->url = url;}
    void setLyricsId(int lyricsId){data->lyricsId = lyricsId;}
    void setAlbumId(int albumId){data->albumId = albumId;}

    int getId() const {return data->id;}
    int getOwnerId() const {return data->ownerId;}
    QString getArtist() const {return data->artist;}
    QString getTitle() const {return data->title;}
    int getDuration() const {return data->duration;}
    QUrl getUrl() const {return data->url;}
    int getLyricsId() const {return data->lyricsId;}
    int getAlbumId() const {return data->albumId;}

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

private:
    QSharedDataPointer<AudioItemData> data;
};
#endif // AUDIOITEM_H
