#include "Job.h"
#include "Main.h"
#include "Player.h"
#include "SceneTitle.h"
#include "PlayerAttack.h"

CJob::CJob()
    : m_tStatus{}, m_pTargetEnemy(nullptr), isEnd(false)
{
    CScene* pScene = GetScene();
    CPlayer* pPlayer = pScene->GetGameObject<CPlayer>();
}

CJob::~CJob()
{
}

void CJob::Update()
{
    for (int i = 0; i < (int)eSkill::Max; i++)
    {
        if (m_tStatus.m_fSkillTime[i] != m_tStatus.m_fSkillCooltime[i])
        {
            m_tStatus.m_fSkillTime[i] += fDeltaTime;
            m_tStatus.m_fSkillTime[i] = std::min(m_tStatus.m_fSkillTime[i], m_tStatus.m_fSkillCooltime[i]);
        }

        m_tStatus.m_fDurationTime[i] += fDeltaTime;
        if (m_tStatus.m_fDurationTime[i] >= m_tStatus.m_fAttackDuration[i])
        {
            m_tStatus.m_fDurationTime[i] = 0.0f;
        }

    }
}

bool CJob::Skill(eSkill inKind)
{
    if (inKind >= eSkill::Max || inKind < eSkill::NormalAttack) return false;
    if (m_tStatus.m_fSkillTime[(int)inKind] < m_tStatus.m_fSkillCooltime[(int)inKind]) return false;

    switch (inKind)
    {
    case eSkill::NormalAttack: NormalAttack(); break;
    case eSkill::QSkill: QSkill(); break;
    case eSkill::ESkill: ESkill(); break;
    case eSkill::RSkill: RSkill();  break;
    default: break;
    }

    m_tStatus.m_fSkillTime[(int)inKind] = 0.0f;
    return true;
}

void CJob::Damage(int inDamage)
{
    if (isEnd) return;
    m_tStatus.m_nHP -= inDamage;
    if (m_tStatus.m_nHP <= 0 && !isEnd)
    {
        isEnd = true;
        FadeOut([]()
            {
                ChangeScene(new CSceneTitle());
                FadeIn(nullptr);
            });
    }
}

void CJob::Attack(AttackState inState)
{
    CPlayerAttack* pAttack = GetScene()->AddGameObject<CPlayerAttack>("PlayerAttack");
    pAttack->Init();
    pAttack->SetAttackState(inState);
    pAttack->AccessorRotate(GetScene()->GetGameObject<CPlayer>()->AccessorRotate());
}
