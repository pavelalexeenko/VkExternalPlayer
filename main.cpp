#include "mainwindow.h"
#include <QApplication>
#include <vk/instancefactory.h>
#include <vk/services/audioservice.h>
#include <vk/objects/audioitem.h>

#include <QDebug>
#include <QUrlQuery>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
/*
    QString string = QString("https://oauth.vk.com/blank.html#access_token=b2a4565e2ebc51af66f5154ec3cc80cd129381ab2fa7de29caad147802343fb7baf77ee5adb53b509856d&expires_in=86400&user_id=17849865").replace("#","?");
    QUrl url(string);

    qDebug() << url.toString();
    QUrlQuery query = QUrlQuery(url);

    //QUrlQuery query(url);

    QString str("access_token");
    qDebug() << query.toString();

    qDebug() << str;

    qDebug() << "tkoen: " << query.queryItemValue(str);

    if (query.hasQueryItem("error"))
    {
        qDebug() << "fail: " << query.queryItemValue("error") << " - " << query.queryItemValue("error_description");
    }

    if (query.hasQueryItem("access_token"))
    {
        qDebug() << "success: " << query.queryItemValue("access_token") << " - " << query.queryItemValue("expires_in")
                 << " - " << query.queryItemValue("user_id");
    }
*/
    MainWindow w;
    w.show();

    return a.exec();
}
