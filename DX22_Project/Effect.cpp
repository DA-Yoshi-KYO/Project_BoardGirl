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
    m_nPlayNum = 0;
}

void CEffect::Update()
{
    if (m_fTime >= m_fStepTime)
    {
        if (m_nStep >= m_n2Split.x * m_n2Split.y - 1)
        {
            m_nPlayNum--;
            if (m_nPlayNum == 0)Destroy();
            else m_nStep = 0;
        }
        else
        {
            m_nStep++;
            m_fTime = 0.0f;
        }
    }

    m_tParam.m_f2UVPos.x = (m_nStep % m_n2Split.x) * (1.0f / (float)m_n2Split.x);
    m_tParam.m_f2UVPos.y = (m_nStep / m_n2Split.x) * (1.0f / (float)m_n2Split.y);

    m_fTime += fDeltaTime;

    CGameObject::Update();
}

void CEffect::SetParam(eEffectKind inKind, float inTotalTime, UINT inPlayNum)
{
    CBillboardRenderer* pRenderer = AddComponent<CBillboardRenderer>();

    switch (inKind)
    {
    case eEffectKind::PlayerSwordNormalSkill:
        m_n2Split = DirectX::XMINT2(9, 1);
        pRenderer->SetKey("SwordNormalAttack");
        break;
    case eEffectKind::PlayerSwordQSkill:
        m_n2Split = DirectX::XMINT2(5, 3);
        pRenderer->SetKey("SwordQSkill");
        break;
    case eEffectKind::PlayerSwordESkill:
        m_n2Split = DirectX::XMINT2(5, 2);
        pRenderer->SetKey("SwordESkill");
        break;
    case eEffectKind::PlayerSwordRSkill:
        m_n2Split = DirectX::XMINT2(2, 12);
        pRenderer->SetKey("SwordRSkill");
        break;
    case eEffectKind::EnemyAttackHit:
        m_n2Split = DirectX::XMINT2(5, 5);
        break;
    default: break;
    }
    m_tParam.m_f2UVSize = DirectX::XMFLOAT2(1.0f / (float)m_n2Split.x, 1.0f / (float)m_n2Split.y);
    m_nPlayNum = inPlayNum;

    m_fStepTime = inTotalTime / float(m_n2Split.x * m_n2Split.y * m_nPlayNum);
}

int CEffect::GetTotalStep()
{
    return m_n2Split.x * m_n2Split.y;
}
