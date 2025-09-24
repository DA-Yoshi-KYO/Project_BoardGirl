#pragma once

// インクルード部
#include "GameObject.h"
#include "EnemyAttack.h"

// 前方宣言
class CPlayer;
class CCollisionObb;
class CHPBar;

// 敵のコリジョン識別用インデックス
enum class eEnemyCollision
{
    Body,
    Search,
    Attack,

    Max
};

// 敵のステートパターン
enum class eEnemyStatePattern
{
    Near,
    Middle,
    Far,

    Max
};

/// <summary>
/// 敵をまとめるベースクラス
/// </summary>
class CEnemyBase : public CGameObject
{
public:
    CEnemyBase();
    virtual ~CEnemyBase();
    void Init() override;
    void Update() override;
    void OnColliderHit(CCollisionBase* other,std::string thisTag = "None") override;
    void Destroy() override;
    int Inspecter(bool isEnd = true) override;

    /// <summary>
    /// 攻撃アクションを実行
    /// </summary>
    virtual void Attack();

    /// <summary>
    /// 派生先で作成された攻撃用ステータスを攻撃用オブジェクトに渡す
    /// </summary>
    /// <param name="inState">
    /// 攻撃用ステータス構造体
    /// </param>
    void Attack(AttackState inState);

    /// <summary>
    /// ダメージ処理
    /// </summary>
    /// <param name="inDamage">
    /// 与えるダメージ
    /// </param>
    void Damage(int inDamage);

    /// <summary>
    /// 無敵状態を設定
    /// </summary>
    /// <param name="isInvincibly">
    /// true:無敵状態 false:無敵状態解除
    /// </param>
    void SetInvincibly(bool isInvincibly);

    /// <summary>
    /// 敵が無敵状態かどうかを取得
    /// </summary>
    /// <returns>
    /// true:無敵状態 false:無敵ではない
    /// </returns>
    bool GetInvincibly() { return m_tEnemyStatus.m_bDamage; }
    eEnemyStatePattern GetPattern(DirectX::XMFLOAT3 inAttackHarfSize);

private:
    DirectX::XMFLOAT3 m_f3Velocity; // 速度

protected:
    // 敵のステータス
    struct EnemyStatus
    {
        int m_nHP;      // HP
        int m_nAttack;  // 攻撃力
        float m_fSpeed; // スピード
        int m_nScore;   // 討伐時のスコア
        bool m_bMove;   // 動けるかどうか
        bool m_bDamage; // 無敵状態か
    }m_tEnemyStatus;

    float m_fAttackTime;    // 攻撃インターバル
    float m_fInvincibleTime;  // 無敵時間
    CCollisionObb* m_pCollision[(int)(eEnemyCollision::Max)];    // 使用するコリジョンのリスト
    CHPBar* m_pHPBar;   // HPバー
    CPlayer* m_pPlayer; // プレイヤー

};

