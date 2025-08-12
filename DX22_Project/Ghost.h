#pragma once

#include "EnemyBase.h"

class CGhost : public CEnemyBase
{
public:
    CGhost();
    virtual ~CGhost();
    void Init() override;
    void Attack() override;

private:

};
