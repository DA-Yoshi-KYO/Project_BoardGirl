#include "Sprite3DRenderer.h"
#include "Sprite.h"
#include "DirectX.h"

CSprite3DRenderer::~CSprite3DRenderer()
{

}

void CSprite3DRenderer::Init()
{
	m_pTexture = nullptr;
}

void CSprite3DRenderer::Load(const char* inPath)
{
	m_pTexture = std::make_shared<Texture>();
	if (FAILED(m_pTexture->Create(inPath))) assert(m_pTexture);
}

void CSprite3DRenderer::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, pDSV);
	Sprite::SetParam(m_tParam, SpriteKind::World);
	Sprite::SetTexture(m_pTexture.get());
	Sprite::Draw();
}
