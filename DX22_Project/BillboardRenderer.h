#pragma once

// インクルード部
#include "RendererComponent.h"

/// <summary>
/// ビルボード描画を扱うコンポーネントクラス
/// </summary>
class CBillboardRenderer : public CRendererComponent
{
public: 
	using CRendererComponent::CRendererComponent;
	~CBillboardRenderer();
	void Draw() override;
};

