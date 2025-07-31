#pragma once

#include "GameObject.h"
#include "CollisionObb.h"

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
    }m_tEnemyStatus;

    CCollisionObb* m_pCollision[static_cast<int>(EnemyCollision::Max)];

};

