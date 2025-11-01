// インクルード部
#include "SelectBackGround.h"

CSelectBackGround::~CSelectBackGround()
{
}

void CSelectBackGround::Init()
{
    // コンポーネントの追加
    // 描画に使用するテクスチャのキーを設定
    AddComponent<CSprite3DRenderer>()->SetKey("SelectBG");

    // 描画用パラメータの設定
    m_tParam.m_f3Size = DirectX::XMFLOAT3(25.0f, 15.0f, 0.0f);
}
