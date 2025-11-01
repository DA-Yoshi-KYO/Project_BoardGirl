#pragma once

// インクルード部
#include "GameObject.h"
#include "Sprite3DRenderer.h"

/// <summary>
/// ジョブ選択画面の背景
/// </summary>
class CSelectBackGround : public CGameObject
{
public:
    virtual ~CSelectBackGround ();
    void Init() override;

};
