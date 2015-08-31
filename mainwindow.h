#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include "musicplayerwidget.h"
#include <vk/objects/audioitem.h>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void getSongs();
    void playSong(int row, int column);

private:
    QTableWidget *table;
    MusicPlayerWidget *musicPlayerWidget;
    QList<AudioItem> list;
};

#endif // MAINWINDOW_H
