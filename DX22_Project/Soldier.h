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
    void NormalAttackHit() override;
    void QSkillHit() override;
    void ESkillHit() override;
    void RSkillHit() override;
private:
    void AllSkill(eSkill inKind);
};

