#pragma once

// インクルード部
#include "GameObject.h"
#include "ModelRenderer.h"

// フィールドモデルとの当たり判定情報
struct HitResult
{
    bool m_bHit;                    // レイがヒットしたか
    DirectX::XMFLOAT3 m_f3Position; // レイのヒットした位置
    DirectX::XMFLOAT3 m_f3Normal;   // 法線
    float m_fDistance;              // 原点からヒットした位置までの距離
};

/// <summary>
/// フィールドの描画を行うクラス
/// </summary>
class CField : public CGameObject
{
public:
    ~CField();
    void Init() override;

    /// <summary>
    /// レイとフィールドモデルとの当たり判定を取る
    /// </summary>
    /// <param name="rayOrigin">
    /// レイの原点
    /// </param>
    /// <param name="rayDir">
    /// レイを飛ばす方向
    /// </param>
    /// <returns>
    /// 当たり判定情報をまとめた構造体
    /// </returns>
    static HitResult RayIntersectsTriangle(const DirectX::XMFLOAT3& rayOrigin, const DirectX::XMFLOAT3& rayDir);

private:
    static std::vector<Model::Mesh> m_Mesh; // モデルのメッシュ情報
    static HitResult m_tResult; // 当たり判定情報

    /// <summary>
    /// レイと三角形の衝突判定を行う内部関数
    /// </summary>
    /// <param name="rayOrigin">
    /// レイの原点
    /// </param>
    /// <param name="rayDir">
    /// レイを飛ばす方向
    /// </param>
    /// <param name="v0">
    /// 三角形の頂点0
    /// </param>
    /// <param name="v1">
    /// 三角形の頂点1
    /// </param>
    /// <param name="v2">
    /// 三角形の頂点2
    /// </param>
    /// <param name="outT">
    /// 原点との距離を返す
    /// </param>
    /// <returns>
    /// true:衝突 false:非衝突
    /// </returns>
    static bool CheckHit(const DirectX::XMVECTOR& inRayOrigin, const DirectX::XMVECTOR& rayDir, const DirectX::XMFLOAT3& inVertex0, const DirectX::XMFLOAT3& inVertex1, const DirectX::XMFLOAT3& inVertex2, float& outDis);

};
