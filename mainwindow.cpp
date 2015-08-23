#include "mainwindow.h"
#include "musicplayerwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    MusicPlayerWidget *musicPlayerWidget = new MusicPlayerWidget(this);
    setCentralWidget(musicPlayerWidget);
}

MainWindow::~MainWindow()
{

}
