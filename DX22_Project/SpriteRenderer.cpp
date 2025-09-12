#include "SpriteRenderer.h"
#include "Sprite.h"
#include "DirectX.h"

CSpriteRenderer::~CSpriteRenderer()
{

}

void CSpriteRenderer::Init()
{

}

void CSpriteRenderer::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, nullptr);
    SetCullingMode(m_tParam.m_eCulling);
	Sprite::SetParam(m_tParam,SpriteKind::Screen);
	Sprite::SetTexture(m_pTextureMap.find(m_sKey.c_str())->second);
	Sprite::Draw();
}
