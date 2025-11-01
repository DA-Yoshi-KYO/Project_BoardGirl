// インクルード部
#include "Dragon.h"
#include "Oparation.h"
#include "Player.h"
#include "BillboardRenderer.h"
#include "CollisionObb.h"

CDragon::CDragon()
    : CEnemyBase()
{
    // ドラゴンのステータスを決定
    m_tEnemyStatus.m_nHP = 30;
    m_tEnemyStatus.m_nAttack = 20;
    m_tEnemyStatus.m_fSpeed = 0.05f;
    m_tEnemyStatus.m_nScore = 50;
    m_tEnemyStatus.m_bMove = false;
    m_tEnemyStatus.m_bDamage = false;

    // 描画用パラメータの設定
    m_tParam.m_f3Size = DirectX::XMFLOAT3(3.0f,3.0f,3.0f);
}

CDragon::~CDragon()
{

}

void CDragon::Init()
{
    // 敵共通の初期化処理
    CEnemyBase::Init();

    // 描画に使用するテクスチャのキーをセット
    AddComponent<CBillboardRenderer>()->SetKey("Dragon");

    // コリジョンのハーフサイズを種類別に設定
    m_pCollision[(int)eEnemyCollision::Body]->AccessorHalfSize(m_tParam.m_f3Size / 2.0f);
    m_pCollision[(int)eEnemyCollision::Search]->AccessorHalfSize(DirectX::XMFLOAT3(5.0f, 5.0f, 5.0f));
    m_pCollision[(int)eEnemyCollision::Attack]->AccessorHalfSize(DirectX::XMFLOAT3(3.0f, 3.0f, 3.0f));
}

void CDragon::Attack()
{
    // 確率の取得
    int nPercent = GetRandOfRange(0,100);

    // プレイヤーとの距離からステートパターンを取得
    // ステートパターンに応じて変更された確率を使い、攻撃手段を決定
    switch (CEnemyBase::GetPattern(m_pCollision[(int)eEnemyCollision::Attack]->AccessorHalfSize()))
    {
    case eEnemyStatePattern::Near:
        if (nPercent <= 20) AttackBreath();
        else AttackNormal();
        break;
    case eEnemyStatePattern::Middle:
        if (nPercent <= 50) AttackBreath();
        else AttackNormal();
        break;
    case eEnemyStatePattern::Far:
        if (nPercent <= 80) AttackBreath();
        else AttackNormal();
        break;
    default:
        break;
    }
}

void CDragon::AttackNormal()
{
    // 攻撃を出す位置を決める
    // プレイヤーの座標を取得
    DirectX::XMFLOAT3 f3PlayerPos = m_pPlayer->AccessorPos();
    // 計算用にVECTORに変換
    DirectX::XMVECTOR vecPlayerPos = DirectX::XMLoadFloat3(&f3PlayerPos);
    // 同様に自身の位置も計算用にVECTORに変換
    DirectX::XMVECTOR vecEnemyPos = DirectX::XMLoadFloat3(&m_tParam.m_f3Pos);

    // 攻撃の方向を求める
    DirectX::XMVECTOR vecDirection = DirectX::XMVector3Normalize(vecPlayerPos - vecEnemyPos);
    // 自身のサイズ分前に出す
    vecDirection *= m_tParam.m_f3Size.z;

    // 攻撃位置(オフセット)の決定
    DirectX::XMFLOAT3 f3AttackPos;
    DirectX::XMStoreFloat3(&f3AttackPos, vecDirection);
    // オフセット位置に自身の座標を加算し最終位置を決定
    f3AttackPos += m_tParam.m_f3Pos;

    // 攻撃用ステータスの決定
    AttackState tState;
    tState.m_f3Center = f3AttackPos;                                // 中心座標
    tState.m_f3Size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);          // サイズ 
    tState.m_fAttackDuration = 1.0f;                                // 攻撃持続時間
    tState.m_nDamage = m_tEnemyStatus.m_nAttack;                    // ダメージ
    tState.m_sTexKey = "DragonNormalAttack";                        // 攻撃用テクスチャのキー
    tState.m_n2Split = DirectX::XMINT2(5, 2);                       // 攻撃用テクスチャのスプライト分割数
    tState.m_tDirectionState.m_eKind = DirectionKind::Stay;         // 生成後の動き
    // 生成後の動きに必要なパラメータの設定
    tState.m_tDirectionState.m_tStayPos.m_f3StayPos = f3AttackPos;  // 留める位置

    // 攻撃用ステータスを渡す
    CEnemyBase::Attack(tState);
}

void CDragon::AttackBreath()
{
    // 攻撃を出す位置を決める
    // プレイヤーの座標を取得
    DirectX::XMFLOAT3 f3PlayerPos = m_pPlayer->AccessorPos();
    // 計算用にVECTORに変換
    DirectX::XMVECTOR vecPlayerPos = DirectX::XMLoadFloat3(&f3PlayerPos);
    // 同様に自身の位置も計算用にVECTORに変換
    DirectX::XMVECTOR vecEnemyPos = DirectX::XMLoadFloat3(&m_tParam.m_f3Pos);

    // 攻撃の方向を求める
    DirectX::XMVECTOR vecDirection = DirectX::XMVector3Normalize(vecPlayerPos - vecEnemyPos);
    // 自身のサイズ分前に出す
    vecDirection *= m_tParam.m_f3Size.z;

    // 攻撃位置(オフセット)の決定
    DirectX::XMFLOAT3 f3AttackPos;
    DirectX::XMStoreFloat3(&f3AttackPos, vecDirection);
    // オフセット位置に自身の座標を加算し最終位置を決定
    f3AttackPos += m_tParam.m_f3Pos;

    // 攻撃用ステータスの決定
    AttackState tState;
    tState.m_f3Center = f3AttackPos;                                // 中心座標
    tState.m_f3Size = DirectX::XMFLOAT3(3.0f, 1.0f, 3.0f);          // サイズ 
    tState.m_fAttackDuration = 1.0f;                                // 攻撃持続時間
    tState.m_nDamage = m_tEnemyStatus.m_nAttack;                    // ダメージ
    tState.m_sTexKey = "DragonNormalAttack";                        // 攻撃用テクスチャのキー
    tState.m_n2Split = DirectX::XMINT2(1, 11);                       // 攻撃用テクスチャのスプライト分割数
    tState.m_tDirectionState.m_eKind = DirectionKind::Stay;         // 生成後の動き
    // 生成後の動きに必要なパラメータの設定
    tState.m_tDirectionState.m_tStayPos.m_f3StayPos = f3AttackPos;  // 留める位置

    // 攻撃用ステータスを渡す
    CEnemyBase::Attack(tState);
}
