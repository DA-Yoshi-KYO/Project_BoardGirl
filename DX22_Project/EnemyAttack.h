#pragma once

// インクルード部
#include "AttackObject.h"

/// <summary>
/// 敵の攻撃オブジェクトを扱うクラス
/// </summary>
class CEnemyAttack : public CAttackObject
{
public:
    CEnemyAttack();
    virtual ~CEnemyAttack();
    void Init() override;
    void OnColliderHit(CCollisionBase* other, std::string thisTag = "None") override;
};
