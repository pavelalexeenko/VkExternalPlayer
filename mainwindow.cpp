#include "mainwindow.h"
#include "musicplayerwidget.h"
#include <vk/vklogindialog.h>
#include <vk/instancefactory.h>
#include <vk/services/audioservice.h>
#include <vk/objects/audioitem.h>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    MusicPlayerWidget *musicPlayerWidget = new MusicPlayerWidget(this);

    QPushButton *btn = new QPushButton(this);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(getSongs()));

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(musicPlayerWidget, 0, 0, Qt::AlignTop);
    layout->addWidget(btn, 0, 1);
}

MainWindow::~MainWindow()
{

}

void MainWindow::getSongs()
{
    InstanceFactory<AudioService>::getInstance()->getAllContactAudio(17849865);
}
