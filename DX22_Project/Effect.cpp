#include "Effect.h"
#include "BillboardRenderer.h"

CEffect::~CEffect()
{
}

void CEffect::Init()
{
    m_n2Split = {};
    m_fTime = 0.0f;
    m_fStepTime = 0.0f;
    m_nStep = 0;
}

void CEffect::Update()
{
    if (m_fTime >= m_fStepTime)
    {
        if (m_nStep >= m_n2Split.x * m_n2Split.y)
        {
            Destroy();
        }
        m_nStep++;
        m_fTime = 0.0f;
    }

    m_tParam.m_f2UVPos.x = (m_nStep % m_n2Split.x) * (1.0f / (float)m_n2Split.x);
    m_tParam.m_f2UVPos.y = (m_nStep / m_n2Split.x) * (1.0f / (float)m_n2Split.y);

    m_fTime += fDeltaTime;

    CGameObject::Update();
}

void CEffect::SetParam(eEffectKind inKind, float inTick)
{
    CBillboardRenderer* pRenderer = AddComponent<CBillboardRenderer>();

    switch (inKind)
    {
    case eEffectKind::PlayerSwordAttackHit:
        m_n2Split = DirectX::XMINT2(9, 1);
        pRenderer->SetKey("SwordAttackHit");
        break;
    case eEffectKind::EnemyAttackHit:
        m_n2Split = DirectX::XMINT2(5, 5);
        break;
    default: break;
    }
    m_tParam.m_f2UVSize = DirectX::XMFLOAT2(1.0f / (float)m_n2Split.x, 1.0f / (float)m_n2Split.y);

    m_fStepTime = inTick;
}
