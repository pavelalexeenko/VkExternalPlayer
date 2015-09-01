#include "mainwindow.h"
#include <vk/vklogindialog.h>
#include <vk/instancefactory.h>
#include <vk/services/audioservice.h>


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    musicPlayerWidget = new MusicPlayerWidget(this);

    QStringList headers;
    headers << tr("Title") << tr("Artist") << tr("Album") << tr("Year");

    table = new QTableWidget(0, 4);
    table->setColumnHidden(3, true);
    table->setHorizontalHeaderLabels(headers);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setFrameStyle(QFrame::NoFrame);
    table->setShowGrid(false);

    connect(table, SIGNAL(cellPressed(int,int)), this, SLOT(playSong(int,int)));

    QPushButton *b = new QPushButton("GetSongs");
    connect(b, SIGNAL(clicked(bool)), this, SLOT(getSongs()));

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(musicPlayerWidget, 0, 0, Qt::AlignTop);
    layout->addWidget(table, 1, 0);
    layout->addWidget(b, 2, 0);
}

MainWindow::~MainWindow()
{

}

void MainWindow::getSongs()
{
    qDebug() << __FUNCTION__;

    list = InstanceFactory<AudioService>::getInstance()->getCurrentUsersAllContactAudio();
    musicPlayerWidget->setUpPlaylist(list);

    for (auto item : list)
    {
        QTableWidgetItem *artistItem = new QTableWidgetItem(item.getArtist());
        artistItem->setFlags(artistItem->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem *titleItem = new QTableWidgetItem(item.getTitle());
        titleItem->setFlags(titleItem->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem *durationItem = new QTableWidgetItem(item.getDuration());
        durationItem->setFlags(durationItem->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem *urlItem = new QTableWidgetItem(item.getUrl().toString());
        urlItem->setFlags(urlItem->flags() ^ Qt::ItemIsEditable);

        int currentRow = table->rowCount();
        table->insertRow(currentRow);
        table->setItem(currentRow, 0, artistItem);
        table->setItem(currentRow, 1, titleItem);
        table->setItem(currentRow, 2, durationItem);
        table->setItem(currentRow, 3, urlItem);
    }
}

void MainWindow::playSong(int row, int column)
{
    //QTableWidgetItem *item = table->item(row, 3);
    //musicPlayerWidget->playUrl(item->text());
    musicPlayerWidget->playSongAtIndex(row);
}
