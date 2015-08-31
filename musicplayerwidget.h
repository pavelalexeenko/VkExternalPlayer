#ifndef MUSICPLAYERWIDGET_H
#define MUSICPLAYERWIDGET_H

#include <QtWidgets>
#include <QMediaPlayer>

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
