#include "mainwindow.h"
#include "musicplayerwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    MusicPlayerWidget *musicPlayerWidget = new MusicPlayerWidget(this);
    QWebView *webView = new QWebView(this);

    webView->load(QUrl("https://oauth.vk.com/authorize?"
                       "client_id=5042372&"
                       "display=page&"
                       "redirect_uri=https://oauth.vk.com/blank.html&"
                       "scope=audio&"
                       "response_type=token&"
                       "v=5.37"));



    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(musicPlayerWidget, 0, 0, Qt::AlignTop);
    layout->addWidget(webView);
}

MainWindow::~MainWindow()
{

}
