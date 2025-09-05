#include "PlayerAttack.h"
#include "EnemyBase.h"
#include "CollisionObb.h"

CPlayerAttack::CPlayerAttack()
{
}

CPlayerAttack::~CPlayerAttack()
{
}

void CPlayerAttack::Init()
{
    CAttackObject::Init();
    CCollisionObb* pCollision = AddComponent<CCollisionObb>();
    pCollision->AccessorCenter(m_tAttackState.m_f3Center);
    pCollision->AccessorHalfSize(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
    pCollision->AccessorTag("PlayerDamage");
    pCollision->AccessorActive(true);
}

void CPlayerAttack::OnColliderHit(CCollisionBase* other, std::string thisTag)
{
    CGameObject* pOtherObject = other->GetGameObject();
    if (other->AccessorTag() == "EnemyBody")
    {
        dynamic_cast<CEnemyBase*>(pOtherObject)->Damage(m_tAttackState.m_nDamage);
        GetComponent<CCollisionObb>()->AccessorActive(false);
    }
}
