#pragma once

#include "Job.h"

class CSoldier : public CJob
{
public:
    void Skill(eSkill inKind) override;
};

