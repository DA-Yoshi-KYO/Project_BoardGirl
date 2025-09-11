#include "SceneJobSelect.h"
#include "SelectBackGround.h"
#include "Camera.h"
#include "BGMPlayer.h"

void CSceneJobSelect::Init()
{
    CBillboardRenderer::Load(TEXTURE_PATH("Jobs.png"), "Player");
    CBillboardRenderer::Load(TEXTURE_PATH("SelectBackGround.jpeg"), "SelectBG");
    CBillboardRenderer::Load(TEXTURE_PATH("Alphabet.png"), "Alphabet");

    CCamera::SetCameraKind(CAM_SELECT);

    AddGameObject<CSelectBackGround>("SelectBackGround");
    AddGameObject<CSelectJobs>("Jobs");
    CBGMPlayer* pPlayer = AddGameObject<CBGMPlayer>("BGM",Tag::Sound);
    pPlayer->Load(AUDIO_PATH("BGM/SelectBGM.wav"));
    pPlayer->SetVolume(0.1f);
    pPlayer->Play();
}
