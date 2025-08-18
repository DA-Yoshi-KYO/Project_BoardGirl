#include "SceneJobSelect.h"
#include "SelectBackGround.h"
#include "Camera.h"
#include "BGMPlayer.h"

void CSceneJobSelect::Init()
{
    CBillboardRenderer::Load(TEXTURE_PATH("Jobs.png"), "Player");

    CCamera::SetCameraKind(CAM_SELECT);

    AddGameObject<CSelectJobs>("Jobs");
    CBGMPlayer* pPlayer = AddGameObject<CBGMPlayer>("BGM",Tag::Sound);
    pPlayer->Load(AUDIO_PATH("BGM/SelectBGM.wav"));
    pPlayer->SetVolume(0.1f);
    pPlayer->Play();
}
