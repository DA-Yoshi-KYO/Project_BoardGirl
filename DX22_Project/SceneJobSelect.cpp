#include "SceneJobSelect.h"
#include "Input.h"
#include "Main.h"
#include "SceneGame.h"
#include "SelectBackGround.h"
#include "Camera.h"

JobKind CSceneJobSelect::m_eSelectedJob = JobKind::Soldier;

void CSceneJobSelect::Init()
{
    CBillboardRenderer::Load(TEXTURE_PATH("Jobs.png"), "Player");

    CCamera::SetCameraKind(CAM_SELECT);

    m_eSelectedJob = JobKind::Soldier;
    m_pSelectJobs = AddGameObject<CSelectJobs>();
}

void CSceneJobSelect::Update()
{
    if (!m_pSelectJobs->IsMove())
    {
        if (IsKeyTrigger(VK_RIGHT))
        {
            m_eSelectedJob = JobKind((int)m_eSelectedJob + 1);
            if (m_eSelectedJob == JobKind::Max)
            {
                m_eSelectedJob = JobKind::Soldier;
            }
            m_pSelectJobs->SetMove(true);
        }
        else if (IsKeyTrigger(VK_LEFT))
        {
            m_eSelectedJob = JobKind((int)m_eSelectedJob - 1);
            if (m_eSelectedJob < JobKind::Soldier)
            {
                m_eSelectedJob = JobKind((int)JobKind::Max - 1);
            }
            m_pSelectJobs->SetMove(false);
        }
        else if (IsKeyTrigger(VK_SPACE))
        {
            ChangeScene(new CSceneGame());
        }
    }

    CScene::Update();
}
