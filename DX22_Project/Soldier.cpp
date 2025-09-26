#include "Soldier.h"
#include "Player.h"
#include "Main.h"
#include "Oparation.h"

CSoldier::CSoldier()
    : CJob()
{
    m_tStatus.m_nHP = 100;
    m_tStatus.m_nAttack = 2;
    
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


    AttackState tState;
    tState.m_f3Center = f3AttackPos;
    tState.m_tDirectionState.m_eKind = DirectionKind::Stay;
    tState.m_tDirectionState.m_tStayPos.m_f3StayPos = f3AttackPos;
    switch (inKind)
    {
    case eSkill::NormalAttack:
        tState.m_f3Size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
        tState.m_fAttackDuration = 0.5f;
        tState.m_n2Split = DirectX::XMINT2(9, 1);
        tState.m_nDamage = m_tStatus.m_nAttack;
        tState.m_nSpeed = 1;
        tState.m_sTexKey = "SwordNormalAttack";
        break;
    case eSkill::QSkill:
        tState.m_f3Size = DirectX::XMFLOAT3(3.0f, 1.0f, 1.0f);
        tState.m_fAttackDuration = 1.0f;
        tState.m_n2Split = DirectX::XMINT2(5, 3);
        tState.m_nDamage = m_tStatus.m_nAttack * 2;
        tState.m_nSpeed = 1;
        tState.m_sTexKey = "SwordQSkill";
        break;
    case eSkill::ESkill:
        tState.m_f3Size = DirectX::XMFLOAT3(1.0f, 1.0f, 3.0f);
        tState.m_fAttackDuration = 1.0f;
        tState.m_n2Split = DirectX::XMINT2(5, 2);
        tState.m_nDamage = m_tStatus.m_nAttack * 2;
        tState.m_nSpeed = 1;
        tState.m_sTexKey = "SwordESkill";
        break;
    case eSkill::RSkill:
        tState.m_f3Size = DirectX::XMFLOAT3(3.0f, 3.0f, 3.0f);
        tState.m_fAttackDuration = 2.0f;
        tState.m_n2Split = DirectX::XMINT2(2, 12);
        tState.m_nDamage = m_tStatus.m_nAttack * 2;
        tState.m_nSpeed = 1;
        tState.m_sTexKey = "SwordRSkill";
        break;
    case eSkill::Max:
        break;
    default:
        break;
    }

    CJob::Attack(tState);
}
