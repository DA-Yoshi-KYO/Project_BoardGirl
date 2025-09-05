#pragma once

#include "GameObject.h"
#include "CollisionObb.h"
#include "Defines.h"
#include "EnemyBase.h"
#include "Effect.h"
#include "PlayerAttack.h"

class CPlayer;

enum class JobKind
{
    Soldier = 0,
    Wizard,
    Fighter,

    Max
};

struct PlayerStatus
{
    int m_nHP;
    int m_nAttack;
    int m_nDefense;
    float m_fSkillTime[(int)eSkill::Max];
    float m_fSkillCooltime[(int)eSkill::Max];
    float m_fDurationTime[(int)eSkill::Max];
    float m_fAttackDuration[(int)eSkill::Max];
    float m_fCriticalPercentage;
};

class CJob
{
public:
    CJob();
    ~CJob();
    virtual void Update();
    virtual bool Skill(eSkill inKind);
    virtual void NormalAttack() = 0;
    virtual void QSkill() = 0;
    virtual void ESkill() = 0;
    virtual void RSkill() = 0;
    
    void Attack(AttackState inState);
    
    void Damage(int inDamage);
    int GetHP() { return m_tStatus.m_nHP; };

private:
    
protected:
    static int m_nLevel;
    static int m_nExp;
    CEnemyBase* m_pTargetEnemy;
    bool isEnd;
    PlayerStatus m_tStatus;
    AttackState m_tAttackState[(int)eSkill::Max];

public:
    PlayerStatus GetStatus() { return m_tStatus; };
};
