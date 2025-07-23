#pragma once

#include "Job.h"

class CFighter : public CJob
{
public:
    void Skill(eSkill inKind) override;
};

