#ifndef VKLOGINDIALOG_H
#define VKLOGINDIALOG_H

#include <QWidget>
#include <QDialog>

class VkLoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit VkLoginDialog(QWidget *parent = 0);

signals:
    void authSuccess(QString token, int expiresIn, int userId);
    void authFail(QString error, QString errorDescription);

private slots:
    void getTokenFromUrl(const QUrl &url);
};

#endif // VKLOGINDIALOG_H
