// インクルード部
#include "Ghost.h"
#include "Oparation.h"
#include "Player.h"
#include "EnemyAttack.h"
#include "Main.h"
#include "BillboardRenderer.h"

// 定数・マクロ定義
constexpr float ce_fShotSpeed = 0.2f;

CGhost::CGhost()
    : CEnemyBase()
{
    // 幽霊のステータスを決定
    m_tEnemyStatus.m_nHP = 30;
    m_tEnemyStatus.m_nAttack = 5;
    m_tEnemyStatus.m_fSpeed = 0.05f;
    m_tEnemyStatus.m_nScore = 10;
    m_tEnemyStatus.m_bMove = false;
    m_tEnemyStatus.m_bDamage = false;
}

CGhost::~CGhost()
{

}

void CGhost::Init()
{
    // 敵共通の初期化処理
    CEnemyBase::Init();

    // 描画に使用するテクスチャのキーをセット
    AddComponent<CBillboardRenderer>()->SetKey("Ghost");

    // コリジョンのハーフサイズを種類別に設定
    m_pCollision[(int)eEnemyCollision::Body]->AccessorHalfSize(m_tParam.m_f3Size / 2.0f);
    m_pCollision[(int)eEnemyCollision::Search]->AccessorHalfSize(DirectX::XMFLOAT3( 10.0f, 10.0f, 10.0f));
    m_pCollision[(int)eEnemyCollision::Attack]->AccessorHalfSize(DirectX::XMFLOAT3( 10.0f, 10.0f, 10.0f));
}

void CGhost::Attack()
{
    // 弾の発射方向決定
    // プレイヤーの座標を取得
    DirectX::XMFLOAT3 f3PlayerPos = m_pPlayer->AccessorPos();
    // 計算用にVECTORに変換
    DirectX::XMVECTOR vecPlayerPos = DirectX::XMLoadFloat3(&f3PlayerPos);
    // 同様に自身の座標も変換
    DirectX::XMVECTOR vecEnemyPos = DirectX::XMLoadFloat3(&m_tParam.m_f3Pos);
    // 差分を正規化し、方向を決定する
    DirectX::XMVECTOR vecDirection = DirectX::XMVector3Normalize(vecPlayerPos - vecEnemyPos);
    // 速度をかける
    vecDirection *= ce_fShotSpeed;
    // 発射方向の決定
    DirectX::XMFLOAT3 f3ShotDir;
    DirectX::XMStoreFloat3(&f3ShotDir, vecDirection);

    AttackState tState;
    tState.m_f3Center = m_tParam.m_f3Pos;                           // 中心座標
    tState.m_f3Size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);          // サイズ 
    tState.m_fAttackDuration = 1.0f;                                // 攻撃持続時間
    tState.m_nDamage = m_tEnemyStatus.m_nAttack;                    // ダメージ
    tState.m_sTexKey = "GhostAttack";                               // 攻撃用テクスチャのキー
    tState.m_n2Split = DirectX::XMINT2(10, 1);                      // 攻撃用テクスチャのスプライト分割数
    tState.m_tDirectionState.m_eKind = DirectionKind::Toward;       // 生成後の動き
    // 生成後の動きに必要なパラメータの設定
    tState.m_tDirectionState.m_tToward.m_f3Direction = f3ShotDir;   // 射撃方向
    // 留める位置
    CEnemyBase::Attack(tState);
}
