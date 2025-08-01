#include "BillboardRenderer.h"
#include "Sprite.h"
#include "DirectX.h"

CBillboardRenderer::~CBillboardRenderer()
{

}

void CBillboardRenderer::Init()
{

}

void CBillboardRenderer::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, nullptr);
	Sprite::SetParam(m_tParam, SpriteKind::Billboard);
	Sprite::SetTexture(m_pTextureMap.find(m_sKey.c_str())->second);
	Sprite::Draw();
}
