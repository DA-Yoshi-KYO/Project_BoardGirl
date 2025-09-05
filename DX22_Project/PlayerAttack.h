#pragma once

#include "AttackObject.h"

enum class eSkill
{
    NormalAttack = 0,
    QSkill,
    ESkill,
    RSkill,

    Max
};

class CPlayerAttack: public CAttackObject
{
public:
    CPlayerAttack();
    virtual ~CPlayerAttack();
    void Init() override;
    void OnColliderHit(CCollisionBase* other, std::string thisTag = "None") override;
};
