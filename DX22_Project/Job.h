#pragma once

#include "GameObject.h"

enum class eSkill
{
    QSkill = 0,
    ESkill,
    RSkill,

    Max
};

enum class JobKind
{
    Soldier = 0,
    Wizard,
    Fighter,

    Max
};

class CJob
{
public:
    CJob();
    ~CJob();
    virtual void Skill(eSkill inKind) = 0;

private:

protected:
    static int m_nLevel;
    static int m_nExp;
    struct PlayerStatus
    {
        int m_nHP;
        int m_nAttack;
        int m_nDefense;
        float m_fAttackSpeed;
        float m_fSkillCooltime[(int)eSkill::Max];
        float m_fCriticalPercentage;
    };
    PlayerStatus m_tStatus;

};
