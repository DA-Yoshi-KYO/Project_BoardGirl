#pragma once

// インクルード部
#include "AttackObject.h"

// スキルの種類
enum class eSkill
{
    NormalAttack,   // 通常攻撃
    QSkill,         // Qスキル
    ESkill,         // Eスキル
    RSkill,         // Rスキル

    Max
};

/// <summary>
/// プレイヤーの攻撃オブジェクトを扱うクラス
/// </summary>
class CPlayerAttack: public CAttackObject
{
public:
    CPlayerAttack();
    virtual ~CPlayerAttack();
    void Init() override;
    void OnColliderHit(CCollisionBase* other, std::string thisTag = "None") override;

};
