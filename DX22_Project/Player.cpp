// インクルード部
#include "Player.h"
#include "Input.h"
#include "BillboardRenderer.h"
#include "Defines.h"
#include <DirectXMath.h>
#include "SceneJobSelect.h"
#include "Soldier.h"
#include "Wizard.h"
#include "Fighter.h"

// 定数定義
constexpr float ce_fRotatePow = 1.0f;   // 回転速度
constexpr float ce_fMovePow = 0.15f;    // 移動速度
constexpr DirectX::XMINT2 ce_n2Split = { 6, 6 };

void CPlayer::Init()
{
    // コンポーネントの追加
	AddComponent<CBillboardRenderer>()->SetKey("Player");
    m_pCollision = AddComponent<CCollisionObb>();

    // 汎用パラメータの初期化
	m_tParam.m_f3Pos = { 0.0f,0.0f,0.0f };
    m_f3OldPos = m_tParam.m_f3Pos;
	m_tParam.m_f3Size = { 1.0f,1.0f,1.0f };
    m_pCollision->AccessorCenter(m_tParam.m_f3Pos);
    m_pCollision->AccessorHalfSize(m_tParam.m_f3Size / 2.0f);
    m_pCollision->AccessorTag("PlayerBody");

    // 特有パラメータの初期化
	m_f3Velocity = {};
	m_bJump = false;

    JobKind eJob = CSceneJobSelect::GetSelectedJob();

    switch (eJob)
    {
    case JobKind::Soldier:
        m_pJob = std::make_unique<CSoldier>();
        m_tParam.m_f2UVPos = { 0.0f / (float)ce_n2Split.x , 1.0f / (float)ce_n2Split.y };
        break;
    case JobKind::Wizard:
        m_pJob = std::make_unique<CWizard>();
        m_tParam.m_f2UVPos = { 3.0f / (float)ce_n2Split.x , 1.0f / (float)ce_n2Split.y };
        break;
    case JobKind::Fighter:
        m_pJob = std::make_unique<CFighter>();
        m_tParam.m_f2UVPos = { 1.0f / (float)ce_n2Split.x , 1.0f / (float)ce_n2Split.y };
        break;
    case JobKind::Max:
        break;
    default:
        break;
    }
    m_tParam.m_f2UVSize = { 1.0f / (float)ce_n2Split.x, 1.0f / (float)ce_n2Split.y };
}

void CPlayer::Update()
{
    m_f3OldPos = m_tParam.m_f3Pos;
    // 移動処理
	PlayerMove();
    PlayerSkill();

    m_pCollision->AccessorCenter(m_tParam.m_f3Pos);
    m_pCollision->AccessorHalfSize(m_tParam.m_f3Size / 2.0f);

    CGameObject::Update();
}

void CPlayer::OnColliderHit(CCollisionBase* other, std::string thisTag)
{
    if (thisTag == "PlayerBody")
    {
        if (other->AccessorTag() == "EnemyBody")
        {
            m_tParam.m_f3Pos = m_f3OldPos;
        }
    }
}

DirectX::XMFLOAT3 CPlayer::GetForward()
{
    // プレイヤーの前方向を取得するために、回転行列を生成
	DirectX::XMMATRIX mRotate = DirectX::XMMatrixRotationRollPitchYaw(m_tParam.m_f3Rotate.x, m_tParam.m_f3Rotate.y, m_tParam.m_f3Rotate.z);

    // 回転行列のZ軸([2])を前方向として取得
	DirectX::XMFLOAT3 f3ForWard;
	DirectX::XMStoreFloat3(&f3ForWard, mRotate.r[2]);

	return f3ForWard;
}

DirectX::XMFLOAT3 CPlayer::GetRight()
{
    // プレイヤーの前方向を取得するために、回転行列を生成
    DirectX::XMMATRIX mRotate = DirectX::XMMatrixRotationRollPitchYaw(m_tParam.m_f3Rotate.x, m_tParam.m_f3Rotate.y, m_tParam.m_f3Rotate.z);

    // 回転行列のX軸([0])を右方向として取得
    DirectX::XMFLOAT3 f3ForWard;
    DirectX::XMStoreFloat3(&f3ForWard, mRotate.r[0]);

    return f3ForWard;
}

