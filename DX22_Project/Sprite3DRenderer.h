#pragma once

#include "RendererComponent.h"
#include "Texture.h"

class CSprite3DRenderer : public CRendererComponent
{
public:
	using CRendererComponent::CRendererComponent;
	~CSprite3DRenderer();
	void Init() override;
	void Load(const char* inPath);
	void Draw() override;

private:
	std::shared_ptr<Texture> m_pTexture;

};

