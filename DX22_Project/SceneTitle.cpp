#include "SceneTitle.h"
#include "TitleBackGround.h"
#include "BGMPlayer.h"

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Init()
{
    CSpriteRenderer::Load(TEXTURE_PATH("Title.jpg"), "TitleBG");

    AddGameObject<CTitleBackGround>(Tag::UI);
    CBGMPlayer* pPlayer = AddGameObject<CBGMPlayer>(Tag::Sound);
    pPlayer->Load(AUDIO_PATH("TitleBGM.wav"));
    pPlayer->SetVolume(0.1f);
    pPlayer->Play();
}
