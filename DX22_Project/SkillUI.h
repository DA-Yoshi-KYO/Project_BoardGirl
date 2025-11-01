#pragma once

#include "GameObject.h"
#include "SpriteRenderer.h"

class CSkillUI : public CGameObject
{
public:
    ~CSkillUI();
    void Init() override;
    void Update() override;
    void Draw() override;
    int Inspecter(bool isEnd = true) override;

    void SetCurrentValue(float inCurrentValue) { m_fCurrentValue = inCurrentValue; m_fCurrentValue = std::min(inCurrentValue, m_fMaxValue); };
    void SetMaxValue(float inMaxValue) { m_fMaxValue = inMaxValue; };
    void SetTransform(DirectX::XMFLOAT3 inPos, DirectX::XMFLOAT3 inSize);

private:
    enum eTexture
    {
        Back,
        Front,
        Frame,

        Max
    };

    CSpriteRenderer* m_pSprite[eTexture::Max];
    RendererParam m_tSpriteParam[eTexture::Max];
    DirectX::XMFLOAT3 m_f3FillSize;

    float m_fCurrentValue;
    float m_fMaxValue;
    float fTime;
};
