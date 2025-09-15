#include "EnemyBase.h"
#include "Main.h"
#include "Oparation.h"
#include "Player.h"
#include "DebugSystem.h"
#include "Field.h"
#include "Score.h"

CEnemyBase::CEnemyBase()
    : m_tEnemyStatus{}, m_pPlayer(nullptr), m_fTime(0.0f)
{
    m_tEnemyStatus.m_nHP = 10;
    m_tEnemyStatus.m_nAttack = 2;
    m_tEnemyStatus.m_nDefense = 1;
    m_tEnemyStatus.m_bMove = false;
    m_tEnemyStatus.m_fSpeed = 0.05f;
    m_fAttackTime = 0.0f;
    m_tEnemyStatus.m_nScore = 10;
    for (int i = 0; i < (int)eEnemyCollision::Max; i++)
    {
        m_pCollision[i] = nullptr;
    }

    m_pHPBar = nullptr;
}

CEnemyBase::~CEnemyBase()
{

}

void CEnemyBase::Init()
{
    for (int i = 0; i < (int)eEnemyCollision::Max; i++)
    {
        m_pCollision[i] = AddComponent<CCollisionObb>();
        m_pCollision[i]->AccessorActive(true);
        m_pCollision[i]->AccessorCenter(m_tParam.m_f3Pos);
    }
    m_pCollision[(int)eEnemyCollision::Body]->AccessorHalfSize(m_tParam.m_f3Size / 2.0f);
    m_pCollision[(int)eEnemyCollision::Body]->AccessorTag("EnemyBody");
    m_pCollision[(int)eEnemyCollision::Search]->AccessorHalfSize(DirectX::XMFLOAT3(5.0f, 5.0f, 5.0f));
    m_pCollision[(int)eEnemyCollision::Search]->AccessorTag("EnemySearch");
    m_pCollision[(int)eEnemyCollision::Attack]->AccessorHalfSize(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
    m_pCollision[(int)eEnemyCollision::Attack]->AccessorTag("EnemyAttack");

    m_pHPBar = GetScene()->AddGameObject<CHPBar>("HPBar",Tag::GameObject);
    m_pHPBar->SetRenderState(DirectX::XMFLOAT3(2.0f, 0.25f, 1.0f), DirectX::XMFLOAT4(1.0f,0.0f,0.0f,1.0f));
    m_pHPBar->SetMaxHP(m_tEnemyStatus.m_nHP);
    m_pHPBar->SetCurrentHP(m_tEnemyStatus.m_nHP);

    m_pPlayer = GetScene()->GetGameObject<CPlayer>();
}

void CEnemyBase::Update()
{
    m_f3OldPos = m_tParam.m_f3Pos;
    if (m_tEnemyStatus.m_bMove)
    {
        m_f3OldPos = m_tParam.m_f3Pos;
        DirectX::XMFLOAT3 f3PlayerPos = m_pPlayer->AccessorPos();
        DirectX::XMFLOAT2 f2PlayerPosXZ = DirectX::XMFLOAT2(f3PlayerPos.x, f3PlayerPos.z);
        DirectX::XMVECTOR vecPlayerPos = DirectX::XMLoadFloat2(&f2PlayerPosXZ);
        DirectX::XMFLOAT2 f2EnemyPosXZ = DirectX::XMFLOAT2(m_tParam.m_f3Pos.x, m_tParam.m_f3Pos.z);
        DirectX::XMVECTOR vecEnemyPos = DirectX::XMLoadFloat2(&f2EnemyPosXZ);
        DirectX::XMVECTOR vecDirection = DirectX::XMVector2Normalize(vecPlayerPos - vecEnemyPos);
        DirectX::XMVECTOR vecVelocity = vecDirection * m_tEnemyStatus.m_fSpeed;
        DirectX::XMFLOAT2 f2Velocity;
        DirectX::XMStoreFloat2(&f2Velocity, vecVelocity);
        m_f3Velocity.x = f2Velocity.x;
        m_f3Velocity.z = f2Velocity.y;
        m_tParam.m_f3Pos.x += m_f3Velocity.x;
        m_tParam.m_f3Pos.z += m_f3Velocity.z;
        DirectX::XMFLOAT2 f2Direction;
        DirectX::XMStoreFloat2(&f2Direction, vecDirection);
        m_tParam.m_f3Rotate.y = atan2(f2Direction.x, f2Direction.y);
    }
    m_tEnemyStatus.m_bMove = false;

    for (int i = 0; i <= (int)eEnemyCollision::Attack; i++)
    {
        m_pCollision[i]->AccessorCenter(m_tParam.m_f3Pos);
    }

    m_tParam.m_f3Pos.y += m_f3Velocity.y;
    DirectX::XMFLOAT3 origin = DirectX::XMFLOAT3(m_tParam.m_f3Pos.x, m_tParam.m_f3Pos.y - m_tParam.m_f3Size.y * 0.5f, m_tParam.m_f3Pos.z);
    HitResult result = CField::RayIntersectsTriangle(m_tParam.m_f3Pos, DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f));

    if (result.Distance <= m_tParam.m_f3Size.y * 0.5f)
    {
        m_tParam.m_f3Pos.y = result.Position.y + m_tParam.m_f3Size.y * 0.5f;
        m_f3Velocity.y = 0.0f;
    }
    else
    {
        // 重力
        m_f3Velocity.y -= 0.015f;
    }

    static float fSwitchTime = 0.0f;
    if (m_tEnemyStatus.m_bDamage)
    {
        if (fSwitchTime >= 0.1f)
        {
            int alpha = (int)m_tParam.m_f4Color.w;
            alpha ^= 1;
            m_tParam.m_f4Color.w = static_cast<float>(alpha);
            fSwitchTime = 0.0f;
        }
        if (m_fTime >= 1.0f)
        {
            m_tEnemyStatus.m_bDamage = false;
            m_tParam.m_f4Color.w = 1.0f;
            m_fTime = 0.0f;
            fSwitchTime = 0.0f;
        }
        m_fTime += fDeltaTime;
        fSwitchTime += fDeltaTime;
    }
    if (m_fAttackTime >= 2.0f)
    {
        Attack();
        m_fAttackTime = 0.0f;
    }

    m_pHPBar->SetCurrentHP(m_tEnemyStatus.m_nHP);
    m_pHPBar->SetParentID(m_tID);

    CGameObject::Update();
}

