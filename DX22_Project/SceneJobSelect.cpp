#include "SceneJobSelect.h"
#include "SelectBackGround.h"
#include "Camera.h"
#include "BGMPlayer.h"
#include "SelectArrow.h"

void CSceneJobSelect::Init()
{
    CBillboardRenderer::Load(TEXTURE_PATH("Jobs.png"), "Player");
    CBillboardRenderer::Load(TEXTURE_PATH("SelectBackGround.jpeg"), "SelectBG");
    CBillboardRenderer::Load(TEXTURE_PATH("Stageselect_Left01.png"), "ArrowLeft");
    CBillboardRenderer::Load(TEXTURE_PATH("Stageselect_Right01.png"), "ArrowRight");

    CCamera::SetCameraKind(CAM_SELECT);

    AddGameObject<CSelectBackGround>("SelectBackGround");
    AddGameObject<CSelectJobs>("Jobs");
    AddGameObject<CSelectArrow>("Arrows");
    CBGMPlayer* pPlayer = AddGameObject<CBGMPlayer>("BGM",Tag::Sound);
    pPlayer->Load(AUDIO_PATH("BGM/SelectBGM.wav"));
    pPlayer->SetVolume(0.1f);
    pPlayer->Play();
}
