#pragma once

#include "AttackObject.h"

class CEnemyAttack : public CAttackObject
{
public:
    CEnemyAttack();
    virtual ~CEnemyAttack();
    void Init() override;
    void OnColliderHit(CCollisionBase* other, std::string thisTag = "None") override;
};
