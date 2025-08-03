#include "Wizard.h"
#include "Main.h"
#include "Player.h"

CWizard::CWizard()
    : m_f3Forward{}, m_f3TargetPos{}, m_f3InitPos{}
    , m_nOldAttack()
{
    m_tStatus.m_nHP = 80;
    m_tStatus.m_fCriticalPercentage = 12.5f;
    m_tStatus.m_nAttack = 2;
    m_tStatus.m_nDefense = 1;
    m_nOldAttack = m_tStatus.m_nAttack;

    m_tStatus.m_fSkillCooltime[(int)eSkill::NormalAttack] = 0.5f;
    m_tStatus.m_fSkillCooltime[(int)eSkill::QSkill] = 8.0f;
    m_tStatus.m_fSkillCooltime[(int)eSkill::ESkill] = 8.0f;
    m_tStatus.m_fSkillCooltime[(int)eSkill::RSkill] = 20.0f;

    m_tStatus.m_fAttackDuration[(int)eSkill::NormalAttack] = 0.5f;
    m_tStatus.m_fAttackDuration[(int)eSkill::QSkill] = 1.0f;
    m_tStatus.m_fAttackDuration[(int)eSkill::ESkill] = 4.0f;
    m_tStatus.m_fAttackDuration[(int)eSkill::RSkill] = 5.0f;

    ObbInfo info[(int)eSkill::Max];
    info[(int)eSkill::NormalAttack] = { {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f,1.0f} };
    info[(int)eSkill::QSkill] = { {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f,1.0f} };
    info[(int)eSkill::ESkill] = { {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f,0.0f} };
    info[(int)eSkill::RSkill] = { {0.0f, 0.0f, 0.0f}, {4.0f, 1.0f,4.0f} };
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
    static float fTime[4] = {};
    DirectX::XMFLOAT3 f3ObbPos{};
    CPlayer* pPlayer = GetScene()->GetGameObject<CPlayer>();
    for (int i = 0; i < (int)eSkill::Max; i++)
    {
        if (m_pCollisionObb[i]->AccessorActive())
        {
            switch (i)
            {
            case (int)eSkill::NormalAttack:
                DirectX::XMFLOAT3 f3NowPos = m_pCollisionObb[(int)eSkill::NormalAttack]->AccessorCenter();
                f3ObbPos = f3NowPos + m_f3Forward;
                m_pCollisionObb[(int)eSkill::NormalAttack]->AccessorCenter(f3ObbPos);
                break;
            case (int)eSkill::QSkill:
                DirectX::XMFLOAT3 f3Forward = pPlayer->GetForward();
                f3ObbPos.x = HelmiteValue(fTime[i], m_f3InitPos.x, m_f3TargetPos.x, 10, 0, m_tStatus.m_fAttackDuration[(int)eSkill::QSkill]);
                f3ObbPos.y = HelmiteValue(fTime[i], m_f3InitPos.y, m_f3TargetPos.y, 10, 0, m_tStatus.m_fAttackDuration[(int)eSkill::QSkill]);
                f3ObbPos.z = HelmiteValue(fTime[i], m_f3InitPos.z, m_f3TargetPos.z, 10, 0, m_tStatus.m_fAttackDuration[(int)eSkill::QSkill]);
                m_pCollisionObb[(int)eSkill::QSkill]->AccessorCenter(f3ObbPos);
                break;
            case (int)eSkill::ESkill:
                if (fTime[i] >= 4.0f)
                {
                    m_tStatus.m_nAttack = m_nOldAttack;
                }

                break;
            case (int)eSkill::RSkill:
                f3ObbPos = pPlayer->AccessorPos();
                m_pCollisionObb[(int)eSkill::RSkill]->AccessorCenter(f3ObbPos);

                break;
            default:
                break;
            }
            fTime[i] += fDeltaTime;
        }
        else
        {
            fTime[i] = 0.0f;
            switch (i)
            {
            case (int)eSkill::ESkill:
                m_tStatus.m_nAttack = m_nOldAttack;
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
    CPlayer* pPlayer = GetScene()->GetGameObject<CPlayer>();
    DirectX::XMFLOAT3 f3Forward = pPlayer->GetForward();
    m_f3InitPos = pPlayer->AccessorPos();
    DirectX::XMVECTOR vecForward = DirectX::XMLoadFloat3(&f3Forward);
    DirectX::XMVECTOR vecTarget = vecForward * 5.0f;
    DirectX::XMFLOAT3 f3Target;
    DirectX::XMStoreFloat3(&f3Target,vecTarget);
    m_f3TargetPos = m_f3InitPos + f3Target;
    m_f3TargetPos.y = 0.0f;
}

void CWizard::ESkill()
{
    m_nOldAttack = m_tStatus.m_nAttack;

    m_tStatus.m_nAttack *= 2.0f;

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
    m_pTargetEnemy->Damage(m_tStatus.m_nAttack * 2);
}

void CWizard::ESkillHit()
{
}

void CWizard::RSkillHit()
{
    m_pTargetEnemy->Damage(m_tStatus.m_nAttack * 5);
   // m_pTargetEnemy->SetInvincibly(false);
}
