#pragma once

#include "Job.h"

class CFighter : public CJob
{
public:
    CFighter();
    virtual ~CFighter();
    void NormalAttack() override;
    void QSkill() override;
    void ESkill() override;
    void RSkill() override;
    void NormalAttackHit() override;
    void QSkillHit() override;
    void ESkillHit() override;
    void RSkillHit() override;
};
