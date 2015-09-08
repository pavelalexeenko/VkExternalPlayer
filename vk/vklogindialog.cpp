#include "vklogindialog.h"
#include <QWebView>
#include <QUrl>
#include <QUrlQuery>
#include <QGridLayout>
#include <QDebug>

VkLoginDialog::VkLoginDialog(QWidget *parent) : QDialog(parent)
{
    qDebug() << __FUNCTION__;
    QUrl url;
    url.setScheme("https");
    url.setHost("oauth.vk.com");
    url.setPath("/authorize");

    QUrlQuery urlQuery;
    urlQuery.addQueryItem("client_id", "5042372");
    urlQuery.addQueryItem("display", "page");
    urlQuery.addQueryItem("redirect_uri", "https://oauth.vk.com/blank.html");
    urlQuery.addQueryItem("response_type", "token");
    urlQuery.addQueryItem("v", "5.37");
    urlQuery.addQueryItem("scope", "audio");
    url.setQuery(urlQuery);

    QWebView *webView = new QWebView(this);
    webView->load(url);

    connect(webView, SIGNAL(urlChanged(QUrl)), this, SLOT(getTokenFromUrl(QUrl)));

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(webView);
}

void VkLoginDialog::getTokenFromUrl(const QUrl &url)
{
    QUrlQuery query(QUrl(QString(url.toString()).replace("#", "?")));

    if (query.hasQueryItem("error"))
    {
        emit authFail(query.queryItemValue("error"), query.queryItemValue("error_description"));
        this->done(QDialog::Rejected);

        return;
    }

    if (query.hasQueryItem("access_token"))
    {
        //qDebug() << query.toString();
        emit authSuccess(query.queryItemValue("access_token"), query.queryItemValue("expires_in").toInt(),
                query.queryItemValue("user_id").toInt());
        this->done(QDialog::Accepted);
        return;
    }
}

