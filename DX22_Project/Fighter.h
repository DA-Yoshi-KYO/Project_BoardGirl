#pragma once

#include "Job.h"

class CFighter : public CJob
{
public:
    CFighter();
    virtual ~CFighter();
    void Update() override;
    void NormalAttack() override;
    void QSkill() override;
    void ESkill() override;
    void RSkill() override;

private:
    bool m_bQSkill;
    bool m_bRSkill;
    int m_nLastSpawnEffectCount;

};
