#include "AttackObject.h"
#include "BillboardRenderer.h"
#include "CollisionObb.h"
#include "Oparation.h"

CAttackObject::CAttackObject()
    : CGameObject()
    , m_tAttackState{}, m_fTime(0.0f), m_nStep(0)
{
}

CAttackObject::~CAttackObject()
{
}

void CAttackObject::Init()
{
    AddComponent<CBillboardRenderer>();
}

void CAttackObject::Update()
{

    switch (m_tAttackState.m_tDirectionState.m_eKind)
    {
    case DirectionKind::Stay:
        m_tAttackState.m_f3Center = m_tAttackState.m_tDirectionState.m_tStayPos.m_f3StayPos;
        break;
    case DirectionKind::Toward:
        m_tAttackState.m_f3Center += m_tAttackState.m_tDirectionState.m_tToward.m_f3Direction;
        break;
    case DirectionKind::Helmite:
        m_tAttackState.m_f3Center.x = HelmiteValue(m_fTime,
            m_tAttackState.m_tDirectionState.m_tHelmite.m_f3InitPos.x, m_tAttackState.m_tDirectionState.m_tHelmite.m_f3TargetPos.x,
            m_tAttackState.m_tDirectionState.m_tHelmite.m_fInitTangentVector[0], m_tAttackState.m_tDirectionState.m_tHelmite.m_fTargetTangentVector[0],
            m_tAttackState.m_fAttackDuration);
        m_tAttackState.m_f3Center.y = HelmiteValue(m_fTime,
            m_tAttackState.m_tDirectionState.m_tHelmite.m_f3InitPos.y, m_tAttackState.m_tDirectionState.m_tHelmite.m_f3TargetPos.y,
            m_tAttackState.m_tDirectionState.m_tHelmite.m_fInitTangentVector[1], m_tAttackState.m_tDirectionState.m_tHelmite.m_fTargetTangentVector[1],
            m_tAttackState.m_fAttackDuration);
        m_tAttackState.m_f3Center.z = HelmiteValue(m_fTime,
            m_tAttackState.m_tDirectionState.m_tHelmite.m_f3InitPos.z, m_tAttackState.m_tDirectionState.m_tHelmite.m_f3TargetPos.z,
            m_tAttackState.m_tDirectionState.m_tHelmite.m_fInitTangentVector[2], m_tAttackState.m_tDirectionState.m_tHelmite.m_fTargetTangentVector[2],
            m_tAttackState.m_fAttackDuration);
        break;
    case DirectionKind::FollowUp:
        m_tAttackState.m_f3Center = m_tAttackState.m_tDirectionState.m_tFollowUp.pTarget->AccessorPos();
        break;
    default:
        break;
    }

    m_tParam.m_f3Size = m_tAttackState.m_f3Size * 2.0f;
    m_tParam.m_f3Pos = m_tAttackState.m_f3Center;
    if (m_tAttackState.m_n2Split.x != 0 && m_tAttackState.m_n2Split.y != 0)
    {
        m_tParam.m_f2UVSize.x = 1.0f / (float)m_tAttackState.m_n2Split.x;
        m_tParam.m_f2UVSize.y = 1.0f / (float)m_tAttackState.m_n2Split.y;
        float fStep = (m_tAttackState.m_fAttackDuration) / float(m_tAttackState.m_n2Split.x * m_tAttackState.m_n2Split.y);
        if (m_fTime >= (fStep * (m_nStep + 1)) / (float)m_tAttackState.m_nSpeed) m_nStep++;
        //if (m_nStep >= m_tAttackState.m_n2Split.x * m_tAttackState.m_n2Split.x) m_nStep = 0;
        m_tParam.m_f2UVPos.x = (1.0f / (float)m_tAttackState.m_n2Split.x) * (m_nStep % m_tAttackState.m_n2Split.x);
        m_tParam.m_f2UVPos.y = (1.0f / (float)m_tAttackState.m_n2Split.y) * (m_nStep / m_tAttackState.m_n2Split.x);
    }

    CCollisionObb* pCollision = GetComponent<CCollisionObb>();
    if (pCollision)
    {
        pCollision->AccessorCenter(m_tAttackState.m_f3Center);
        pCollision->AccessorHalfSize(m_tAttackState.m_f3Size * 0.5f);
    }

    if (m_fTime >= m_tAttackState.m_fAttackDuration)
        Destroy();

    m_fTime += fDeltaTime;
    CGameObject::Update();
}

void CAttackObject::Draw()
{
    if (m_tAttackState.m_sTexKey != "") GetComponent<CBillboardRenderer>()->SetKey(m_tAttackState.m_sTexKey);
    CGameObject::Draw();
}

void CAttackObject::OnColliderHit(CCollisionBase* other, std::string thisTag)
{

}
