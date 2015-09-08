#include "audioservice.h"
#include <QUrl>
#include <QUrlQuery>
#include <QString>
#include <QDebug>
#include "../objects/audioitem.h"
#include "../instancefactory.h"
#include "loginservice.h"
#include "urlqueryexecuteservice.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QByteArray>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

AudioService::AudioService(QObject *parent) : QObject(parent)
{

}

QList<AudioItem> AudioService::getCurrentUsersAllContactAudio()
{
    return getAllContactAudio(InstanceFactory<LoginService>::getInstance()->getUserId());
}

QList<AudioItem> AudioService::getCurrentUsersContactAudio(int count)
{
    return getContactAudio(InstanceFactory<LoginService>::getInstance()->getUserId(), count);
}

int AudioService::getCurrentUsersAudioCount()
{
    return getAudioCount(InstanceFactory<LoginService>::getInstance()->getUserId());
}

QList<AudioItem> AudioService::getAllContactAudio(int ownerId)
{
    return getContactAudio(ownerId, getAudioCount(ownerId));
}

QList<AudioItem> AudioService::getContactAudio(int ownerId, int count)
{
    qDebug() << __FUNCTION__;

    QUrl url;
    url.setScheme("https");
    url.setHost("api.vk.com");
    url.setPath("/method/audio.get");

    QUrlQuery urlQuery;
    urlQuery.addQueryItem("owner_id", QString::number(ownerId));
    urlQuery.addQueryItem("need_user", "0");
    urlQuery.addQueryItem("count", QString::number(count));
    urlQuery.addQueryItem("v", "5.37");
    urlQuery.addQueryItem("access_token", InstanceFactory<LoginService>::getInstance()->getToken());
    url.setQuery(urlQuery);

    return toAudioItemList(InstanceFactory<UrlQueryExecuteService>::getInstance()->executeUrl(url));
}

int AudioService::getAudioCount(int ownerId)
{
    qDebug() << __FUNCTION__;

    QUrl url;
    url.setScheme("https");
    url.setHost("api.vk.com");
    url.setPath("/method/audio.getCount");

    QUrlQuery urlQuery;
    urlQuery.addQueryItem("owner_id", QString::number(ownerId));
    urlQuery.addQueryItem("v", "5.37");
    urlQuery.addQueryItem("access_token", InstanceFactory<LoginService>::getInstance()->getToken());
    url.setQuery(urlQuery);

    return toAudioCount(InstanceFactory<UrlQueryExecuteService>::getInstance()->executeUrl(url));
}

int AudioService::toAudioCount(const QByteArray &array)
{
    return QJsonDocument::fromJson(array).object()["response"].toInt();
}

QList<AudioItem> AudioService::toAudioItemList(const QByteArray &array)
{
    QList<AudioItem> list;

    QJsonObject json = QJsonDocument::fromJson(array).object();
    QJsonObject responseObj = json.value("response").toObject();
    QJsonArray itemArray = responseObj.value("items").toArray();

    for (int songIndex = 0; songIndex < itemArray.size(); ++songIndex)
    {
        QJsonObject songObject = itemArray[songIndex].toObject();
        AudioItem audioItem;
        audioItem.read(songObject);
        list.append(audioItem);
    }

    return list;
}

