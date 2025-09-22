// インクルード部
#include "Sprite3DRenderer.h"
#include "Sprite.h"
#include "DirectX.h"

CSprite3DRenderer::~CSprite3DRenderer()
{

}

void CSprite3DRenderer::Init()
{
    // デフォルトでは深度バッファを有効にする
    m_bIsDepth = true;
}

void CSprite3DRenderer::Draw()
{
    // キーが設定されていない時は描画しない
    if (m_sKey.empty()) return;

    // フラグによって深度バッファを使用するか決める
    RenderTarget* pRTV = GetDefaultRTV();
    DepthStencil* pDSV = GetDefaultDSV();
    if (m_bIsDepth) SetRenderTargets(1, &pRTV, pDSV);
    else SetRenderTargets(1, &pRTV, nullptr);

    // カリングのセット
    SetCullingMode(m_tParam.m_eCulling);

    // 描画用パラメータのセット
    Sprite::SetParam(m_tParam, SpriteKind::World);

    // テクスチャのセット
    Sprite::SetTexture(std::get<Texture*>(m_RendererObjectMap.find(m_sKey.c_str())->second.m_Data));

    // 描画
    Sprite::Draw();
}
