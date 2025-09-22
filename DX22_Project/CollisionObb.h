#pragma once

// インクルード部
#include "CollisionBase.h"

// OBB用パラメータ
struct ObbInfo
{
    DirectX::XMFLOAT3 m_f3Center;     // 中心座標
    DirectX::XMFLOAT3 m_f3HalfSize;   // ハーフサイズ
};

class CCollisionObb : public CCollisionBase
{
public:
	using CCollisionBase::CCollisionBase;
	void Draw() override;

    /// <summary>
    /// 衝突が起きたかどうかを取得
    /// </summary>
    /// <param name="other">
    /// 衝突先
    /// </param>
    /// <returns>
    /// true:衝突 false:非衝突
    /// </returns>
	bool IsHit(CCollisionBase* other) override;

    /// <summary>
    /// コリジョン情報の中心座標を取得
    /// </summary>
    /// <returns>
    /// (DirectX::XMFLOAT3)コリジョンの中心座標
    /// </returns>
    DirectX::XMFLOAT3 AccessorCenter() { return m_tCollisionInfo.m_f3Center; }

    /// <summary>
    /// コリジョンの中心座標をセット
    /// </summary>
    /// <param name="center">
    /// コリジョンの中心座標
    /// </param>
    void AccessorCenter(const DirectX::XMFLOAT3& center) { m_tCollisionInfo.m_f3Center = center; }

    /// <summary>
    /// コリジョン情報のハーフサイズ
    /// </summary>
    /// <returns>
    /// (DirectX::XMFLOAT3)コリジョンのハーフサイズ
    /// </returns>
    DirectX::XMFLOAT3 AccessorHalfSize() { return m_tCollisionInfo.m_f3HalfSize; }

    /// <summary>
    /// コリジョンのハーフサイズをセット
    /// </summary>
    /// <param name="halfSize">
    /// コリジョンのハーフサイズ
    /// </param>
    void AccessorHalfSize(const DirectX::XMFLOAT3& halfSize) { m_tCollisionInfo.m_f3HalfSize = halfSize; }

    /// <summary>
    /// OBB用パラメータの取得
    /// </summary>
    /// <returns>
    /// OBB用パラメータをまとめた構造体
    /// </returns>
    ObbInfo AcessorCollisionInfo() const { return m_tCollisionInfo; }

    /// <summary>
    /// OBB用パラメータのセット
    /// </summary>
    /// <param name="info">
    /// OBB用パラメータ
    /// </param>
    void AccessorCollisionInfo(const ObbInfo& info)
    {
        m_tCollisionInfo.m_f3Center = info.m_f3Center;
        m_tCollisionInfo.m_f3HalfSize = info.m_f3HalfSize;
    }

private:
    ObbInfo m_tCollisionInfo;   // OBB用パラメータ

};
