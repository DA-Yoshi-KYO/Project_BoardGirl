#pragma once

// インクルード部
#include "GameObject.h"
#include "Texture.h"

class CField : public CGameObject
{
public:
    ~CField();
    void Init() override;
    void Update() override;

    float GetGroundHeight(DirectX::XMFLOAT3 pos);
private:
    std::unique_ptr<Texture> m_pHeightMap;

};
