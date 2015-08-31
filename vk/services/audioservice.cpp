#include "audioservice.h"
#include <QUrl>
#include <QUrlQuery>
#include <QString>
#include <QDebug>
#include "../objects/audioitem.h"
#include "../instancefactory.h"
#include "loginservice.h"

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

    qDebug() << url.toDisplayString();

    // NotYetImplementedVkUrlExecuteQueryService(url);

    QNetworkAccessManager* manager = new QNetworkAccessManager();//создаем объект класса для работы с http
    QNetworkReply* reply = manager->get(QNetworkRequest(QUrl(url)));//выполняем гет запрос и записываем ответ

    QEventLoop eventLoop;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),&eventLoop, SLOT(quit()));
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
    eventLoop.exec();

    QByteArray answer = reply->readAll();

    reply->deleteLater();

    delete manager;

    qDebug() << QString::fromStdString(answer.toStdString());

    QList<AudioItem> list;

    QJsonDocument loadDoc(QJsonDocument::fromJson(answer));
    QJsonObject json = loadDoc.object();
    qDebug() << "\n\n"<<json;

    QJsonValue response = json.value("response");
    QJsonObject responseObj = response.toObject();
    qDebug() << "\n"<<responseObj;

    QStringList keys1 = responseObj.keys();
    foreach(QString key, keys1)
        qDebug() << key;

    qDebug() << responseObj.value("count");
    QJsonObject itemArrayObj = responseObj.value("items").toObject();

    QStringList keys = itemArrayObj.keys();
    foreach(QString key, keys)
        qDebug() << key;

    QJsonArray songArray = json["response"].toArray();

    for (int songIndex = 0; songIndex < songArray.size(); ++songIndex)
    {
        QJsonObject songObject = songArray[songIndex].toObject();
        AudioItem audioItem;
        audioItem.read(songObject);
        list.append(audioItem);
    }

    for (auto song : list)
    {
        qDebug() << song.toString();
    }

    return list;
}

int AudioService::getAudioCount(int ownerId)
{
    return 2;
}

