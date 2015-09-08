#include "loginservice.h"
#include "../vklogindialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>

LoginService::LoginService(QObject *parent)
    : QObject(parent)
    , _userId(0)
{

}

QString LoginService::getToken()
{
    if (_token.isEmpty())
        login();

    return _token;
}

int LoginService::getUserId()
{
    if (!_userId)
        login();

    return _userId;
}

void LoginService::authSuccess(QString token, int expiresIn, int userId)
{
    _token = token;
    _userId = userId;

    QTimer::singleShot(expiresIn * 1000, this, SLOT(dropCredentialsDueTheTimeOut()));
}

void LoginService::authFail(QString error, QString errorDescription)
{
    QMessageBox::critical(0, error, errorDescription);
}

void LoginService::dropCredentialsDueTheTimeOut()
{
    _token.clear();
    _userId = 0;

    qDebug() << "Cleared!";
}

void LoginService::login()
{
    VkLoginDialog *vld = new VkLoginDialog(0);
    connect(vld, SIGNAL(authSuccess(QString,int,int)), this, SLOT(authSuccess(QString,int,int)));
    connect(vld, SIGNAL(authFail(QString,QString)), this, SLOT(authFail(QString,QString)));
    vld->exec();
}

