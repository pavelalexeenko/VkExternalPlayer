#include "urlqueryexecuteservice.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QEventLoop>

UrlQueryExecuteService::UrlQueryExecuteService(QObject *parent)
    : QObject(parent)
    , manager(new QNetworkAccessManager())
    , eventLoop(new QEventLoop())
{
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), eventLoop, SLOT(quit()));
}

UrlQueryExecuteService::~UrlQueryExecuteService()
{
    delete manager;
    delete eventLoop;
}

QByteArray UrlQueryExecuteService::executeUrl(const QUrl &url)
{
    QNetworkReply* reply = manager->get(QNetworkRequest(QUrl(url)));
    eventLoop->exec();
    return reply->readAll();
}

