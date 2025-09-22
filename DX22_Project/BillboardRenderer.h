#pragma once

#include "RendererComponent.h"

class CBillboardRenderer : public CRendererComponent
{
public: 
	using CRendererComponent::CRendererComponent;
	~CBillboardRenderer();
	void Draw() override;
};

