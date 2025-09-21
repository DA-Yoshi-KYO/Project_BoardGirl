#pragma once

// インクルード部
#include "Camera.h"

/// <summary>
/// デバッグ用カメラを扱うCCamera派生クラス
/// </summary>
class CCameraDebug : public CCamera
{
public:
	CCameraDebug();
	~CCameraDebug();
	void Update() final;

private:
	float m_radXZ;  // 横回転
	float m_radY;   // 縦回転
	float m_radius; // カメラの距離
};