void CPlayer::PlayerMove()
{
    // プレイヤーの前方向と右方向を取得
	DirectX::XMFLOAT3 f3ForWard = GetForward();
	DirectX::XMFLOAT3 f3Right = GetRight();

    // 移動量は初期化してから計算する
	m_f3Velocity.x = 0.0f;
	m_f3Velocity.z = 0.0f;

    // キー入力によるカメラ回転処理
	if (IsKeyPress(VK_LEFT)) m_tParam.m_f3Rotate.y -= DirectX::XMConvertToRadians(ce_fRotatePow);
	else if (IsKeyPress(VK_RIGHT)) m_tParam.m_f3Rotate.y += DirectX::XMConvertToRadians(ce_fRotatePow);
	if (IsKeyPress(VK_DOWN)) m_tParam.m_f3Rotate.x -= DirectX::XMConvertToRadians(ce_fRotatePow);
	else if (IsKeyPress(VK_UP)) m_tParam.m_f3Rotate.x += DirectX::XMConvertToRadians(ce_fRotatePow);
    // 回転の速度は-45度から45度の範囲に制限する
	constexpr float ce_fMinRotateX = DirectX::XMConvertToRadians(-45.0f);
	constexpr float ce_fMaxRotateX = DirectX::XMConvertToRadians(45.0f);
	m_tParam.m_f3Rotate.x = std::clamp(m_tParam.m_f3Rotate.x, ce_fMinRotateX, ce_fMaxRotateX);

    // キー入力による移動処理
	if (IsKeyPress('W'))
	{
		m_f3Velocity.x += f3ForWard.x * ce_fMovePow;
		m_f3Velocity.z += f3ForWard.z * ce_fMovePow;
	}
	else if (IsKeyPress('S'))
	{
		m_f3Velocity.x -= f3ForWard.x * ce_fMovePow;
		m_f3Velocity.z -= f3ForWard.z * ce_fMovePow;
	}
	if (IsKeyPress('A'))
	{
		m_f3Velocity.x -= f3Right.x * ce_fMovePow;
		m_f3Velocity.z -= f3Right.z * ce_fMovePow;
	}
	else if (IsKeyPress('D'))
	{
		m_f3Velocity.x += f3Right.x * ce_fMovePow;
		m_f3Velocity.z += f3Right.z * ce_fMovePow;
	}

    // キー入力によるジャンプ処理
	if (IsKeyTrigger(VK_SPACE) && !m_bJump)
	{
		m_f3Velocity.y += 0.35f;
		m_bJump = true;
	}

    // 重力
	m_f3Velocity.y -= 0.015f;

    // 移動量を使用してプレイヤーの位置を更新
    m_tParam.m_f3Pos.x += m_f3Velocity.x;
	m_tParam.m_f3Pos.y += m_f3Velocity.y;
	m_tParam.m_f3Pos.z += m_f3Velocity.z;

    // 着地処理
	float ground_height = 0.0f;
	if (m_tParam.m_f3Pos.y < ground_height + m_tParam.m_f3Size.y * 0.5f)
	{
		m_tParam.m_f3Pos.y = ground_height + m_tParam.m_f3Size.y * 0.5f;
		m_f3Velocity.y = 0.0f;
		m_bJump = false;
	}
}

void CPlayer::PlayerSkill()
{
    if (IsKeyTrigger('1'))
    {
        m_pJob->Skill(eSkill::NormalAttack);
    }
    if (IsKeyTrigger('Q'))
    {
        m_pJob->Skill(eSkill::QSkill);
    }
    if (IsKeyTrigger('E'))
    {
        m_pJob->Skill(eSkill::ESkill);
    }
    if (IsKeyTrigger('R'))
    {
        m_pJob->Skill(eSkill::RSkill);
    }

    m_pJob->Update();
}
