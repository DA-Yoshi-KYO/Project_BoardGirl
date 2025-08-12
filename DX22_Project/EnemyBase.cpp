#include "EnemyBase.h"
#include "Main.h"
#include "Oparation.h"
#include "Player.h"

CEnemyBase::CEnemyBase()
    : m_tEnemyStatus{}, m_pPlayer(nullptr), m_fTime(0.0f)
{
    m_tEnemyStatus.m_nHP = 10;
    m_tEnemyStatus.m_nAttack = 2;
    m_tEnemyStatus.m_nDefense = 1;
    m_tEnemyStatus.m_bMove = false;
    m_tEnemyStatus.m_fSpeed = 0.05f;
    m_fAttackTime = 0.0f;
    for (int i = 0; i < (int)EnemyCollision::Max; i++)
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
    for (int i = 0; i < (int)EnemyCollision::Max; i++)
    {
        m_pCollision[i] = AddComponent<CCollisionObb>();
        m_pCollision[i]->AccessorActive(true);
        m_pCollision[i]->AccessorCenter(m_tParam.m_f3Pos);
    }
    m_pCollision[(int)EnemyCollision::Body]->AccessorHalfSize(m_tParam.m_f3Size / 2.0f);
    m_pCollision[(int)EnemyCollision::Body]->AccessorTag("EnemyBody");
    m_pCollision[(int)EnemyCollision::Search]->AccessorHalfSize(DirectX::XMFLOAT3(5.0f, 5.0f, 5.0f));
    m_pCollision[(int)EnemyCollision::Search]->AccessorTag("EnemySearch");
    m_pCollision[(int)EnemyCollision::Attack]->AccessorHalfSize(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
    m_pCollision[(int)EnemyCollision::Attack]->AccessorTag("EnemyAttack");

    m_pHPBar = GetScene()->AddGameObject<CHPBar>();
    m_pHPBar->SetPos(DirectX::XMFLOAT3(m_tParam.m_f3Pos.x, m_tParam.m_f3Pos.y + m_tParam.m_f3Size.y / 1.2f, m_tParam.m_f3Pos.z));
    m_pHPBar->SetRenderState(DirectX::XMFLOAT3(2.0f, 0.25f, 1.0f), DirectX::XMFLOAT4(1.0f,0.0f,0.0f,1.0f));
    m_pHPBar->SetMaxHP(m_tEnemyStatus.m_nHP);
    m_pHPBar->SetCurrentHP(m_tEnemyStatus.m_nHP);

    m_pPlayer = GetScene()->GetGameObject<CPlayer>();
}

void CEnemyBase::Update()
{
    if (m_tEnemyStatus.m_bMove)
    {
        m_f3OldPos = m_tParam.m_f3Pos;
        DirectX::XMFLOAT3 f3PlayerPos = m_pPlayer->AccessorPos();
        DirectX::XMVECTOR vecPlayerPos = DirectX::XMLoadFloat3(&f3PlayerPos);
        DirectX::XMVECTOR vecEnemyPos = DirectX::XMLoadFloat3(&m_tParam.m_f3Pos);
        DirectX::XMVECTOR vecDirection = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(vecPlayerPos, vecEnemyPos));
        DirectX::XMVECTOR vecVelocity = vecDirection * m_tEnemyStatus.m_fSpeed;
        DirectX::XMFLOAT3 f3Velocity;
        DirectX::XMStoreFloat3(&f3Velocity, vecVelocity);
        m_tParam.m_f3Pos.x += f3Velocity.x;
        m_tParam.m_f3Pos.z += f3Velocity.z;
    }
    m_tEnemyStatus.m_bMove = false;

    for (int i = 0; i <= (int)EnemyCollision::Attack; i++)
    {
        m_pCollision[i]->AccessorCenter(m_tParam.m_f3Pos);
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

    m_pHPBar->SetPos(DirectX::XMFLOAT3(m_tParam.m_f3Pos.x, m_tParam.m_f3Pos.y + m_tParam.m_f3Size.y, m_tParam.m_f3Pos.z));
    m_pHPBar->SetCurrentHP(m_tEnemyStatus.m_nHP);

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
        }

        return;
    }
}

void CEnemyBase::Attack()
{

}

void CEnemyBase::Attack(AttackState inState)
{
    CEnemyAttack* pAttack = GetScene()->AddGameObject<CEnemyAttack>();
    pAttack->Init();
    pAttack->SetAttackState(inState);
}

void CEnemyBase::OnDestroy()
{
    m_pHPBar->Destroy();
}

void CEnemyBase::Damage(int inDamage)
{
    if (m_tEnemyStatus.m_bDamage) return;
    m_tEnemyStatus.m_nHP -= inDamage;
    m_tEnemyStatus.m_bDamage = true;

    if (m_tEnemyStatus.m_nHP <= 0)
    {
        Destroy();
    }
}

void CEnemyBase::SetInvincibly(bool isInvincibly)
{
    m_tEnemyStatus.m_bDamage = isInvincibly;
}
