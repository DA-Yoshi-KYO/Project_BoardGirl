#pragma once

#include "GameObject.h"

struct AttackState
{
    DirectX::XMFLOAT3 m_f3Center;
    DirectX::XMFLOAT3 m_f3Size;
    DirectX::XMFLOAT3 m_f3Direction;
    float m_fAttackDuration;
    int m_nDamage;
    std::string m_sTexKey;
};

class CEnemyAttack : public CGameObject
{
public:
    CEnemyAttack();
    virtual ~CEnemyAttack();
    void Init() override;
    void Update() override;
    void Draw() override;
    void OnColliderHit(CCollisionBase* other, std::string thisTag = "None") override;

    void SetAttackState(AttackState inState) { m_tAttackState = inState; }
    void SetCenter(DirectX::XMFLOAT3 inCenter) { m_tAttackState.m_f3Center = inCenter; }
    void SetSize(DirectX::XMFLOAT3 inSize) { m_tAttackState.m_f3Size = inSize; }
    void SetDirection(DirectX::XMFLOAT3 inDirection) { m_tAttackState.m_f3Direction = inDirection; }
    void SetAttackDuration(float inAttackDuration) { m_tAttackState.m_fAttackDuration = inAttackDuration; }
    void SetAttack(float inAttack) { m_tAttackState.m_nDamage = inAttack; }

private:
    AttackState m_tAttackState;
    float m_fTime;

};
