#pragma once

// インクルード部
#include "GameObject.h"
#include "Job.h"

// 前方宣言
class CHPBar;
class CCollisionObb;

/// <summary>
/// プレイヤーを扱うクラス
/// </summary>
class CPlayer: public CGameObject
{
public:
    CPlayer();
	void Init() override;
	void Update() override;
    void OnColliderHit(CCollisionBase* other, std::string thisTag = "None") override;
    int Inspecter(bool isEnd = true) override;

    /// <summary>
    /// ダメージ処理
    /// </summary>
    /// <param name="inDamage">
    /// 与えるダメージ
    /// </param>
    void Damage(int inDamage);

private:
    bool m_bJump;   // ジャンプ中かどうか
    bool m_bDamage; // 無敵状態かどうか
	DirectX::XMFLOAT3 m_f3Velocity; // 移動量
    JobKind m_eJobKind; // 自身のジョブの種類
    std::unique_ptr<CJob> m_pJob;   // 自身のジョブを扱うクラスポインタ
    CCollisionObb* m_pCollision;    // 自身の当たり判定
    CHPBar* m_pHPBar;   // HPバー

private:
    /// <summary>
    /// プレイヤーの移動を行う内部関数
    /// </summary>
    void PlayerMove();

    /// <summary>
    /// プレイヤーのスキル発動を行う内部関数
    /// </summary>
    void PlayerSkill();

};
