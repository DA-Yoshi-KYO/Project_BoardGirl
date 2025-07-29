#pragma once

#include "RendererComponent.h"

class CSpriteRenderer : public CRendererComponent
{
public:
	using CRendererComponent::CRendererComponent;
	virtual ~CSpriteRenderer();
	void Init() override;
	void Draw() override;
};

