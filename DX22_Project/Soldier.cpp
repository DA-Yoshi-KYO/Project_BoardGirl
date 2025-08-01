#include "Soldier.h"
#include "Player.h"
#include "Main.h"

CSoldier::CSoldier()
    : CJob()
{
    m_tStatus.m_nHP = 100;
    m_tStatus.m_fCriticalPercentage = 12.5f;
    m_tStatus.m_nAttack = 2;
    m_tStatus.m_nDefense = 1;

    m_tStatus.m_fSkillCooltime[(int)eSkill::NormalAttack] = 0.5f;
    m_tStatus.m_fSkillCooltime[(int)eSkill::QSkill] = 5.0f;
    m_tStatus.m_fSkillCooltime[(int)eSkill::ESkill] = 5.0f;
    m_tStatus.m_fSkillCooltime[(int)eSkill::RSkill] = 15.0f;

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

CSoldier::~CSoldier()
{
}

void CSoldier::NormalAttack()
{
    AllSkill(eSkill::NormalAttack);
}

void CSoldier::QSkill()
{
    AllSkill(eSkill::QSkill);
}

void CSoldier::ESkill()
{
    AllSkill(eSkill::ESkill);
}

void CSoldier::RSkill()
{
    AllSkill(eSkill::RSkill);
}

void CSoldier::NormalAttackHit()
{
    m_pTargetEnemy->Damage(m_tStatus.m_nAttack);
}

void CSoldier::QSkillHit()
{
}

void CSoldier::ESkillHit()
{
}

void CSoldier::RSkillHit()
{
}

void CSoldier::AllSkill(eSkill inKind)
{
    if (inKind >= eSkill::Max || inKind < eSkill::NormalAttack) return;

    CPlayer* pPlayer = GetScene()->GetGameObject<CPlayer>();
    DirectX::XMFLOAT3 f3Pos = pPlayer->AccessorPos();
    DirectX::XMFLOAT3 f3Forward = pPlayer->GetForward();
    DirectX::XMVECTOR vPos = XMLoadFloat3(&f3Pos);
    DirectX::XMVECTOR vForward = XMLoadFloat3(&f3Forward);
    vForward = DirectX::XMVector3Normalize(vForward);
    vForward = DirectX::XMVectorScale(vForward, 4.0f);
    vPos = vPos + vForward;
    DirectX::XMFLOAT3 f3AttackPos;
    DirectX::XMStoreFloat3(&f3AttackPos, vPos);

    m_pCollisionObb[(int)inKind]->AccessorCenter(f3AttackPos);
}
