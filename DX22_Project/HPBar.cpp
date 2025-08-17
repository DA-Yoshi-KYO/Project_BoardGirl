#include "HPBar.h"
#include "Camera.h"
#include "Oparation.h"
#include "Main.h"
#include "Player.h"

CHPBar::~CHPBar()
{
}

void CHPBar::Init()
{
    m_tValue.m_nMaxHP = m_tValue.m_nCurrentHP = 0;

    for (int i = 0; i < (int)TextureKind::Max; i++)
    {
        m_pHPBar[i] = AddComponent<CBillboardRenderer>();
        m_pHPBar[i]->SetKey("HPBar");
        m_tRendererParam[i].m_f3Pos = {};
        m_tRendererParam[i].m_f3Size = { 2.0f,1.0f,0.0f };
        m_tRendererParam[i].m_f3Rotate = {};
        m_tRendererParam[i].m_f2UVPos = {};
        m_tRendererParam[i].m_f2UVSize = {1.0f,1.0f};

        switch (i)
        {
        case (int)TextureKind::Back:
            m_tRendererParam[i].m_f4Color = { 0.0f,0.0f,0.0f,1.0f };
            break;
        case (int)TextureKind::Flont:
            m_tRendererParam[i].m_f4Color = { 0.0f,1.0f,0.0f,1.0f };
            break;
        default:
            break;
        }
    }
}

void CHPBar::Draw()
{
    float fStep = (float)m_tValue.m_nCurrentHP / (float)m_tValue.m_nMaxHP;
    m_tRendererParam[(int)TextureKind::Flont].m_f3Size.x = m_tValue.m_fMaxSize * fStep;
    float fOffSetRatio = 1.0f - fStep;
    DirectX::XMFLOAT3 f3MovePos = GetScene()->GetGameObject<CPlayer>()->GetRight();
    f3MovePos.x *= m_tValue.m_fMaxSize * 0.5f;
    DirectX::XMFLOAT3 f3OffSetRight = f3MovePos * fOffSetRatio;
    
    m_tRendererParam[(int)TextureKind::Flont].m_f3Pos -= f3OffSetRight;

    for (int i = 0; i < (int)TextureKind::Max; i++)
    {
        m_pHPBar[i]->SetRendererParam(m_tRendererParam[i]);
        m_pHPBar[i]->Draw();
    }
}

void CHPBar::SetCurrentHP(int inCurrentHP)
{
    m_tValue.m_nCurrentHP = inCurrentHP;
}

void CHPBar::SetMaxHP(int inMaxHP)
{
    m_tValue.m_nMaxHP = inMaxHP;
}

void CHPBar::SetParent(CGameObject* inParent)
{
    m_pParent = inParent;
}

void CHPBar::SetRenderState(DirectX::XMFLOAT3 inSize, DirectX::XMFLOAT4 inFlontColor)
{
    for (int i = 0; i < (int)TextureKind::Max; i++)
    {
        m_tRendererParam[i].m_f3Size = inSize;
    }
    m_tValue.m_fMaxSize = inSize.x;
    m_tRendererParam[(int)TextureKind::Flont].m_f4Color = inFlontColor;
}

void CHPBar::SetPos(DirectX::XMFLOAT3 inPos)
{
    for (int i = 0; i < (int)TextureKind::Max; i++)
    {
        m_tRendererParam[i].m_f3Pos = inPos;
    }
}
