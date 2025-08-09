#pragma once

#include "GameObject.h"
#include "Audio.h"

class CBGMPlayer : public CGameObject
{
public:
    virtual ~CBGMPlayer();
    void Load(const char* inPath);
    void Play();
    void Stop();
    void SetVolume(float inVolume);

private:
    CAudio* m_pAudio;

};
