#include "BGMPlayer.h"

CBGMPlayer::~CBGMPlayer()
{

}

void CBGMPlayer::Load(const char* inPath)
{
    m_pAudio = AddComponent<CAudio>();
    m_pAudio->Load(inPath);
}

void CBGMPlayer::Play()
{
    m_pAudio->Play(true);
}

void CBGMPlayer::Stop()
{
    m_pAudio->Stop();
}

void CBGMPlayer::SetVolume(float inVolume)
{
    m_pAudio->SetVolume(inVolume);
}
