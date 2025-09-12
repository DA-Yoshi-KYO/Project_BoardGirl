#pragma once

#include "GameObject.h"
#include "Sprite3DRenderer.h"

class CSelectArrow : public CGameObject
{
public:
    virtual ~CSelectArrow();
    void Init() override;
    void Update() override;
    void Draw() override;
    int Inspecter(bool isEnd = true) override;
private:
    CSprite3DRenderer* m_pArrowSprite[2];
    DirectX::XMFLOAT3 m_f3ArrowPos[2];
    DirectX::XMFLOAT3 m_f3ArrowSize[2];
    DirectX::XMFLOAT3 m_f3ArrowRotate[2];
};
