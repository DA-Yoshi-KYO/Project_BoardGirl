#pragma once

#include "RendererComponent.h"
#include "Texture.h"

class CSpriteRenderer : public CRendererComponent
{
public:
	using CRendererComponent::CRendererComponent;
	virtual ~CSpriteRenderer();
	void Init() override;
    void Uninit() override;
	void Load(const char* inPath, const char* inKey);
	void Draw() override;

private:
	static std::map<const char*,Texture*> m_pTextureMap;
    const char* m_chKey;
};

