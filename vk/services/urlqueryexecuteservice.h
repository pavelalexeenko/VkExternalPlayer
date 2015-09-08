#ifndef URLQUERYEXECUTESERVICE_H
#define URLQUERYEXECUTESERVICE_H

#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;
class QEventLoop;
class UrlQueryExecuteService : public QObject
{
    Q_OBJECT
public:
    explicit UrlQueryExecuteService(QObject *parent = 0);
    ~UrlQueryExecuteService();

    QByteArray executeUrl(const QUrl& url);

private:
    QNetworkAccessManager* manager;
    QNetworkReply* reply;
    QEventLoop *eventLoop;
};

#endif // URLQUERYEXECUTESERVICE_H
