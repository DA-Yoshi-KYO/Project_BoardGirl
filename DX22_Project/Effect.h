#pragma once

#include "GameObject.h"

enum class eEffectKind
{
    PlayerSwordNormalSkill,
    PlayerSwordQSkill,
    PlayerSwordESkill,
    PlayerSwordRSkill,
    PlayerAttackHit,
    EnemyAttackHit,
};

class CEffect : public CGameObject
{
public:
    virtual ~CEffect();
    void Init() override;
    void Update() override;
    void SetParam(eEffectKind inKind,float inTotalTime, UINT inPlayNum = 1);
    int GetTotalStep();
    
private:
    DirectX::XMINT2 m_n2Split;
    float m_fTime;
    float m_fStepTime;
    int m_nStep;
    UINT m_nPlayNum;

};
