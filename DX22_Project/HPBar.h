#pragma once

#include "BillboardRenderer.h"
#include "GameObject.h"

class CHPBar : public CGameObject 
{
public:
    virtual ~CHPBar();
    void Init() override;
    void Update() override;
    void Draw() override;

    void SetRenderState(DirectX::XMFLOAT3 inSize, DirectX::XMFLOAT4 inFlontColor);
    void SetCurrentHP(int inCurrentHP);
    void SetMaxHP(int inMaxHP);
    void SetParentID(ObjectID inParent);

    virtual int Inspecter(bool isEnd = true);

private:
    enum class TextureKind
    {
        Back,
        Flont,

        Max
    };
    CBillboardRenderer* m_pHPBar[(int)TextureKind::Max];
    RendererParam m_tRendererParam[(int)TextureKind::Max];
    ObjectID m_tParentID;
    
    struct BarParam
    {
        int m_nMaxHP;
        int m_nCurrentHP;
        float m_fMaxSize;
    }m_tValue;
};
