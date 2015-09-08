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

    MainWindow w;
    w.show();

    return a.exec();
}
