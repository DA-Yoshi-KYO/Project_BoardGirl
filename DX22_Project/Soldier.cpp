#include "Soldier.h"
#include "Player.h"
#include "Main.h"
#include "Oparation.h"

CSoldier::CSoldier()
    : CJob()
{
    m_tStatus.m_nHP = 100;
    m_tStatus.m_fCriticalPercentage = 1.0f / 16.0f;
    m_tStatus.m_nAttack = 2;
    m_tStatus.m_nDefense = 1;

    m_tStatus.m_fSkillCooltime[(int)eSkill::NormalAttack] = 0.5f;
    m_tStatus.m_fSkillCooltime[(int)eSkill::QSkill] = 5.0f;
    m_tStatus.m_fSkillCooltime[(int)eSkill::ESkill] = 5.0f;
    m_tStatus.m_fSkillCooltime[(int)eSkill::RSkill] = 15.0f;

    m_tStatus.m_fAttackDuration[(int)eSkill::NormalAttack] = 0.5f;
    m_tStatus.m_fAttackDuration[(int)eSkill::QSkill] = 1.0f;
    m_tStatus.m_fAttackDuration[(int)eSkill::ESkill] = 1.0f;
    m_tStatus.m_fAttackDuration[(int)eSkill::RSkill] = 2.0f;

    for (int i = 0; i < (int)eSkill::Max; i++)
    {
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
    f3AttackPos.y = f3Pos.y;
    
    CEffect* pEffect = GetScene()->AddGameObject<CEffect>("SoldierSkill", Tag::GameObject);
    switch (inKind)
    {
    case eSkill::NormalAttack:
        pEffect->SetParam(eEffectKind::PlayerSwordNormalSkill, m_tStatus.m_fAttackDuration[(int)inKind]);
        m_tAttackState[(int)inKind].m_f3Size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
        break;
    case eSkill::QSkill:
        pEffect->SetParam(eEffectKind::PlayerSwordQSkill, m_tStatus.m_fAttackDuration[(int)inKind]);
        m_tAttackState[(int)inKind].m_f3Size = DirectX::XMFLOAT3(3.0f, 1.0f, 1.0f);
        break;
    case eSkill::ESkill:
        pEffect->SetParam(eEffectKind::PlayerSwordESkill, m_tStatus.m_fAttackDuration[(int)inKind]);
        m_tAttackState[(int)inKind].m_f3Size = DirectX::XMFLOAT3(1.0f, 1.0f, 3.0f);
        break;
    case eSkill::RSkill:
        pEffect->SetParam(eEffectKind::PlayerSwordRSkill, m_tStatus.m_fAttackDuration[(int)inKind], 3);
        m_tAttackState[(int)inKind].m_f3Size = DirectX::XMFLOAT3(3.0f, 3.0f, 3.0f);
        break;
    case eSkill::Max:
        break;
    default:
        break;
    }
    pEffect->AccessorPos(f3AttackPos);
    pEffect->AccessorSize(m_tAttackState[(int)inKind].m_f3Size);

    m_tAttackState[(int)inKind].m_f3Center = f3AttackPos;
    m_tAttackState[(int)inKind].m_fAttackDuration = m_tStatus.m_fAttackDuration[(int)inKind];
    m_tAttackState[(int)inKind].m_nDamage = m_tStatus.m_nAttack;
    m_tAttackState[(int)inKind].m_tDirectionState.m_eKind = DirectionKind::Stay;
    m_tAttackState[(int)inKind].m_tDirectionState.m_tStayPos.m_f3StayPos = f3AttackPos;
    CJob::Attack(m_tAttackState[(int)inKind]);
}
