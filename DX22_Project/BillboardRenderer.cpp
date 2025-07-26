#include "BillboardRenderer.h"
#include "Sprite.h"
#include "DirectX.h"

std::map<const char*, Texture*> CBillboardRenderer::m_pTextureMap = {};

CBillboardRenderer::~CBillboardRenderer()
{

}

void CBillboardRenderer::Init()
{
    m_pTextureMap = {};
}

void CBillboardRenderer::Uninit()
{
    for (auto itr : m_pTextureMap)
    {
        delete itr.second;
        itr.second = nullptr;
    }
    m_pTextureMap.clear();
}

void CBillboardRenderer::Load(const char* inPath, const char* inKey)
{
    for (auto itr : m_pTextureMap)
    {
        if (strcmp(itr.first, inKey) == 0)
        {
            m_chKey = itr.first;
            itr.second = m_pTextureMap.find(m_chKey)->second;
            return;
        }
    }

    Texture* pTexture = new Texture();
    if (FAILED(pTexture->Create(inPath))) assert(pTexture);
    m_pTextureMap.emplace(inKey, pTexture);
    m_chKey = inKey;
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
