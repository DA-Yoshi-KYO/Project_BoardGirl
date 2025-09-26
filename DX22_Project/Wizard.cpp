#include "Wizard.h"
#include "Main.h"
#include "Player.h"
#include "Oparation.h"

constexpr float ce_fNormalAttackSpeed = 0.1f;

CWizard::CWizard()
    : m_fESkillTime(0.0f)
    , m_nOldAttack()
    , m_bAttackUp(false)
{
    m_tStatus.m_nHP = 80;
    m_tStatus.m_nAttack = 2;
    m_nOldAttack = m_tStatus.m_nAttack;

    m_tStatus.m_fSkillCooltime[(int)eSkill::NormalAttack] = 0.5f;
    m_tStatus.m_fSkillCooltime[(int)eSkill::QSkill] = 8.0f;
    m_tStatus.m_fSkillCooltime[(int)eSkill::ESkill] = 8.0f;
    m_tStatus.m_fSkillCooltime[(int)eSkill::RSkill] = 20.0f;

    m_tStatus.m_fAttackDuration[(int)eSkill::NormalAttack] = 0.5f;
    m_tStatus.m_fAttackDuration[(int)eSkill::QSkill] = 1.0f;
    m_tStatus.m_fAttackDuration[(int)eSkill::ESkill] = 4.0f;
    m_tStatus.m_fAttackDuration[(int)eSkill::RSkill] = 5.0f;

    for (int i = 0; i < (int)eSkill::Max; i++)
    {
        m_tStatus.m_fDurationTime[i] = 0.0f;
        m_tStatus.m_fSkillTime[i] = 0.0f;
    }
}

CWizard::~CWizard()
{
}

void CWizard::Update()
{
    if (m_bAttackUp)
    {
        m_fESkillTime += fDeltaTime;
        if (m_fESkillTime >= 5.0f)
        {
            m_bAttackUp = false;
            m_tStatus.m_nAttack = m_nOldAttack;
            m_fESkillTime = 0.0f;
        }
    }
    CJob::Update();
}

void CWizard::NormalAttack()
{
    CPlayer* pPlayer = GetScene()->GetGameObject<CPlayer>();
    AttackState tState;
    tState.m_f3Center = pPlayer->AccessorPos();
    tState.m_f3Size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
    tState.m_fAttackDuration = m_tStatus.m_fAttackDuration[(int)eSkill::NormalAttack];
    tState.m_n2Split = DirectX::XMINT2(1, 4);
    tState.m_nDamage = m_tStatus.m_nAttack;
    tState.m_sTexKey = "WizardNormalAttack";
    tState.m_tDirectionState.m_eKind = DirectionKind::Toward;
    tState.m_tDirectionState.m_tToward.m_f3Direction = pPlayer->GetForward() * ce_fNormalAttackSpeed;
    tState.m_nSpeed = 1;

    CJob::Attack(tState);
}

void CWizard::QSkill()
{
    CPlayer* pPlayer = GetScene()->GetGameObject<CPlayer>();
    DirectX::XMFLOAT3 f3Forward = pPlayer->GetForward();
    DirectX::XMFLOAT3 f3InitPos = pPlayer->AccessorPos();
    DirectX::XMVECTOR vecForward = DirectX::XMLoadFloat3(&f3Forward);
    DirectX::XMVECTOR vecTarget = vecForward * 5.0f;
    DirectX::XMFLOAT3 f3TargetPos;
    DirectX::XMStoreFloat3(&f3TargetPos,vecTarget);
    f3TargetPos += f3InitPos;
    f3TargetPos.y = 0.0f;

    AttackState tState;
    tState.m_f3Center = pPlayer->AccessorPos();
    tState.m_f3Size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
    tState.m_fAttackDuration = m_tStatus.m_fAttackDuration[(int)eSkill::QSkill];
    tState.m_n2Split = DirectX::XMINT2(10, 1);
    tState.m_nDamage = m_tStatus.m_nAttack;
    tState.m_sTexKey = "WizardQSkill";
    tState.m_tDirectionState.m_eKind = DirectionKind::Helmite;
    tState.m_tDirectionState.m_tHelmite.m_f3InitPos = f3InitPos;
    tState.m_tDirectionState.m_tHelmite.m_f3TargetPos = f3TargetPos;
    tState.m_tDirectionState.m_tHelmite.m_fInitTangentVector = DirectX::XMFLOAT3(10.0f,10.0f,10.0f);
    tState.m_tDirectionState.m_tHelmite.m_fTargetTangentVector = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    tState.m_nSpeed = 1;

    CJob::Attack(tState);
}

void CWizard::ESkill()
{
    m_nOldAttack = m_tStatus.m_nAttack;

    m_tStatus.m_nAttack *= 2;
    m_bAttackUp = true;

    CPlayer* pPlayer = GetScene()->GetGameObject<CPlayer>();
    AttackState tState;
    tState.m_f3Center = pPlayer->AccessorPos();
    tState.m_f3Size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
    tState.m_fAttackDuration = m_tStatus.m_fAttackDuration[(int)eSkill::QSkill];
    tState.m_n2Split = DirectX::XMINT2(5, 4);
    tState.m_nDamage = 0;
    tState.m_sTexKey = "WizardESkill";
    tState.m_tDirectionState.m_eKind = DirectionKind::FollowUp;
    tState.m_tDirectionState.m_tFollowUp.pTarget = pPlayer;
    tState.m_nSpeed = 1;
    CJob::Attack(tState);

    tState.m_n2Split = DirectX::XMINT2(10, 1);
    tState.m_nDamage = 0;
    tState.m_sTexKey = "WizardESkill2";
    tState.m_fAttackDuration = 5.0f;
    tState.m_tDirectionState.m_eKind = DirectionKind::FollowUp;
    tState.m_tDirectionState.m_tFollowUp.pTarget = pPlayer;
    tState.m_nSpeed = 5;
    tState.m_nSpeed = 1;
    CJob::Attack(tState);
}

void CWizard::RSkill()
{
    CPlayer* pPlayer = GetScene()->GetGameObject<CPlayer>();
    AttackState tState;
    tState.m_f3Center = pPlayer->AccessorPos();
    tState.m_f3Size = DirectX::XMFLOAT3(5.0f, 5.0f, 5.0f);
    tState.m_fAttackDuration = m_tStatus.m_fAttackDuration[(int)eSkill::RSkill];
    tState.m_n2Split = DirectX::XMINT2(5, 2);
    tState.m_nDamage = m_tStatus.m_nAttack;
    tState.m_sTexKey = "WizardRSkill";
    tState.m_tDirectionState.m_eKind = DirectionKind::FollowUp;
    tState.m_tDirectionState.m_tFollowUp.pTarget = pPlayer;
    tState.m_nSpeed = 5;

    CJob::Attack(tState);
}
