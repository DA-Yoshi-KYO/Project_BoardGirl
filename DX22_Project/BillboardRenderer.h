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
    static void Unload();
private:
    static std::map<std::string, Texture*> m_pTextureMap;
    std::string m_chKey;
};

