#pragma once

#include "RendererComponent.h"
#include "Texture.h"

class CSpriteRenderer : public CRendererComponent
{
public:
	using CRendererComponent::CRendererComponent;
	~CSpriteRenderer();
	void Init() override;
	void Load(const char* inPath);
	void Draw() override;

private:
	std::shared_ptr<Texture> m_pTexture;

};

