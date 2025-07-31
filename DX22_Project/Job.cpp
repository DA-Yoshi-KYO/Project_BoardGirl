#include "Job.h"
#include "Main.h"
#include "Player.h"

CJob::CJob()
    : m_tStatus{}, m_pCollisionObb{}
{
    CScene* pScene = GetScene();
    CPlayer* pPlayer = pScene->GetGameObject<CPlayer>();

    for (int i = 0; i < (int)eSkill::Max; i++)
    {
        m_pCollisionObb[i] = std::make_unique<CCollisionObb>(pPlayer);
        m_pCollisionObb[i]->AccessorActive(false);
        pScene->AddCollision(m_pCollisionObb[i].get());
    }

    m_pCollisionObb[(int)eSkill::NormalAttack]->AccessorTag("NormalAttack");
    m_pCollisionObb[(int)eSkill::QSkill]->AccessorTag("QSkill");
    m_pCollisionObb[(int)eSkill::ESkill]->AccessorTag("ESkill");
    m_pCollisionObb[(int)eSkill::RSkill]->AccessorTag("RSkill");
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

void CJob::SkillHit(eSkill inKind, CEnemyBase* inTarget)
{
    if (inKind >= eSkill::Max || inKind < eSkill::NormalAttack) return;
    m_pTargetEnemy = inTarget;

    switch (inKind)
    {
    case eSkill::NormalAttack: NormalAttackHit(); break;
    case eSkill::QSkill: QSkillHit(); break;
    case eSkill::ESkill: ESkillHit(); break;
    case eSkill::RSkill: RSkillHit(); break;
    default: break;
    }
}
