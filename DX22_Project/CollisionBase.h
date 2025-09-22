#pragma once

// インクルード部
#include "Component.h" 

/// <summary>
/// 衝突判定をまとめるベースクラス
/// </summary>
class CCollisionBase : public CComponent
{
public:
    using CComponent::CComponent;
    virtual ~CCollisionBase();

    /// <summary>
    /// 衝突が起きたかどうかを取得
    /// </summary>
    /// <param name="other">
    /// 衝突先
    /// </param>
    /// <returns>
    /// true:衝突 false:非衝突
    /// </returns>
    virtual bool IsHit(CCollisionBase* other);

    /// <summary>
    /// 衝突識別用タグの指定
    /// </summary>
    /// <param name="inTag">
    /// 識別用タグ
    /// </param>
    void AccessorTag(const std::string& inTag) { m_sTag = inTag; }

    /// <summary>
    /// 衝突識別用タグの取得
    /// </summary>
    /// <param name="inTag">
    /// 識別用タグ
    /// </param>
    const std::string AccessorTag() { return m_sTag; }

    /// <summary>
    /// 衝突判定を有効にするか設定
    /// </summary>
    /// <param name="inActive">
    /// true:有効 false:無効
    /// </param>
    void AccessorActive(const bool inActive) { m_bActive = inActive; }

    /// <summary>
    /// 衝突判定が有効かどうか取得
    /// </summary>
    /// <returns>
    /// true:有効 false:無効
    /// </returns>
    const bool AccessorActive() const { return m_bActive; }

protected:
    bool m_bActive;     // 衝突判定が有効かどうか
    std::string m_sTag; // 衝突判定識別用タグ

};
