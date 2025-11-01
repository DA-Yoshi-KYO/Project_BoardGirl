#pragma once

#include "Job.h"

class CWizard : public CJob
{
public:
    CWizard();
    virtual ~CWizard();
    void Update() override;
    void NormalAttack() override;
    void QSkill() override;
    void ESkill() override;
    void RSkill() override;
private:
    int m_nOldAttack;
    float m_fESkillTime;
    bool m_bAttackUp;
};
