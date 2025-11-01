// インクルード部
#include "SkyBox.h"
#include "Main.h"
#include "Camera.h"

CSkyBox::~CSkyBox()
{

}

void CSkyBox::Init()
{
    // 
    // コンポーネントの追加
    CModelRenderer* pRenderer = AddComponent<CModelRenderer>();
    //  描画に使用するモデルのキーをセット
    pRenderer->SetKey("SkyBox");
    // 震度バッファを無効
    pRenderer->SetDepth(false);

    // 表明をカリングする(裏面を描画する)
    m_tParam.m_eCulling = D3D11_CULL_FRONT;
}

void CSkyBox::Update()
{
    // 座標の更新
    m_tParam.m_f3Pos = CCamera::GetInstance()->GetPos();

    CGameObject::Update();
}
