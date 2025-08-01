#pragma once

#include "BillboardRenderer.h"
#include "GameObject.h"

class CHPBar : public CGameObject 
{
public:
    virtual ~CHPBar();
    void Init() override;
    void Draw() override;

    void SetPos(DirectX::XMFLOAT3 inPos);
    void SetRenderState(DirectX::XMFLOAT3 inSize, DirectX::XMFLOAT4 inFlontColor);
    void SetCurrentHP(int inCurrentHP);
    void SetMaxHP(int inMaxHP);
private:
    enum class TextureKind
    {
        Back,
        Flont,

        Max
    };
    CBillboardRenderer* m_pHPBar[(int)TextureKind::Max];
    RendererParam m_tRendererParam[(int)TextureKind::Max];

    struct BarParam
    {
        int m_nMaxHP;
        int m_nCurrentHP;
        float m_fMaxSize;
    }m_tValue;
};