void CEnemyBase::OnColliderHit(CCollisionBase* other, std::string thisTag)
{
    if (thisTag == "EnemyBody")
    {
        if (other->AccessorTag() == "PlayerBody")
        {
            m_tParam.m_f3Pos = m_f3OldPos;
        }
        if (other->AccessorTag() == "EnemyBody")
        {
            m_tParam.m_f3Pos = m_f3OldPos;
        }

        return;
    }
    if (thisTag == "EnemySearch")
    {
        if (other->AccessorTag() == "PlayerBody")
        {
            m_tEnemyStatus.m_bMove = true;
        }

        return;
    }
    if (thisTag == "EnemyAttack")
    {
        if (other->AccessorTag() == "PlayerBody")
        {
            m_fAttackTime += fDeltaTime;
            m_tEnemyStatus.m_bMove = false;
        }

        return;
    }
}

void CEnemyBase::Attack()
{

}

void CEnemyBase::Attack(AttackState inState)
{
    CEnemyAttack* pAttack = GetScene()->AddGameObject<CEnemyAttack>("EnemyAttack", Tag::GameObject);
    pAttack->Init();
    pAttack->SetAttackState(inState);
    pAttack->AccessorRotate(m_tParam.m_f3Rotate);
}

void CEnemyBase::Destroy()
{
    m_bDestroy = true;
    m_pHPBar->Destroy();
}

void CEnemyBase::Damage(int inDamage)
{
    if (inDamage <= 0) return;
    if (m_tEnemyStatus.m_bDamage) return;
    m_tEnemyStatus.m_nHP -= inDamage;
    m_tEnemyStatus.m_bDamage = true;

    if (m_tEnemyStatus.m_nHP <= 0)
    {
        CScore::AddScore(m_tEnemyStatus.m_nScore);
        Destroy();
    }
}

void CEnemyBase::SetInvincibly(bool isInvincibly)
{
    m_tEnemyStatus.m_bDamage = isInvincibly;
}

eEnemyStatePattern CEnemyBase::GetPattern(DirectX::XMFLOAT3 inAttackHarfSize)
{
    DirectX::XMFLOAT3 f3PlayerPos = m_pPlayer->AccessorPos();
    DirectX::XMVECTOR vecPlayerPos = DirectX::XMLoadFloat3(&f3PlayerPos);
    DirectX::XMVECTOR vecEnemyPos = DirectX::XMLoadFloat3(&m_tParam.m_f3Pos);
    DirectX::XMVECTOR vDistance = vecPlayerPos - vecEnemyPos;
    float fDistance = fabsf(DirectX::XMVectorGetX(vDistance));
    float fMaxDistance = sqrtf(powf(inAttackHarfSize.x, 2) + powf(inAttackHarfSize.z, 2));

    eEnemyStatePattern ePattern;
    float fValue = fDistance / fMaxDistance;
    float fStandardValue = 1.0f / (int)eEnemyStatePattern::Max;

    if (fValue <= fStandardValue) ePattern = eEnemyStatePattern::Near;
    else if (fValue <= fStandardValue * 2) ePattern = eEnemyStatePattern::Middle;
    else ePattern = eEnemyStatePattern::Far;

    return ePattern;
}

eEnemyStatePattern CEnemyBase::GetPattern(DirectX::XMFLOAT3 inAttackHarfSize, eEnemyStatePattern AdjustPattern)
{
    return eEnemyStatePattern();
}

int CEnemyBase::Inspecter(bool isEnd)
{
    int nChildCnt = CGameObject::Inspecter(false);

    if (ImGui::CollapsingHeader(std::string("[Status]").c_str()))
    {
        ImGui::BeginChild(ImGui::GetID((void*)nChildCnt), ImVec2(ce_f2InspecterSize.x, ce_f2InspecterSize.y * 4));

        ImGui::Text(std::string("HP:" + std::to_string(m_tEnemyStatus.m_nHP)).c_str());
        ImGui::Text(std::string("ATK:" + std::to_string(m_tEnemyStatus.m_nAttack)).c_str());
        ImGui::Text(std::string("DEF:" + std::to_string(m_tEnemyStatus.m_nDefense)).c_str());
        ImGui::Text(std::string("SPD:" + std::to_string(m_tEnemyStatus.m_fSpeed)).c_str());

        ImGui::EndChild();
        nChildCnt++;
    }

    ImGui::End();

    return nChildCnt;
}
