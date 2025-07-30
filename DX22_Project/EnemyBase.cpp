#include "EnemyBase.h"

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
