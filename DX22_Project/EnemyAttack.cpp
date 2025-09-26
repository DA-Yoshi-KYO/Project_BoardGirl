// インクルード部
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
    // 攻撃オブジェクト共通の初期化処理
    CAttackObject::Init();

    // コンポーネントの追加
    CCollisionObb* pCollision = AddComponent<CCollisionObb>();
    // コリジョン情報のセット
    pCollision->AccessorCenter(m_tAttackState.m_f3Center);
    pCollision->AccessorHalfSize(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
    pCollision->AccessorTag("EnemyDamage");
    pCollision->AccessorActive(true);
}

void CEnemyAttack::OnColliderHit(CCollisionBase* other, std::string thisTag)
{
    CGameObject* pOtherObject = other->GetGameObject();

    // 攻撃オブジェクトがプレイヤーの身体に当たったならダメージを与える
    if (other->AccessorTag() == "PlayerBody")
    {
        dynamic_cast<CPlayer*>(pOtherObject)->Damage(m_tAttackState.m_nDamage);

        // 攻撃は一回限りヒット
        GetComponent<CCollisionObb>()->AccessorActive(false);
    }
}
