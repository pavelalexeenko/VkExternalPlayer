#include "musicplayerwidget.h"

MusicPlayerWidget::MusicPlayerWidget(QWidget *parent)
    : QWidget(parent)
{
    createWidgets();

    connect(&mediaPlayer, &QMediaObject::metaDataAvailableChanged, this, &MusicPlayerWidget::updateInfo);
    connect(&mediaPlayer, &QMediaPlayer::positionChanged, this, &MusicPlayerWidget::updatePosition);
    connect(&mediaPlayer, &QMediaPlayer::durationChanged, this, &MusicPlayerWidget::updateDuration);
    connect(&mediaPlayer, &QMediaPlayer::stateChanged, this, &MusicPlayerWidget::updateState);
}

void MusicPlayerWidget::togglePlayback()
{
    if (mediaPlayer.mediaStatus() == QMediaPlayer::NoMedia)
        openFile();
    else if (mediaPlayer.state() == QMediaPlayer::PlayingState)
        mediaPlayer.pause();
    else
        mediaPlayer.play();
}

void MusicPlayerWidget::openFile()
{
    const QStringList musicPaths = QStandardPaths::standardLocations(QStandardPaths::MusicLocation);
    const QString filePath =
        QFileDialog::getOpenFileName(this, tr("Open File"),
                                     musicPaths.isEmpty() ? QDir::homePath() : musicPaths.first(),
                                     tr("MP3 files (*.mp3);;All files (*.*)"));
    if (!filePath.isEmpty())
        playFile(filePath);
}

void MusicPlayerWidget::playFile(const QString &filePath)
{
    playButton->setEnabled(true);
    infoLabel->setText(QFileInfo(filePath).fileName());

    mediaPlayer.setMedia(QUrl::fromLocalFile(filePath));
    mediaPlayer.play();
}

void MusicPlayerWidget::setPosition(int position)
{
    // avoid seeking when the slider value change is triggered from updatePosition()
    if (qAbs(mediaPlayer.position() - position) > 99)
        mediaPlayer.setPosition(position);
}

void MusicPlayerWidget::updateState(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::PlayingState) {
        playButton->setToolTip(tr("Pause"));
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    } else {
        playButton->setToolTip(tr("Play"));
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
}

void MusicPlayerWidget::updatePosition(qint64 position)
{
    positionSlider->setValue(position);

    QTime duration(0, position / 60000, qRound((position % 60000) / 1000.0));
    positionLabel->setText(duration.toString(tr("mm:ss")));
}

void MusicPlayerWidget::updateDuration(qint64 duration)
{
    positionSlider->setRange(0, duration);
    positionSlider->setEnabled(duration > 0);
    positionSlider->setPageStep(duration / 10);
}

void MusicPlayerWidget::updateInfo()
{
    QStringList info;
    QString author = mediaPlayer.metaData("Author").toString();
    if (!author.isEmpty())
        info += author;
    QString title = mediaPlayer.metaData("Title").toString();
    if (!title.isEmpty())
        info += title;
    if (!info.isEmpty())
        infoLabel->setText(info.join(tr(" - ")));
}

void MusicPlayerWidget::createWidgets()
{
    playButton = new QPushButton(this);
    playButton->setEnabled(false);
    playButton->setToolTip(tr("Play"));
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(playButton, &QAbstractButton::clicked, this, &MusicPlayerWidget::togglePlayback);

    skipBackwardButton = new QPushButton(this);
    skipBackwardButton->setEnabled(false);
    skipBackwardButton->setToolTip(tr("Skip Backward"));
    skipBackwardButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
   // connect(skipBackwardButton, &QAbstractButton::clicked, this, &MusicPlayerWidget::togglePlayback);

    skipForwardButton = new QPushButton(this);
    skipForwardButton->setEnabled(false);
    skipForwardButton->setToolTip(tr("Skip Forward"));
    skipForwardButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
   // connect(skipForwardButton, &QAbstractButton::clicked, this, &MusicPlayerWidget::togglePlayback);

    QAbstractButton *openButton = new QToolButton(this);
    openButton->setText(tr("..."));
    openButton->setToolTip(tr("Open a file..."));
    openButton->setFixedSize(playButton->sizeHint());
    connect(openButton, &QAbstractButton::clicked, this, &MusicPlayerWidget::openFile);

    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setToolTip(tr("Adjust volume"));
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(mediaPlayer.volume());
    volumeSlider->setMaximumWidth(100);
    connect(volumeSlider, &QSlider::valueChanged, &mediaPlayer, &QMediaPlayer::setVolume);

    positionSlider = new QSlider(Qt::Horizontal, this);
    positionSlider->setEnabled(false);
    positionSlider->setToolTip(tr("Seek"));
    connect(positionSlider, &QSlider::valueChanged, this, &MusicPlayerWidget::setPosition);

    infoLabel = new QLabel(this);
    positionLabel = new QLabel(tr("00:00"), this);
    positionLabel->setMinimumWidth(positionLabel->sizeHint().width());

    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setMargin(0);
    controlLayout->addWidget(openButton);
    controlLayout->addWidget(skipBackwardButton);
    controlLayout->addWidget(playButton);
    controlLayout->addWidget(skipForwardButton);
    controlLayout->addWidget(positionSlider);
    controlLayout->addWidget(positionLabel);
    controlLayout->addWidget(volumeSlider);

    QBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(infoLabel);
    mainLayout->addLayout(controlLayout);
}

