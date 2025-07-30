#pragma once

#include "GameObject.h"
#include "CollisionObb.h"

class CEnemyBase : public CGameObject
{
public:
    CEnemyBase();
    virtual ~CEnemyBase();
    void Init() override;

private:

protected:
    struct EnemyStatus
    {
        int m_nHP;
        int m_nAttack;
        int m_nDefense;
    }m_tEnemyStatus;



};

