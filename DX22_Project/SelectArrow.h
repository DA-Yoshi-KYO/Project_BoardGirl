#pragma once

// インクルード部
#include "GameObject.h"

// 前方宣言
class CSprite3DRenderer;

/// <summary>
/// ジョブ選択画面の矢印UI
/// </summary>
class CSelectArrow : public CGameObject
{
public:
    CSelectArrow();
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
