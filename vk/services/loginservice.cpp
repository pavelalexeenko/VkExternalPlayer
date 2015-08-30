#include "loginservice.h"
#include "../vklogindialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QEventLoop>

LoginService::LoginService(QObject *parent) : QObject(parent)
{

}

QString LoginService::getToken()
{
    qDebug() << __FUNCTION__;

    if (_token.isEmpty())
    {
        VkLoginDialog *vld = new VkLoginDialog(0);
        connect(vld, SIGNAL(authSuccess(QString,int,int)), this, SLOT(authSuccess(QString,int,int)));
        connect(vld, SIGNAL(authFail(QString,QString)), this, SLOT(authFail(QString,QString)));
        vld->exec();

        QEventLoop eventLoop;
        QObject::connect(vld, SIGNAL(authSuccess(QString,int,int)),&eventLoop, SLOT(quit()));
        QObject::connect(vld, SIGNAL(authFail(QString,QString)),&eventLoop, SLOT(quit()));
        eventLoop.exec();
        qDebug() << "test";
    }

    return _token;
}

void LoginService::authSuccess(QString token, int expiresIn, int userId)
{
    qDebug() << __FUNCTION__;

    if (!token.isEmpty())
        _token = token;

    _expiresIn = expiresIn;
    _userId = userId;
}

void LoginService::authFail(QString error, QString errorDescription)
{
    qDebug() << __FUNCTION__;

    QMessageBox::critical(0, error, errorDescription);
}

