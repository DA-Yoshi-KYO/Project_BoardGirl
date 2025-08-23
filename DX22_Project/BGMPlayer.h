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

    virtual int Inspecter(bool isEnd = true) override;

private:
    CAudio* m_pAudio;
    struct AudioState
    {
        std::string m_sBGMName;
        float m_fVolume;
    }m_tState;
    
};
