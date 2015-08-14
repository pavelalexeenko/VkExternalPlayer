#ifndef MUSICPLAYERWIDGET_H
#define MUSICPLAYERWIDGET_H

#include <QtWidgets>
#include <QMediaPlayer>
#include <QtWinExtras>


class MusicPlayerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MusicPlayerWidget(QWidget *parent = 0);

signals:

public slots:
    void togglePlayback();
    void openFile();
    void playFile(const QString& filePath);

private slots:
    void setPosition(int position);
    void updateState(QMediaPlayer::State state);
    void updatePosition(qint64 position);
    void updateDuration(qint64 duration);
    void updateInfo();

private:
    void createWidgets();

    QMediaPlayer mediaPlayer;
    QPushButton *playButton;
    QPushButton *skipForwardButton;
    QPushButton *skipBackwardButton;
    QSlider *volumeSlider;
    QSlider *positionSlider;
    QLabel *positionLabel;
    QLabel *infoLabel;
};

#endif // MUSICPLAYERWIDGET_H
