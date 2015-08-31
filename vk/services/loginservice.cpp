#include "loginservice.h"
#include "../vklogindialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QEventLoop>

LoginService::LoginService(QObject *parent)
    : QObject(parent)
    , _expiresIn(0)
    , _userId(0)
{

}

QString LoginService::getToken()
{
    qDebug() << __FUNCTION__;

    if (_token.isEmpty())
        login();

    return _token;
}

int LoginService::getExpiresIn()
{
    if (!_expiresIn)
        login();

    return _expiresIn;
}

int LoginService::getUserId()
{
    if (!_userId)
        login();

    return _userId;
}

void LoginService::authSuccess(QString token, int expiresIn, int userId)
{
    qDebug() << __FUNCTION__;

    _token = token;
    _expiresIn = expiresIn;
    _userId = userId;
}

void LoginService::authFail(QString error, QString errorDescription)
{
    qDebug() << __FUNCTION__;

    QMessageBox::critical(0, error, errorDescription);
}

void LoginService::login()
{
    VkLoginDialog *vld = new VkLoginDialog(0);
    connect(vld, SIGNAL(authSuccess(QString,int,int)), this, SLOT(authSuccess(QString,int,int)));
    connect(vld, SIGNAL(authFail(QString,QString)), this, SLOT(authFail(QString,QString)));
    vld->exec();
}

