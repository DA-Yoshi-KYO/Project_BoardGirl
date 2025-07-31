#include "EnemyBase.h"
#include "Main.h"
#include "Player.h"
#include "Defines.h"

CEnemyBase::CEnemyBase()
    : m_tEnemyStatus{}
{
}

CEnemyBase::~CEnemyBase()
{

}

void CEnemyBase::Init()
{

}

void CEnemyBase::Update()
{
    m_f3OldPos = m_tParam.m_f3Pos;
    DirectX::XMFLOAT3 f3PlayerPos = GetScene()->GetGameObject<CPlayer>()->AccessorPos();
    DirectX::XMVECTOR vecPlayerPos = DirectX::XMLoadFloat3(&f3PlayerPos);
    DirectX::XMVECTOR vecEnemyPos  = DirectX::XMLoadFloat3(&m_tParam.m_f3Pos);
    DirectX::XMVECTOR vecDirection = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(vecPlayerPos, vecEnemyPos));
    DirectX::XMVECTOR vecVelocity = vecDirection * 0.1f;
    DirectX::XMFLOAT3 f3Velocity;
    DirectX::XMStoreFloat3(&f3Velocity, vecVelocity);
    m_tParam.m_f3Pos += f3Velocity;

    CGameObject::Update();
}

void CEnemyBase::OnColliderHit(CCollisionBase* other)
{
    if (other->AccessorTag() == "PlayerBody")
    {
        m_tParam.m_f3Pos = m_f3OldPos;
    }
    else return;
}

void CEnemyBase::Damage(int inDamage)
{
    m_tEnemyStatus.m_nHP -= inDamage;
    if (m_tEnemyStatus.m_nHP <= 0)
    {
        Destroy();
    }
}
