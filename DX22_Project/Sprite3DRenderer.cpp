#include "Sprite3DRenderer.h"
#include "Sprite.h"
#include "DirectX.h"

CSprite3DRenderer::~CSprite3DRenderer()
{

}

void CSprite3DRenderer::Init()
{

}

void CSprite3DRenderer::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();

    if (m_bIsDepth) SetRenderTargets(1, &pRTV, pDSV);
    else SetRenderTargets(1, &pRTV, nullptr);
    SetCullingMode(m_tParam.m_eCulling);

	Sprite::SetParam(m_tParam, SpriteKind::World);
	Sprite::SetTexture(std::get<Texture*>(m_RendererObjectMap.find(m_sKey.c_str())->second.m_Data));
	Sprite::Draw();
}
