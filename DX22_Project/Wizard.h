#pragma once

#include "Job.h"

class CWizard : public CJob
{
public:
    CWizard();
    virtual ~CWizard();
    void NormalAttack() override;
    void QSkill() override;
    void ESkill() override;
    void RSkill() override;
    void NormalAttackHit() override;
    void QSkillHit() override;
    void ESkillHit() override;
    void RSkillHit() override;
};
