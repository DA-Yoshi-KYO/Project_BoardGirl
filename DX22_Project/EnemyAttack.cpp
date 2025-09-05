#include "EnemyAttack.h"
#include "Player.h"
#include "CollisionObb.h"

CEnemyAttack::CEnemyAttack()
    : CAttackObject()
{

}

CEnemyAttack::~CEnemyAttack()
{
}

void CEnemyAttack::Init()
{
    CAttackObject::Init();
    CCollisionObb* pCollision = AddComponent<CCollisionObb>();
    pCollision->AccessorCenter(m_tAttackState.m_f3Center);
    pCollision->AccessorHalfSize(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
    pCollision->AccessorTag("EnemyDamage");
    pCollision->AccessorActive(true);
}

void CEnemyAttack::OnColliderHit(CCollisionBase* other, std::string thisTag)
{
    CGameObject* pOtherObject = other->GetGameObject();
    if (other->AccessorTag() == "PlayerBody")
    {
        dynamic_cast<CPlayer*>(pOtherObject)->Damage(m_tAttackState.m_nDamage);
        GetComponent<CCollisionObb>()->AccessorActive(false);
    }
}
