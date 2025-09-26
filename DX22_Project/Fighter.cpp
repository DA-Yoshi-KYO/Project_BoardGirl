#include "Fighter.h"
#include "Main.h"
#include "Player.h"
#include "Input.h"
#include "Oparation.h"

CFighter::CFighter()
    : m_bQSkill(false), m_bRSkill(false), m_nLastSpawnEffectCount(0)
{
    m_tStatus.m_nHP = 100;
    m_tStatus.m_nAttack = 1;

    m_tStatus.m_fSkillCooltime[(int)eSkill::NormalAttack] = 0.5f;
    m_tStatus.m_fSkillCooltime[(int)eSkill::QSkill] = 8.0f;
    m_tStatus.m_fSkillCooltime[(int)eSkill::ESkill] = 15.0f;
    m_tStatus.m_fSkillCooltime[(int)eSkill::RSkill] = 15.0f;

    m_tStatus.m_fAttackDuration[(int)eSkill::NormalAttack] = 0.5f;
    m_tStatus.m_fAttackDuration[(int)eSkill::QSkill] = 1.0f;
    m_tStatus.m_fAttackDuration[(int)eSkill::ESkill] = 1.0f;
    m_tStatus.m_fAttackDuration[(int)eSkill::RSkill] = 0.5f;

    for (int i = 0; i < (int)eSkill::Max; i++)
    {
        m_tStatus.m_fDurationTime[i] = 0.0f;
        m_tStatus.m_fSkillTime[i] = 0.0f;
    }
}

CFighter::~CFighter()
{
}

void CFighter::Update()
{
    static float fQSkillTime = 0.0f;
    if (m_bQSkill)
    {
        fQSkillTime += fDeltaTime;
        if (fQSkillTime >= 5.0f)
        {
            fQSkillTime = 5.0f;
        }

        int nDamage = 0;;
        switch ((int)fQSkillTime)
        {
        case 0:
            nDamage = m_tStatus.m_nAttack * 0.5f;
            break;
        case 1:
            nDamage = m_tStatus.m_nAttack * 1.0f;
            break;
        case 2:
            nDamage = m_tStatus.m_nAttack * 1.5f;
            break;
        case 3:
            nDamage = m_tStatus.m_nAttack * 2.0f;
            break;
        case 4:
            nDamage = m_tStatus.m_nAttack * 2.5f;
            break;
        case 5:
            nDamage = m_tStatus.m_nAttack * 3.0f;
            break;
        default:
            nDamage = m_tStatus.m_nAttack * 0.5f;
            break;
        }

        if (m_nLastSpawnEffectCount != (int)fQSkillTime && m_nLastSpawnEffectCount < 4)
        {
            int nChargeNo = (int)fQSkillTime;
            m_nLastSpawnEffectCount = nChargeNo;
            std::string sKey = "FighterQSkillCharge" + std::to_string(nChargeNo + 1);
            AttackState tState;
            CPlayer* pPlayer = GetScene()->GetGameObject<CPlayer>();
            tState.m_f3Center = pPlayer->AccessorPos();
            tState.m_f3Size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
            tState.m_fAttackDuration = 1.0f;
            tState.m_nDamage = 0.0f;
            tState.m_tDirectionState.m_eKind = DirectionKind::FollowUp;
            tState.m_tDirectionState.m_tFollowUp.pTarget = pPlayer;
            tState.m_sTexKey = sKey;
            tState.m_n2Split = DirectX::XMINT2(10, 1);
            tState.m_nSpeed = 1;
            CJob::Attack(tState);
        }

        if (IsKeyRelease('Q'))
        {
            CPlayer* pPlayer = GetScene()->GetGameObject<CPlayer>();
            DirectX::XMFLOAT3 f3Pos = pPlayer->AccessorPos();
            DirectX::XMFLOAT3 f3Forward = pPlayer->GetForward();
            DirectX::XMVECTOR vPos = XMLoadFloat3(&f3Pos);
            DirectX::XMVECTOR vForward = XMLoadFloat3(&f3Forward);
            vForward = DirectX::XMVector3Normalize(vForward);
            vForward = DirectX::XMVectorScale(vForward, 1.0f);
            vPos = vPos + vForward;
            DirectX::XMFLOAT3 f3AttackPos;
            DirectX::XMStoreFloat3(&f3AttackPos, vPos);

            AttackState tState;
            tState.m_f3Center = f3AttackPos;
            tState.m_f3Size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f) * (((int)fQSkillTime + 1) * 0.5f);
            tState.m_fAttackDuration = m_tStatus.m_fAttackDuration[(int)eSkill::QSkill];
            tState.m_nDamage = nDamage;
            tState.m_tDirectionState.m_eKind = DirectionKind::Stay;
            tState.m_tDirectionState.m_tStayPos.m_f3StayPos = f3AttackPos;
            tState.m_sTexKey = "FighterQSkill";
            tState.m_n2Split = DirectX::XMINT2(5, 2);
            tState.m_nSpeed = 1;
            CJob::Attack(tState);
            m_bQSkill = false;
            fQSkillTime = 0.0f;
            m_nLastSpawnEffectCount = 0;
        }
    }

    static float fRSkillTime = 0.0f;
    static int nRSkillCnt = 0;
    if (m_bRSkill)
    {
        fRSkillTime += fDeltaTime;
        if (fRSkillTime >= 0.1f)
        {
            nRSkillCnt++;
            fRSkillTime = 0.0f;

            CPlayer* pPlayer = GetScene()->GetGameObject<CPlayer>();
            DirectX::XMFLOAT3 f3Pos = pPlayer->AccessorPos();
            DirectX::XMFLOAT3 f3Forward = pPlayer->GetForward();
            DirectX::XMVECTOR vPos = XMLoadFloat3(&f3Pos);
            DirectX::XMVECTOR vForward = XMLoadFloat3(&f3Forward);
            vForward = DirectX::XMVector3Normalize(vForward);
            vForward = DirectX::XMVectorScale(vForward, 1.0f);
            vPos = vPos + vForward;
            DirectX::XMFLOAT3 f3AttackPos;
            DirectX::XMStoreFloat3(&f3AttackPos, vPos);

            DirectX::XMFLOAT3 f3Right = pPlayer->GetRight();
            int nRandXZ = GetRandOfRange(-50, 50);
            float fRandXZ = (float)nRandXZ / 50.0f;
            f3AttackPos += f3Right * (fRandXZ * 2.0f);
            int nRandY = GetRandOfRange(-50, 50);
            float fRandY = (float)nRandY / 50.0f;
            f3AttackPos.y = pPlayer->AccessorSize().y * fRandY + pPlayer->AccessorPos().y;

            AttackState tState;
            tState.m_f3Center = f3AttackPos;
            tState.m_f3Size = DirectX::XMFLOAT3({ 1.0f, 1.0f, 1.0f });
            tState.m_fAttackDuration = m_tStatus.m_fAttackDuration[(int)eSkill::RSkill];
            tState.m_nDamage = m_tStatus.m_nAttack;
            tState.m_tDirectionState.m_eKind = DirectionKind::Stay;
            tState.m_tDirectionState.m_tStayPos.m_f3StayPos = f3AttackPos;
            tState.m_sTexKey = "FighterRSkill";
            tState.m_n2Split = DirectX::XMINT2(5, 1);
            tState.m_nSpeed = 1;
            CJob::Attack(tState);
        }

        if (nRSkillCnt >= 10)
        {
            nRSkillCnt = 0;
            m_bRSkill = false;
        }
    }
    CJob::Update();
}

