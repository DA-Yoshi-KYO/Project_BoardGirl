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
    m_tAttackState[(int)eSkill::NormalAttack].m_f3Center = pPlayer->AccessorPos();
    m_tAttackState[(int)eSkill::NormalAttack].m_f3Size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
    m_tAttackState[(int)eSkill::NormalAttack].m_fAttackDuration = m_tStatus.m_fAttackDuration[(int)eSkill::NormalAttack];
    m_tAttackState[(int)eSkill::NormalAttack].m_n2Split = DirectX::XMINT2(1, 4);
    m_tAttackState[(int)eSkill::NormalAttack].m_nDamage = m_tStatus.m_nAttack;
    m_tAttackState[(int)eSkill::NormalAttack].m_sTexKey = "WizardNormalAttack";
    m_tAttackState[(int)eSkill::NormalAttack].m_tDirectionState.m_eKind = DirectionKind::Toward;
    m_tAttackState[(int)eSkill::NormalAttack].m_tDirectionState.m_tToward.m_f3Direction = pPlayer->GetForward() * ce_fNormalAttackSpeed;
    CJob::Attack(m_tAttackState[(int)eSkill::NormalAttack]);
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

    m_tAttackState[(int)eSkill::QSkill].m_f3Center = pPlayer->AccessorPos();
    m_tAttackState[(int)eSkill::QSkill].m_f3Size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
    m_tAttackState[(int)eSkill::QSkill].m_fAttackDuration = m_tStatus.m_fAttackDuration[(int)eSkill::QSkill];
    m_tAttackState[(int)eSkill::QSkill].m_n2Split = DirectX::XMINT2(10, 1);
    m_tAttackState[(int)eSkill::QSkill].m_nDamage = m_tStatus.m_nAttack;
    m_tAttackState[(int)eSkill::QSkill].m_sTexKey = "WizardQSkill";
    m_tAttackState[(int)eSkill::QSkill].m_tDirectionState.m_eKind = DirectionKind::Helmite;
    m_tAttackState[(int)eSkill::QSkill].m_tDirectionState.m_tHelmite.m_f3InitPos = f3InitPos;
    m_tAttackState[(int)eSkill::QSkill].m_tDirectionState.m_tHelmite.m_f3TargetPos = f3TargetPos;
    m_tAttackState[(int)eSkill::QSkill].m_tDirectionState.m_tHelmite.m_fInitTangentVector[0] = 10.0f;
    m_tAttackState[(int)eSkill::QSkill].m_tDirectionState.m_tHelmite.m_fInitTangentVector[1] = 10.0f;
    m_tAttackState[(int)eSkill::QSkill].m_tDirectionState.m_tHelmite.m_fInitTangentVector[2] = 10.0f;
    m_tAttackState[(int)eSkill::QSkill].m_tDirectionState.m_tHelmite.m_fTargetTangentVector[0] = 0.0f;
    m_tAttackState[(int)eSkill::QSkill].m_tDirectionState.m_tHelmite.m_fTargetTangentVector[1] = 0.0f;
    m_tAttackState[(int)eSkill::QSkill].m_tDirectionState.m_tHelmite.m_fTargetTangentVector[2] = 0.0f;
    CJob::Attack(m_tAttackState[(int)eSkill::QSkill]);
}

void CWizard::ESkill()
{
    m_nOldAttack = m_tStatus.m_nAttack;

    m_tStatus.m_nAttack *= 2;
    m_bAttackUp = true;

    CPlayer* pPlayer = GetScene()->GetGameObject<CPlayer>();
    m_tAttackState[(int)eSkill::ESkill].m_f3Center = pPlayer->AccessorPos();
    m_tAttackState[(int)eSkill::ESkill].m_f3Size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
    m_tAttackState[(int)eSkill::ESkill].m_fAttackDuration = m_tStatus.m_fAttackDuration[(int)eSkill::QSkill];
    m_tAttackState[(int)eSkill::ESkill].m_n2Split = DirectX::XMINT2(5, 4);
    m_tAttackState[(int)eSkill::ESkill].m_nDamage = 0;
    m_tAttackState[(int)eSkill::ESkill].m_sTexKey = "WizardESkill";
    m_tAttackState[(int)eSkill::ESkill].m_tDirectionState.m_eKind = DirectionKind::FollowUp;
    m_tAttackState[(int)eSkill::ESkill].m_tDirectionState.m_tFollowUp.pTarget = pPlayer;
    DirectX::XMFLOAT3 temp = DirectX::XMFLOAT3();
    m_tAttackState[(int)eSkill::ESkill].m_tDirectionState.m_tFollowUp.m_f3Offset = &temp;
    CJob::Attack(m_tAttackState[(int)eSkill::ESkill]);
    m_tAttackState[(int)eSkill::ESkill].m_n2Split = DirectX::XMINT2(10, 1);
    m_tAttackState[(int)eSkill::ESkill].m_nDamage = 0;
    m_tAttackState[(int)eSkill::ESkill].m_sTexKey = "WizardESkill2";
    m_tAttackState[(int)eSkill::ESkill].m_fAttackDuration = 5.0f;
    m_tAttackState[(int)eSkill::ESkill].m_tDirectionState.m_eKind = DirectionKind::FollowUp;
    DirectX::XMFLOAT3 temp2 = pPlayer->GetRight();
    m_tAttackState[(int)eSkill::ESkill].m_tDirectionState.m_tFollowUp.m_f3Offset = &temp2;
    m_tAttackState[(int)eSkill::ESkill].m_tDirectionState.m_tFollowUp.pTarget = pPlayer;
    m_tAttackState[(int)eSkill::ESkill].m_nSpeed = 5;
    CJob::Attack(m_tAttackState[(int)eSkill::ESkill]);
}

void CWizard::RSkill()
{
    CPlayer* pPlayer = GetScene()->GetGameObject<CPlayer>();
    m_tAttackState[(int)eSkill::RSkill].m_f3Center = pPlayer->AccessorPos();
    m_tAttackState[(int)eSkill::RSkill].m_f3Size = DirectX::XMFLOAT3(5.0f, 5.0f, 5.0f);
    m_tAttackState[(int)eSkill::RSkill].m_fAttackDuration = m_tStatus.m_fAttackDuration[(int)eSkill::RSkill];
    m_tAttackState[(int)eSkill::RSkill].m_n2Split = DirectX::XMINT2(5, 2);
    m_tAttackState[(int)eSkill::RSkill].m_nDamage = m_tStatus.m_nAttack;
    m_tAttackState[(int)eSkill::RSkill].m_sTexKey = "WizardRSkill";
    m_tAttackState[(int)eSkill::RSkill].m_tDirectionState.m_eKind = DirectionKind::FollowUp;
    DirectX::XMFLOAT3 temp = DirectX::XMFLOAT3();
    m_tAttackState[(int)eSkill::ESkill].m_tDirectionState.m_tFollowUp.m_f3Offset = &temp;
    m_tAttackState[(int)eSkill::RSkill].m_tDirectionState.m_tFollowUp.pTarget = pPlayer;
    m_tAttackState[(int)eSkill::RSkill].m_nSpeed = 5;

    CJob::Attack(m_tAttackState[(int)eSkill::RSkill]);
}
