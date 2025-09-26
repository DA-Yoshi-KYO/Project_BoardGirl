#pragma once

// インクルード部
#include "EnemyBase.h"

class CSlime : public CEnemyBase
{
public:
    CSlime();
    virtual ~CSlime();
    void Init() override;
    void Attack() override;

};
