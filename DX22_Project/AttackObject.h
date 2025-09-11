#pragma once

#include "GameObject.h"

enum class DirectionKind
{
    Stay,
    Toward,
    Helmite,
    FollowUp
};

struct DirectionState
{
    DirectionState() {};
    DirectionKind m_eKind;
    union
    {
        struct StayValue
        {
            DirectX::XMFLOAT3 m_f3StayPos;
        }m_tStayPos;

        struct TowardValue
        {
            DirectX::XMFLOAT3 m_f3Direction;
        }m_tToward;

        struct HelmiteValue
        {
        public:
            DirectX::XMFLOAT3 m_f3InitPos;
            DirectX::XMFLOAT3 m_f3TargetPos;
            float m_fInitTangentVector[3];
            float m_fTargetTangentVector[3];

        private:
            float m_fTime = 0.0f;

        }m_tHelmite;

        struct FollowUpValue
        {
            CGameObject* pTarget;
        }m_tFollowUp;
    };
};

struct AttackState
{
    DirectX::XMFLOAT3 m_f3Center;
    DirectX::XMFLOAT3 m_f3Size;
    float m_fAttackDuration;
    int m_nDamage;
    std::string m_sTexKey;
    DirectX::XMINT2 m_n2Split;
    DirectionState m_tDirectionState;
};


class CAttackObject : public CGameObject
{
public:
    CAttackObject();
    virtual ~CAttackObject();
    void Init() override;
    void Update() override;
    void Draw() override;
    void OnColliderHit(CCollisionBase* other, std::string thisTag = "None") override;

    void SetAttackState(AttackState inState) { m_tAttackState = inState; }
    void SetCenter(DirectX::XMFLOAT3 inCenter) { m_tAttackState.m_f3Center = inCenter; }
    void SetSize(DirectX::XMFLOAT3 inSize) { m_tAttackState.m_f3Size = inSize; }
    void SetAttackDuration(float inAttackDuration) { m_tAttackState.m_fAttackDuration = inAttackDuration; }
    void SetAttack(int inAttack) { m_tAttackState.m_nDamage = inAttack; }

    void SetDirection(DirectionState inDirState) { m_tAttackState.m_tDirectionState = inDirState; };

private:
    float m_fTime;
    int m_nStep;
   
protected:
    AttackState m_tAttackState;
};
