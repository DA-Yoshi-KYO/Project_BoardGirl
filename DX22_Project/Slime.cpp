#include "Slime.h"
#include "BillboardRenderer.h"
#include "Oparation.h"
#include "Player.h"

CSlime::CSlime()
    : CEnemyBase()
{
    // 幽霊のステータスを決定
    m_tEnemyStatus.m_nHP = 10;
    m_tEnemyStatus.m_nAttack = 10;
    m_tEnemyStatus.m_fSpeed = 0.05f;
    m_tEnemyStatus.m_nScore = 10;
    m_tEnemyStatus.m_bMove = false;
    m_tEnemyStatus.m_bDamage = false;
}

CSlime::~CSlime()
{

}

void CSlime::Init()
{
    // 敵共通の初期化処理
    CEnemyBase::Init();

    // 描画に使用するテクスチャのキーをセット
    AddComponent<CBillboardRenderer>()->SetKey("Slime");

    // コリジョンのハーフサイズを種類別に設定
    m_pCollision[(int)eEnemyCollision::Body]->AccessorHalfSize(m_tParam.m_f3Size / 2.0f);
    m_pCollision[(int)eEnemyCollision::Search]->AccessorHalfSize(DirectX::XMFLOAT3(5.0f, 5.0f, 5.0f));
    m_pCollision[(int)eEnemyCollision::Attack]->AccessorHalfSize(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
}

void CSlime::Attack()
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
    tState.m_sTexKey = "SlimeAttack";                               // 攻撃用テクスチャのキー
    tState.m_n2Split = DirectX::XMINT2(5, 2);                       // 攻撃用テクスチャのスプライト分割数
    tState.m_tDirectionState.m_eKind = DirectionKind::Stay;         // 生成後の動き
    // 生成後の動きに必要なパラメータの設定
    tState.m_tDirectionState.m_tStayPos.m_f3StayPos = f3AttackPos;  // 留める位置

    // 攻撃用ステータスを渡す
    CEnemyBase::Attack(tState);
}
