#include "audioservice.h"
#include <QUrl>
#include <QString>

AudioService::AudioService()
{

}

QList<AudioItem> AudioService::getAllContactAudio(int ownerId)
{
    return getContactAudio(ownerId, getAudioCount(ownerId));
}

QList<AudioItem> AudioService::getContactAudio(int ownerId, int count)
{
    QUrl url("https://api.vk.com/method/audio.get");
    url.addQueryItem("owner_id", QString::number(ownerId));
    url.addQueryItem("need_user", "0");
    url.addQueryItem("count", QString::number(count));
    url.addQueryItem("v", "5.37");
    //access_token=  //нужен в конце каждого метода
    NotYetImplementedVkUrlExecuteQueryService(url);
}

int AudioService::getAudioCount(int ownerId)
{
    return 4;
}

