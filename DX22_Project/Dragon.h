#pragma once

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
    void AttackNormal();
    void AttackBreath();

};
