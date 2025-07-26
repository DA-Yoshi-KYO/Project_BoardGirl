#pragma once

#include "RendererComponent.h"
#include "Texture.h"

class CBillboardRenderer : public CRendererComponent
{
public: 
	using CRendererComponent::CRendererComponent;
	~CBillboardRenderer();
	void Init() override;
    void Uninit() override;
	void Draw() override;

    void Load(const char* inPath, const char* inKey);
private:
    static std::map<const char*, Texture*> m_pTextureMap;
    const char* m_chKey;
};

