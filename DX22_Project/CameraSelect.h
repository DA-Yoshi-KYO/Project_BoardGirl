#pragma once

// インクルード部
#include "Camera.h"

/// <summary>
/// ジョブ選択画面用カメラを扱うCCamera派生クラス
/// </summary>
class CCameraSelect : public CCamera
{
public:
	virtual ~CCameraSelect();
	void Update() final;
};
