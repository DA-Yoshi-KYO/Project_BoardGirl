#include "Player.h"
#include "Input.h"
#include "BillboardRenderer.h"
#include "Defines.h"

constexpr float ce_fRotatePow = 1.0f;
constexpr float ce_fMovePow = 0.15f;
constexpr float ce_fAccel = 0.15f;

void CPlayer::Init()
{
	AddComponent<CBillboardRenderer>();
	m_tParam.m_f3Pos = { 0.0f,0.0f,0.0f };
	m_tParam.m_f3Size = { 1.0f,1.0f,1.0f };

	m_f3Velocity = {};
	m_bJump = false;
}

void CPlayer::Update()
{
	PlayerMove();
}

DirectX::XMFLOAT3 CPlayer::GetForward()
{
	DirectX::XMMATRIX mRotate = DirectX::XMMatrixRotationRollPitchYaw(m_tParam.m_f3Rotate.x, m_tParam.m_f3Rotate.y, m_tParam.m_f3Rotate.z);

	DirectX::XMFLOAT3 f3ForWard;
	DirectX::XMStoreFloat3(&f3ForWard, mRotate.r[2]);

	return f3ForWard;
}

DirectX::XMFLOAT3 CPlayer::GetRight()
{
	DirectX::XMMATRIX mRotate = DirectX::XMMatrixRotationRollPitchYaw(m_tParam.m_f3Rotate.x, m_tParam.m_f3Rotate.y, m_tParam.m_f3Rotate.z);

	DirectX::XMFLOAT3 f3Right;
	DirectX::XMStoreFloat3(&f3Right, mRotate.r[0]);

	return f3Right;
}

void CPlayer::PlayerMove()
{
	DirectX::XMFLOAT3 f3ForWard = GetForward();
	DirectX::XMFLOAT3 f3Right = GetRight();
	m_f3Velocity.x = 0.0f;
	m_f3Velocity.z = 0.0f;
	if (IsKeyPress(VK_LEFT)) m_tParam.m_f3Rotate.y -= DirectX::XMConvertToRadians(ce_fRotatePow);
	else if (IsKeyPress(VK_RIGHT)) m_tParam.m_f3Rotate.y += DirectX::XMConvertToRadians(ce_fRotatePow);
	if (IsKeyPress(VK_DOWN)) m_tParam.m_f3Rotate.x -= DirectX::XMConvertToRadians(ce_fRotatePow);
	else if (IsKeyPress(VK_UP)) m_tParam.m_f3Rotate.x += DirectX::XMConvertToRadians(ce_fRotatePow);
	constexpr float ce_fMinRotateX = DirectX::XMConvertToRadians(-45.0f);
	constexpr float ce_fMaxRotateX = DirectX::XMConvertToRadians(45.0f);
	m_tParam.m_f3Rotate.x = std::clamp(m_tParam.m_f3Rotate.x, ce_fMinRotateX, ce_fMaxRotateX);

	if (IsKeyPress('W'))
	{
		m_f3Velocity.x += f3ForWard.x * ce_fAccel;
		m_f3Velocity.z += f3ForWard.z * ce_fAccel;
	}
	else if (IsKeyPress('S'))
	{
		m_f3Velocity.x -= f3ForWard.x * ce_fAccel;
		m_f3Velocity.z -= f3ForWard.z * ce_fAccel;
	}
	if (IsKeyPress('A'))
	{
		m_f3Velocity.x -= f3Right.x * ce_fAccel;
		m_f3Velocity.z -= f3Right.z * ce_fAccel;
	}
	else if (IsKeyPress('D'))
	{
		m_f3Velocity.x += f3Right.x * ce_fAccel;
		m_f3Velocity.z += f3Right.z * ce_fAccel;
	}

	if (IsKeyTrigger(VK_SPACE) && !m_bJump)
	{
		m_f3Velocity.y += 0.35f;
		m_bJump = true;
	}

    m_f3Velocity.x = std::clamp(m_f3Velocity.x, -ce_fMovePow, ce_fMovePow);
    m_f3Velocity.z = std::clamp(m_f3Velocity.z, -ce_fMovePow, ce_fMovePow);

	float ground_height = 0.0f;
	m_f3Velocity.y -= 0.015f;
	m_tParam.m_f3Pos.x += m_f3Velocity.x;
	m_tParam.m_f3Pos.y += m_f3Velocity.y;
	m_tParam.m_f3Pos.z += m_f3Velocity.z;
	if (m_tParam.m_f3Pos.y < ground_height)
	{
		m_tParam.m_f3Pos.y = ground_height;
		m_f3Velocity.y = 0.0f;
		m_bJump = false;
	}
}
