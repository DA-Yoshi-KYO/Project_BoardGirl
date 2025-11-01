#pragma once

// インクルード部
#include "Camera.h"

/// <summary>
/// インゲーム用カメラを扱うCCamera派生クラス
/// </summary>
class CCameraPlayer : public CCamera
{
public:
	virtual ~CCameraPlayer();
	void Update() final;
};