void CFighter::NormalAttack()
{
    CPlayer* pPlayer = GetScene()->GetGameObject<CPlayer>();
    DirectX::XMFLOAT3 f3Pos = pPlayer->AccessorPos();
    DirectX::XMFLOAT3 f3Forward = pPlayer->GetForward();
    DirectX::XMVECTOR vPos = XMLoadFloat3(&f3Pos);
    DirectX::XMVECTOR vForward = XMLoadFloat3(&f3Forward);
    vForward = DirectX::XMVector3Normalize(vForward);
    vForward = DirectX::XMVectorScale(vForward, 1.0f);
    vPos = vPos + vForward;
    DirectX::XMFLOAT3 f3AttackPos;
    DirectX::XMStoreFloat3(&f3AttackPos, vPos);

    AttackState tState;
    tState.m_f3Center = f3AttackPos;
    tState.m_f3Size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
    tState.m_fAttackDuration = m_tStatus.m_fAttackDuration[(int)eSkill::NormalAttack];
    tState.m_nDamage = m_tStatus.m_nAttack;
    tState.m_tDirectionState.m_eKind = DirectionKind::Stay;
    tState.m_tDirectionState.m_tStayPos.m_f3StayPos = f3AttackPos;
    tState.m_sTexKey = "FighterNormalAttack";
    tState.m_n2Split = DirectX::XMINT2(10,1);
    tState.m_nSpeed = 1;
    CJob::Attack(tState);
}

void CFighter::QSkill()
{
    m_bQSkill = true;

    CPlayer* pPlayer = GetScene()->GetGameObject<CPlayer>();
    AttackState tState;
    tState.m_f3Center = pPlayer->AccessorPos();
    tState.m_f3Size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
    tState.m_fAttackDuration = 1.0f;
    tState.m_nDamage = 0;
    tState.m_tDirectionState.m_eKind = DirectionKind::FollowUp;
    tState.m_tDirectionState.m_tFollowUp.pTarget = pPlayer;
    tState.m_sTexKey = "FighterQSkillCharge1";
    tState.m_n2Split = DirectX::XMINT2(10, 1);
    tState.m_nSpeed = 1;
    CJob::Attack(tState);
}

void CFighter::ESkill()
{
    m_tStatus.m_nHP += 10;
    m_tStatus.m_nHP = std::min(m_tStatus.m_nHP, 100);

    CPlayer* pPlayer = GetScene()->GetGameObject<CPlayer>();
    AttackState tState;
    tState.m_f3Center = pPlayer->AccessorPos();
    tState.m_f3Size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
    tState.m_fAttackDuration = m_tStatus.m_fAttackDuration[(int)eSkill::ESkill];
    tState.m_nDamage = 0;
    tState.m_tDirectionState.m_eKind = DirectionKind::FollowUp;
    tState.m_tDirectionState.m_tFollowUp.pTarget = pPlayer;
    tState.m_sTexKey = "FighterESkill";
    tState.m_n2Split = DirectX::XMINT2(8,1);
    tState.m_nSpeed = 1;
    CJob::Attack(tState);
}

void CFighter::RSkill()
{
    m_bRSkill = true;
}
