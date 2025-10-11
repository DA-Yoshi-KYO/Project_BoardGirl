#pragma once

// インクルード部
#include "CollisionObb.h"
#include "Defines.h"
#include "EnemyBase.h"
#include "PlayerAttack.h"
#include "SkillUI.h"

// 前方宣言
class CPlayer;

// ジョブの種類
enum class JobKind
{
    Soldier = 0,
    Wizard,
    Fighter,

    Max
};

// プレイヤーのジョブごとのステータス
struct PlayerStatus
{
    int m_nHP;      // HP
    int m_nAttack;  // 攻撃力
    float m_fSkillTime[(int)eSkill::Max];       // スキルのクールタイム用タイマー
    float m_fSkillCooltime[(int)eSkill::Max];   // スキルのクールタイム
};

/// <summary>
/// プレイヤーのジョブをまとめるベースクラス
/// </summary>
class CJob
{
public:
    CJob();
    ~CJob();
    void Init();
    virtual void Update();

    /// <summary>
    /// スキルの発動
    /// </summary>
    /// <param name="inKind">
    /// 発動するスキルの種類
    /// </param>
    /// <returns>
    /// true:スキル発動 false:スキル発動失敗
    /// </returns>
    virtual bool Skill(eSkill inKind);

    /// <summary>
    /// 通常攻撃を発動
    /// </summary>
    virtual void NormalAttack() = 0;

    /// <summary>
    /// Qスキルを発動
    /// </summary>
    virtual void QSkill() = 0;

    /// <summary>
    /// Eスキルを発動
    /// </summary>
    virtual void ESkill() = 0;

    /// <summary>
    /// Rスキルを発動
    /// </summary>
    virtual void RSkill() = 0;
    
    void Attack(AttackState inState);
    
    void Damage(int inDamage);
    int GetHP() { return m_tStatus.m_nHP; };
    PlayerStatus GetStatus() { return m_tStatus; }

private:
    CSkillUI* m_pSkillUI[3];
    
protected:
    bool isEnd; // ゲーム終了フラグ
    PlayerStatus m_tStatus;
};
