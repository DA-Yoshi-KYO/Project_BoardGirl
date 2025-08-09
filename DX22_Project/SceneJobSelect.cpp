#include "SceneJobSelect.h"
#include "Input.h"
#include "Main.h"
#include "SceneGame.h"
#include "SelectBackGround.h"
#include "Camera.h"
#include "BGMPlayer.h"

JobKind CSceneJobSelect::m_eSelectedJob = JobKind::Soldier;

void CSceneJobSelect::Init()
{
    CBillboardRenderer::Load(TEXTURE_PATH("Jobs.png"), "Player");

    CCamera::SetCameraKind(CAM_SELECT);

    m_eSelectedJob = JobKind::Soldier;
    m_pSelectJobs = AddGameObject<CSelectJobs>();
    CBGMPlayer* pPlayer = AddGameObject<CBGMPlayer>(Tag::Sound);
    pPlayer->Load(AUDIO_PATH("SelectBGM.wav"));
    pPlayer->SetVolume(0.1f);
    pPlayer->Play();
}

void CSceneJobSelect::Update()
{
    int nSelect = (int)m_eSelectedJob;
    if (!m_pSelectJobs->IsMove())
    {
        if (IsKeyTrigger(VK_RIGHT))
        {
            nSelect++;
            if (nSelect == (int)JobKind::Max)
            {
                nSelect = 0;
            }
            m_pSelectJobs->SetMove(true);
        }
        else if (IsKeyTrigger(VK_LEFT))
        {
            nSelect--;
            if (nSelect < 0)
            {
                nSelect = (int)JobKind::Max - 1;
            }
            m_pSelectJobs->SetMove(false);
        }
        else if (IsKeyTrigger(VK_SPACE))
        {
            ChangeScene(new CSceneGame());
        }
    }

    m_eSelectedJob = (JobKind)nSelect;
    CScene::Update();
}
