#pragma once

// インクルード部
#include "RendererComponent.h"

/// <summary>
/// 2Dスプライト描画を扱うコンポーネントクラス
/// </summary>
class CSpriteRenderer : public CRendererComponent
{
public:
	using CRendererComponent::CRendererComponent;
	virtual ~CSpriteRenderer();
	void Draw() override;
};

