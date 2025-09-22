#include "SceneJobSelect.h"
#include "SelectBackGround.h"
#include "Camera.h"
#include "BGMPlayer.h"
#include "SelectArrow.h"

void CSceneJobSelect::Init()
{


    CCamera::SetCameraKind(CAM_SELECT);

    AddGameObject<CSelectBackGround>("SelectBackGround", Tag::GameObject);
    AddGameObject<CSelectJobs>("Jobs", Tag::GameObject);
    AddGameObject<CSelectArrow>("Arrows", Tag::GameObject);
    CBGMPlayer* pPlayer = AddGameObject<CBGMPlayer>("BGM",Tag::Sound);
    pPlayer->Load(AUDIO_PATH("BGM/SelectBGM.wav"));
    pPlayer->SetVolume(0.1f);
    pPlayer->Play();
}
