#ifndef LOGINSERVICE_H
#define LOGINSERVICE_H

#include <QObject>

class LoginService : public QObject
{
    Q_OBJECT
public:
    explicit LoginService(QObject *parent = 0);

    QString getToken();
    int getUserId();

private slots:
    void authSuccess(QString token, int expiresIn, int userId);
    void authFail(QString error, QString errorDescription);
    void dropCredentialsDueTheTimeOut();

private:
    void login();

private:
    QString _token;
    int _userId;
};

#endif // LOGINSERVICE_H
