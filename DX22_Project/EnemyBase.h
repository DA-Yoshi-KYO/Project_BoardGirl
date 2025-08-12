#pragma once

#include "GameObject.h"
#include "CollisionObb.h"
#include "HPBar.h"
#include "EnemyAttack.h"

class CPlayer;

enum class EnemyCollision
{
    Body,
    Search,
    Attack,

    Max
};

class CEnemyBase : public CGameObject
{
public:
    CEnemyBase();
    virtual ~CEnemyBase();
    void Init() override;
    void Update() override;
    void OnColliderHit(CCollisionBase* other,std::string thisTag = "None") override;
    void OnDestroy() override;

    virtual void Attack();
    void Attack(AttackState inState);
    void Damage(int inDamage);
    void SetInvincibly(bool isInvincibly);
    bool GetInvincibly() { return m_tEnemyStatus.m_bDamage; }

private:

protected:
    struct EnemyStatus
    {
        int m_nHP;
        int m_nAttack;
        int m_nDefense;
        float m_fSpeed;

        bool m_bMove;
        bool m_bDamage;
    }m_tEnemyStatus;

    float m_fAttackTime;
    float m_fTime;
    CCollisionObb* m_pCollision[static_cast<int>(EnemyCollision::Max)];
    CHPBar* m_pHPBar;
    CPlayer* m_pPlayer;

};

