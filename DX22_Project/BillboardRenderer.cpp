#include "BillboardRenderer.h"
#include "Sprite.h"
#include "DirectX.h"

std::map<std::string, Texture*> CBillboardRenderer::m_pTextureMap{};

CBillboardRenderer::~CBillboardRenderer()
{

}

void CBillboardRenderer::Init()
{

}

void CBillboardRenderer::Uninit()
{

}

void CBillboardRenderer::Load(const char* inPath, const char* inKey)
{
    std::string keyStr(inKey);

    auto itr = m_pTextureMap.find(keyStr);
    if (itr != m_pTextureMap.end())
    {
        m_chKey = itr->first;
        return;
    }

    Texture* tex = new Texture();
    if (FAILED(tex->Create(inPath))) {
        assert(false); // Create失敗
        delete tex;
        return;
    }

    m_pTextureMap.emplace(keyStr, tex);
    m_chKey = keyStr;
}

void CBillboardRenderer::Unload()
{
    for (auto& itr : m_pTextureMap)
    {
        delete itr.second;
        itr.second = nullptr;
    }
    m_pTextureMap.clear();
}

void CBillboardRenderer::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, pDSV);
	Sprite::SetParam(m_tParam, SpriteKind::Billboard);
	Sprite::SetTexture(m_pTextureMap.find(m_chKey)->second);
	Sprite::Draw();
}
