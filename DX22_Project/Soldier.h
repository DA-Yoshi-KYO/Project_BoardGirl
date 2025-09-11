#pragma once

#include "Job.h"

class CSoldier : public CJob
{
public:
    CSoldier();
    virtual ~CSoldier();
    void NormalAttack() override;
    void QSkill() override;
    void ESkill() override;
    void RSkill() override;
private:
    void AllSkill(eSkill inKind);
};
