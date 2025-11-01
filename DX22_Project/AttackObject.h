#pragma once

// インクルード部
#include "GameObject.h"

// 生成後の動き
enum class DirectionKind
{
    Stay,       // 生成された位置で留まる
    Toward,     // Directionの方向に移動
    Helmite,    // 目的地にエルミート曲線を使用し移動
    FollowUp    // GameObjectの座標に追従
};

// 動きのパラメータ
struct DirectionState
{
    DirectionKind m_eKind;  // 生成後の動き

    // 使用する動きは一種類なので共用体にする
    union
    {
        // 停止
        struct StayValue
        {
            DirectX::XMFLOAT3 m_f3StayPos;      // 生成位置
        }m_tStayPos;

        // 直線移動
        struct TowardValue
        {
            DirectX::XMFLOAT3 m_f3Direction;    // 移動方向
        }m_tToward;

        // エルミート
        struct HelmiteValue
        {
        public:
            DirectX::XMFLOAT3 m_f3InitPos;      // 初期位置
            DirectX::XMFLOAT3 m_f3TargetPos;    // 目標位置
            DirectX::XMFLOAT3 m_fInitTangentVector;      // 初期位置接線ベクトル
            DirectX::XMFLOAT3 m_fTargetTangentVector;    // 目標位置接線ベクトル
        }m_tHelmite;

        // 追従
        struct FollowUpValue
        {
            CGameObject* pTarget;               // 追従先のオブジェクト
        }m_tFollowUp;
    };
};

struct AttackState
{
    DirectX::XMFLOAT3 m_f3Center;       // 中心座標
    DirectX::XMFLOAT3 m_f3Size;         // サイズ
    float m_fAttackDuration;            // 攻撃持続時間
    int m_nDamage;                      // ダメージ
    std::string m_sTexKey;              // 使用するテクスチャのキー
    DirectX::XMINT2 m_n2Split;          // 使用するテクスチャの分割数
    int m_nSpeed;                       // テクスチャアニメーションの再生速度係数
    DirectionState m_tDirectionState;   // 生成後の動きのパラメータ
};

/// <summary>
/// 攻撃用オブジェクトを生成するベースクラス
/// </summary>
class CAttackObject : public CGameObject
{
public:
    CAttackObject();
    virtual ~CAttackObject();
    void Init() override;
    void Update() override;
    void Draw() override;
    void OnColliderHit(CCollisionBase* other, std::string thisTag = "None") override;

    /// <summary>
    /// 攻撃用オブジェクトのステータスをセット
    /// </summary>
    /// <param name="inState">
    /// ステータスの構造体
    /// </param>
    void SetAttackState(AttackState inState) { m_tAttackState = inState; }

private:
    float m_fTime;  // タイマー
    int m_nStep;    // テクスチャアニメーション進行度

protected:
    AttackState m_tAttackState; // 攻撃用オブジェクトのステータス

};
