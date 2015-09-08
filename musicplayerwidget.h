#ifndef MUSICPLAYERWIDGET_H
#define MUSICPLAYERWIDGET_H

#include <QtWidgets>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class AudioItem;
class MusicPlayerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MusicPlayerWidget(QWidget *parent = 0);
    ~MusicPlayerWidget();

    void setUpPlaylist(const QList<AudioItem>& songList);
    void playSongAtIndex(int index);

signals:

public slots:
    void togglePlayback();
    void forward();
    void backward();
    void openFile();
    void playFile(const QString& filePath);
    void playUrl(const QString& url);

private slots:
    void setPosition(int position);
    void updateState(QMediaPlayer::State state);
    void updatePosition(qint64 position);
    void updateDuration(qint64 duration);
    void updateInfo();

private:
    void createWidgets();

    QMediaPlayer mediaPlayer;
    QMediaPlaylist *playlist;
    QPushButton *playButton;
    QPushButton *skipForwardButton;
    QPushButton *skipBackwardButton;
    QSlider *volumeSlider;
    QSlider *positionSlider;
    QLabel *positionLabel;
    QLabel *infoLabel;

protected:
    QSize sizeHint() const
    {
        QSize size = QWidget::sizeHint();

        return QSize(500, 80);
    }

};

#endif // MUSICPLAYERWIDGET_H
