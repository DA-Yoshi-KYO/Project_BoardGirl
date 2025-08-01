#pragma once

#include "GameObject.h"
#include "CollisionObb.h"
#include "HPBar.h"

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
    void Uninit() override;
    void Update() override;
    void OnColliderHit(CCollisionBase* other,std::string thisTag = "None") override;
    void OnDestroy() override;

    void Damage(int inDamage);
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

    CCollisionObb* m_pCollision[static_cast<int>(EnemyCollision::Max)];
    CHPBar* m_pHPBar;

};

