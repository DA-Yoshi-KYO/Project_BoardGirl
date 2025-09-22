#include "BillboardRenderer.h"
#include "Sprite.h"
#include "DirectX.h"

CBillboardRenderer::~CBillboardRenderer()
{

}

void CBillboardRenderer::Draw()
{
    if (m_sKey.empty()) return;
	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, nullptr);
    SetCullingMode(m_tParam.m_eCulling);
	Sprite::SetParam(m_tParam, SpriteKind::Billboard);
	Sprite::SetTexture(std::get<Texture*>(m_RendererObjectMap.find(m_sKey.c_str())->second.m_Data));
	Sprite::Draw();
}
