#ifndef AUDIOSERVICE_H
#define AUDIOSERVICE_H

#include <QList>
#include <QObject>

class AudioItem;

class AudioService : public QObject
{
    Q_OBJECT
public:
    explicit AudioService(QObject *parent = 0);

    QList<AudioItem> getCurrentUsersAllContactAudio();
    QList<AudioItem> getCurrentUsersContactAudio(int count);
    int getCurrentUsersAudioCount();

    QList<AudioItem> getAllContactAudio(int ownerId);
    QList<AudioItem> getContactAudio(int ownerId, int count);
    int getAudioCount(int ownerId);

private:
    int toAudioCount(const QByteArray& array);
    QList<AudioItem> toAudioItemList(const QByteArray& array);
};

#endif // AUDIOSERVICE_H
