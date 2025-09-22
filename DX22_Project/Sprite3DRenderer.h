#pragma once

#include "RendererComponent.h"

class CSprite3DRenderer : public CRendererComponent
{
public:
	using CRendererComponent::CRendererComponent;
    ~CSprite3DRenderer();
    void Init() override;
	void Draw() override;
    void SetDepth(bool isDepth) { m_bIsDepth = isDepth; }

private:
    bool m_bIsDepth = true;
};

