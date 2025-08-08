#pragma once

#include "GameObject.h"

enum class eEffectKind
{
    PlayerSwordAttackHit,
    EnemyAttackHit,
};

class CEffect : public CGameObject
{
public:
    virtual ~CEffect();
    void Init() override;
    void Update() override;
    void SetParam(eEffectKind inKind,float inTick);
    
private:
    DirectX::XMINT2 m_n2Split;
    float m_fTime;
    float m_fStepTime;
    int m_nStep;
};
