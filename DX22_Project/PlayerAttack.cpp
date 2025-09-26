// インクルード部
#include "PlayerAttack.h"
#include "EnemyBase.h"
#include "CollisionObb.h"

CPlayerAttack::CPlayerAttack()
    : CAttackObject()
{
}

CPlayerAttack::~CPlayerAttack()
{
}

void CPlayerAttack::Init()
{
    // 攻撃オブジェクト共通の初期化処理
    CAttackObject::Init();

    // コンポーネントの追加
    CCollisionObb* pCollision = AddComponent<CCollisionObb>();
    // コリジョン情報のセット
    pCollision->AccessorCenter(m_tAttackState.m_f3Center);
    pCollision->AccessorHalfSize(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
    pCollision->AccessorTag("PlayerDamage");
    pCollision->AccessorActive(true);
}

void CPlayerAttack::OnColliderHit(CCollisionBase* other, std::string thisTag)
{
    CGameObject* pOtherObject = other->GetGameObject();

    // 攻撃オブジェクトが敵の身体に当たったならダメージを与える
    if (other->AccessorTag() == "EnemyBody")
    {
        dynamic_cast<CEnemyBase*>(pOtherObject)->Damage(m_tAttackState.m_nDamage);
    }
}
