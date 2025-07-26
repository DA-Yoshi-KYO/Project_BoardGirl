#include "Job.h"
#include "Main.h"
#include "Player.h"

CJob::CJob()
    : m_tStatus{}, m_pCollisionObb{}
{
    CScene* pScene = GetScene();
    CPlayer* pPlayer = pScene->GetGameObject<CPlayer>();
    m_pCollisionObb[(int)eSkill::NormalAttack] = std::make_unique<CCollisionObb>(pPlayer);
    m_pCollisionObb[(int)eSkill::QSkill] = std::make_unique<CCollisionObb>(pPlayer);
    m_pCollisionObb[(int)eSkill::ESkill] = std::make_unique<CCollisionObb>(pPlayer);
    m_pCollisionObb[(int)eSkill::RSkill] = std::make_unique<CCollisionObb>(pPlayer);

    for (int i = 0; i < (int)eSkill::Max; i++)
    {
        m_pCollisionObb[i]->AccessorActive(false);
        pScene->AddCollision(m_pCollisionObb[i].get());
    }
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

        if (m_pCollisionObb[i]->AccessorActive())
        {
            m_tStatus.m_fDurationTime[i] += fDeltaTime;
            if (m_tStatus.m_fDurationTime[i] >= m_tStatus.m_fAttackDuration[i])
            {
                m_pCollisionObb[i]->AccessorActive(false);
                m_tStatus.m_fDurationTime[i] = 0.0f;
            }
        }
    }
}

void CJob::Skill(eSkill inKind)
{
    if (inKind >= eSkill::Max || inKind < eSkill::NormalAttack) return;
    if (m_tStatus.m_fSkillTime[(int)inKind] < m_tStatus.m_fSkillCooltime[(int)inKind]) return;

    m_pCollisionObb[(int)inKind]->AccessorActive(true);
    switch (inKind)
    {
    case eSkill::NormalAttack: NormalAttack(); break;
    case eSkill::QSkill: QSkill(); break;
    case eSkill::ESkill: ESkill(); break;
    case eSkill::RSkill: RSkill();  break;
    default: break;
    }

    m_tStatus.m_fSkillTime[(int)inKind] = 0.0f;
}
