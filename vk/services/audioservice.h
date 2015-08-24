#ifndef AUDIOSERVICE_H
#define AUDIOSERVICE_H

#include "../objects/audioitem.h"
#include <QList>

class AudioService
{
public:
    AudioService();

    QList<AudioItem> getAllContactAudio(int ownerId);
    QList<AudioItem> getContactAudio(int ownerId, int count);
    int getAudioCount(int ownerId);
};

#endif // AUDIOSERVICE_H
