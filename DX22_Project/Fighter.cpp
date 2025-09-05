#include "Fighter.h"

CFighter::CFighter()
{
    m_tStatus.m_nHP = 100;
    m_tStatus.m_fCriticalPercentage = 1.0f / 8.0f;
    m_tStatus.m_nAttack = 1;
    m_tStatus.m_nDefense = 1;

    m_tStatus.m_fSkillCooltime[(int)eSkill::NormalAttack] = 0.5f;
    m_tStatus.m_fSkillCooltime[(int)eSkill::QSkill] = 3.0f;
    m_tStatus.m_fSkillCooltime[(int)eSkill::ESkill] = 5.0f;
    m_tStatus.m_fSkillCooltime[(int)eSkill::RSkill] = 15.0f;

    m_tStatus.m_fAttackDuration[(int)eSkill::NormalAttack] = 0.5f;
    m_tStatus.m_fAttackDuration[(int)eSkill::QSkill] = 1.0f;
    m_tStatus.m_fAttackDuration[(int)eSkill::ESkill] = 1.0f;
    m_tStatus.m_fAttackDuration[(int)eSkill::RSkill] = 2.0f;

    ObbInfo info[(int)eSkill::Max];
    info[(int)eSkill::NormalAttack] = { {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f,1.0f} };
    info[(int)eSkill::QSkill] = { {0.0f, 0.0f, 0.0f}, {2.0f, 2.0f, 2.0f} };
    info[(int)eSkill::ESkill] = { {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} };
    info[(int)eSkill::RSkill] = { {0.0f, 0.0f, 0.0f}, {3.0f, 3.0f, 3.0f} };
    for (int i = 0; i < (int)eSkill::Max; i++)
    {

        m_tStatus.m_fDurationTime[i] = 0.0f;
        m_tStatus.m_fSkillTime[i] = 0.0f;
    }
}

CFighter::~CFighter()
{
}

void CFighter::NormalAttack()
{
}

void CFighter::QSkill()
{
}

void CFighter::ESkill()
{
}

void CFighter::RSkill()
{
}
