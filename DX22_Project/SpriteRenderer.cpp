#include "SpriteRenderer.h"
#include "Sprite.h"
#include "DirectX.h"

CSpriteRenderer::~CSpriteRenderer()
{
}

void CSpriteRenderer::Init()
{
	m_pTexture = nullptr;
}

void CSpriteRenderer::Load(const char* inPath)
{
	m_pTexture = std::make_shared<Texture>();
	if (FAILED(m_pTexture->Create(inPath))) assert(m_pTexture);
}

void CSpriteRenderer::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, nullptr);
	Sprite::SetParam(m_tParam,SpriteKind::Screen);
	Sprite::SetTexture(m_pTexture.get());
	Sprite::Draw();
}
