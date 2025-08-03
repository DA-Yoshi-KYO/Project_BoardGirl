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
    void NormalAttackHit() override;
    void QSkillHit() override;
    void ESkillHit() override;
    void RSkillHit() override;
private:
    DirectX::XMFLOAT3 m_f3Forward;
    DirectX::XMFLOAT3 m_f3InitPos;
    DirectX::XMFLOAT3 m_f3TargetPos;
    int m_nOldAttack;
};
