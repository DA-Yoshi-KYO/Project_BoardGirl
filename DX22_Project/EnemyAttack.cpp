#include "EnemyAttack.h"
#include "Oparation.h"
#include "Player.h"
#include "CollisionObb.h"
#include "BillboardRenderer.h"
#include "Main.h"

CEnemyAttack::CEnemyAttack()
    : CGameObject()
    , m_tAttackState{},m_fTime(0.0f)
{

}

CEnemyAttack::~CEnemyAttack()
{
}

void CEnemyAttack::Init()
{
    CCollisionObb* pCollision = AddComponent<CCollisionObb>();
    pCollision->AccessorCenter(m_tAttackState.m_f3Center);
    pCollision->AccessorHalfSize(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
    pCollision->AccessorTag("EnemyDamage");
    pCollision->AccessorActive(true);

    AddComponent<CBillboardRenderer>();
}

void CEnemyAttack::Update()
{
    m_tAttackState.m_f3Center += m_tAttackState.m_f3Direction;
    m_tParam.m_f3Pos = m_tAttackState.m_f3Center;
    m_tParam.m_f3Size = m_tAttackState.m_f3Size;

    CCollisionObb* pCollision = GetComponent<CCollisionObb>();
    if (pCollision)
    {
        pCollision->AccessorCenter(m_tAttackState.m_f3Center);
        pCollision->AccessorHalfSize(m_tAttackState.m_f3Size * 0.5f);
    }

    if (m_fTime >= m_tAttackState.m_fAttackDuration)
        Destroy();

    m_fTime += fDeltaTime;
    CGameObject::Update();
}

void CEnemyAttack::Draw()
{
    // GetComponent<CBillboardRenderer>()->SetKey(m_tAttackState.m_sTexKey);
    CGameObject::Draw();
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
