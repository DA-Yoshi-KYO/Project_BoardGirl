#pragma once

#include "EnemyBase.h"

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
