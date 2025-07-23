#include "SceneJobSelect.h"
#include "Input.h"
#include "Main.h"
#include "SceneGame.h"
#include "SelectBackGround.h"
#include "SelectJobs.h"

JobKind CSceneJobSelect::m_eSelectedJob = JobKind::Soldier;

void CSceneJobSelect::Init()
{
    m_eSelectedJob = JobKind::Soldier;
    AddGameObject<CSelectJobs>();
}

void CSceneJobSelect::Update()
{
    if (IsKeyTrigger(VK_RIGHT))
    {
        m_eSelectedJob = JobKind((int)m_eSelectedJob + 1);
    }
    else if (IsKeyTrigger(VK_LEFT))
    {
        // ジョブの選択を左に移動
        m_eSelectedJob = JobKind((int)m_eSelectedJob - 1);
    }
    else if (IsKeyTrigger(VK_RETURN))
    {
        ChangeScene(new CSceneGame());
    }

    m_eSelectedJob = (JobKind)std::clamp((int)m_eSelectedJob, (int)JobKind::Soldier, (int)JobKind::Max - 1);

    CScene::Update();
}
