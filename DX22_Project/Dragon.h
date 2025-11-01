#pragma once

// インクルード部
#include "EnemyBase.h"

/// <summary>
/// 敵：ドラゴンの実装クラス
/// </summary>
class CDragon : public CEnemyBase
{
public:
    CDragon();
    virtual ~CDragon();
    void Init() override;
    void Attack() override;

private:
    /// <summary>
    /// 通常攻撃
    /// </summary>
    void AttackNormal();

    /// <summary>
    /// ブレス攻撃
    /// </summary>
    void AttackBreath();

};
