#pragma once

// インクルード部
#include "GameObject.h"

// 前方宣言
class CBillboardRenderer;

/// <summary>
/// HPバーを実装するクラス
/// </summary>
class CHPBar : public CGameObject 
{
public:
    virtual ~CHPBar();
    void Init() override;
    void Update() override;
    void Draw() override;
    int Inspecter(bool isEnd = true) override;

    /// <summary>
    /// HPバーの見た目をセット
    /// </summary>
    /// <param name="inSize">
    /// サイズ
    /// </param>
    /// <param name="inFlontColor">
    /// バーのFill部分の色
    /// </param>
    void SetRenderState(DirectX::XMFLOAT3 inSize, DirectX::XMFLOAT4 inFlontColor);

    /// <summary>
    /// 現在のHPのセット
    /// </summary>
    /// <param name="inCurrentHP">
    /// HPの値
    /// </param>
    void SetCurrentHP(int inCurrentHP);

    /// <summary>
    /// 最大HPのセット
    /// </summary>
    /// <param name="inMaxHP">
    /// 最大の
    /// </param>
    void SetMaxHP(int inMaxHP);

    /// <summary>
    /// HPバーを追加する親オブジェクトをセット
    /// </summary>
    /// <param name="inParent">
    /// 親オブジェクトの識別用ID
    /// </param>
    void SetParentID(ObjectID inParent);

private:
    // テクスチャの種類
    enum class TextureKind
    {
        Back,   // 背景部分
        Flont,  // Fill部分

        Max
    };

    // HPバー用パラメータ
    struct BarParam
    {
        int m_nMaxHP;       // 最大HP
        int m_nCurrentHP;   // 現在HP
        float m_fMaxSize;   // HPバーの最大横サイズ
    }m_tValue;

    CBillboardRenderer* m_pHPBar[(int)TextureKind::Max];    // HPバーの描画コンポーネント
    RendererParam m_tRendererParam[(int)TextureKind::Max];  // HPバーの描画パラメータ
    ObjectID m_tParentID;   // 親オブジェクトのID
    
};
