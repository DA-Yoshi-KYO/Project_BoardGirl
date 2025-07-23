#pragma once

#include "Job.h"

class CWizard : public CJob
{
public:
    void Skill(eSkill inKind) override;
};

