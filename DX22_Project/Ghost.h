#pragma once

// インクルード部
#include "EnemyBase.h"

/// <summary>
/// 敵：幽霊の実装クラス
/// </summary>
class CGhost : public CEnemyBase
{
public:
    CGhost();
    virtual ~CGhost();
    void Init() override;
    void Attack() override;

};
