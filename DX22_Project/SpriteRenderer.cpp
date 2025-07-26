#include "SpriteRenderer.h"
#include "Sprite.h"
#include "DirectX.h"

std::map<const char*, Texture*> CSpriteRenderer::m_pTextureMap = {};

CSpriteRenderer::~CSpriteRenderer()
{

}

void CSpriteRenderer::Init()
{
    m_pTextureMap = {};
}

void CSpriteRenderer::Uninit()
{
    for (auto itr : m_pTextureMap)
    {
        delete itr.second;
        itr.second = nullptr;
    }
    m_pTextureMap.clear();
}

void CSpriteRenderer::Load(const char* inPath, const char* inKey)
{
    for (auto itr : m_pTextureMap)
    {
        if (strcmp(itr.first, inKey) == 0)
        {
            m_chKey = itr.first;
            return;
        }
    }

    Texture* pTexture = new Texture();
    if (FAILED(pTexture->Create(inPath))) assert(pTexture);
    m_pTextureMap.emplace(inKey, pTexture);
    m_chKey = inKey;
}

void CSpriteRenderer::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, nullptr);
	Sprite::SetParam(m_tParam,SpriteKind::Screen);
	Sprite::SetTexture(m_pTextureMap.find(m_chKey)->second);
	Sprite::Draw();
}
