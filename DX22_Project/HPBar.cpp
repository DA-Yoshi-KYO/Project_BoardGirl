#include "HPBar.h"
#include "Camera.h"
#include "Oparation.h"

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
    m_tRendererParam[(int)TextureKind::Flont].m_f3Size.x = m_tValue.m_fMaxSize * ((float)m_tValue.m_nCurrentHP / (float)m_tValue.m_nMaxHP);

    DirectX::XMFLOAT4X4 view = CCamera::GetInstance(CCamera::GetCameraKind())->GetViewMatrix(false);
    DirectX::XMMATRIX mView = DirectX::XMLoadFloat4x4(&view);
    DirectX::XMVECTOR vecCameraRight = DirectX::XMVector3Normalize(mView.r[0]);
    float fOffSet = (m_tValue.m_fMaxSize - m_tRendererParam[(int)TextureKind::Flont].m_f3Size.x) / 2.0f;

    // カメラ右方向にオフセットをずらす
    DirectX::XMVECTOR vecPos = DirectX::XMLoadFloat3(&m_tRendererParam[(int)TextureKind::Flont].m_f3Pos);
    vecPos -= vecCameraRight * fOffSet;
    DirectX::XMStoreFloat3(&m_tRendererParam[(int)TextureKind::Flont].m_f3Pos, vecPos);

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
