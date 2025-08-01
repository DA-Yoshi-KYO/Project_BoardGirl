#include "Wizard.h"
#include "Main.h"
#include "Player.h"

CWizard::CWizard()
{
    m_tStatus.m_nHP = 80;
    m_tStatus.m_fCriticalPercentage = 12.5f;
    m_tStatus.m_nAttack = 1;
    m_tStatus.m_nDefense = 1;

    m_tStatus.m_fSkillCooltime[(int)eSkill::NormalAttack] = 0.5f;
    m_tStatus.m_fSkillCooltime[(int)eSkill::QSkill] = 8.0f;
    m_tStatus.m_fSkillCooltime[(int)eSkill::ESkill] = 8.0f;
    m_tStatus.m_fSkillCooltime[(int)eSkill::RSkill] = 20.0f;

    m_tStatus.m_fAttackDuration[(int)eSkill::NormalAttack] = 0.5f;
    m_tStatus.m_fAttackDuration[(int)eSkill::QSkill] = 1.0f;
    m_tStatus.m_fAttackDuration[(int)eSkill::ESkill] = 1.0f;
    m_tStatus.m_fAttackDuration[(int)eSkill::RSkill] = 3.0f;

    ObbInfo info[(int)eSkill::Max];
    info[(int)eSkill::NormalAttack] = { {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f,1.0f} };
    info[(int)eSkill::QSkill] = { {0.0f, 0.0f, 0.0f}, {3.0f, 1.0f,1.0f} };
    info[(int)eSkill::ESkill] = { {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f,3.0f} };
    info[(int)eSkill::RSkill] = { {0.0f, 0.0f, 0.0f}, {3.0f, 3.0f,3.0f} };
    for (int i = 0; i < (int)eSkill::Max; i++)
    {
        m_pCollisionObb[i]->AccessorCollisionInfo(info[i]);

        m_tStatus.m_fDurationTime[i] = 0.0f;
        m_tStatus.m_fSkillTime[i] = 0.0f;
    }
}

CWizard::~CWizard()
{
}

void CWizard::Update()
{
    for (int i = 0; i < (int)eSkill::Max; i++)
    {
        if (m_pCollisionObb[i]->AccessorActive())
        {
            switch (i)
            {
            case (int)eSkill::NormalAttack:
                DirectX::XMFLOAT3 f3NowPos = m_pCollisionObb[(int)eSkill::NormalAttack]->AccessorCenter();
                f3NowPos += m_f3Forward;
                m_pCollisionObb[(int)eSkill::NormalAttack]->AccessorCenter(f3NowPos);
                break;
            default:
                break;
            }
        }
    }

    CJob::Update();
}

void CWizard::NormalAttack()
{
    CPlayer* pPlayer = GetScene()->GetGameObject<CPlayer>();
    m_f3Forward = pPlayer->GetForward();
    m_pCollisionObb[(int)eSkill::NormalAttack]->AccessorCenter(pPlayer->AccessorPos());
}

void CWizard::QSkill()
{
}

void CWizard::ESkill()
{
}

void CWizard::RSkill()
{
}

void CWizard::NormalAttackHit()
{
    m_pTargetEnemy->Damage(m_tStatus.m_nAttack);
}

void CWizard::QSkillHit()
{
}

void CWizard::ESkillHit()
{
}

void CWizard::RSkillHit()
{
}
