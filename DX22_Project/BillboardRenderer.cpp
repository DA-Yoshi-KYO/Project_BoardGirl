#include "BillboardRenderer.h"
#include "Sprite.h"
#include "DirectX.h"

CBillboardRenderer::~CBillboardRenderer()
{

}

void CBillboardRenderer::Init()
{
	m_pTexture = nullptr;
}

void CBillboardRenderer::Load(const char* inPath)
{
	m_pTexture = std::make_shared<Texture>();
	if (FAILED(m_pTexture->Create(inPath))) assert(m_pTexture);
}

void CBillboardRenderer::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, pDSV);
	Sprite::SetParam(m_tParam, SpriteKind::Billboard);
	Sprite::SetTexture(m_pTexture.get());
	Sprite::Draw();
}
