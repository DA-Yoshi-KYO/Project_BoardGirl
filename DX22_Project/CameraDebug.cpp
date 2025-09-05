#include "CameraDebug.h"
#include "Defines.h"
#include "Oparation.h"

CCameraDebug::CCameraDebug()
	: m_radXZ(0.0f), m_radY(DirectX::XMConvertToRadians(0.0f)), m_radius(0.0f)
{
	m_f3Pos = { 0.0f,0.0f, 161.0f };
	m_f3Look = { 0.0f,3.5f,111.0f };
}

CCameraDebug::~CCameraDebug()
{
}

void CCameraDebug::Update()
{
    DirectX::XMFLOAT3 f3Forward = m_f3Look - m_f3Pos;
    DirectX::XMVECTOR vForward = DirectX::XMLoadFloat3(&f3Forward);
    vForward = DirectX::XMVector3Normalize(vForward);
    DirectX::XMStoreFloat3(&f3Forward, vForward);

    DirectX::XMFLOAT3 fUp = m_f3Up;
    DirectX::XMVECTOR vUp = DirectX::XMLoadFloat3(&m_f3Up);
    vUp = DirectX::XMVector3Normalize(vUp);
    DirectX::XMStoreFloat3(&fUp, vUp);

    DirectX::XMVECTOR vRight = DirectX::XMVector3Cross(vUp, vForward);
    DirectX::XMFLOAT3 f3Right;
    DirectX::XMStoreFloat3(&f3Right, vRight);

    DirectX::XMFLOAT3 f3Velocity{};
	if (IsKeyPress(VK_UP))f3Velocity += f3Forward;
	if (IsKeyPress(VK_DOWN))f3Velocity -= f3Forward;
	if (IsKeyPress(VK_RIGHT))f3Velocity += f3Right;
	if (IsKeyPress(VK_LEFT))f3Velocity -= f3Right;
	if (IsKeyPress(VK_SHIFT))f3Velocity += fUp;
	if (IsKeyPress(VK_CONTROL))f3Velocity -= fUp;

    m_f3Look += f3Velocity;

	if (IsKeyPress('A')) m_radXZ -= CAMERA_ROTATE;
	if (IsKeyPress('D')) m_radXZ += CAMERA_ROTATE;
	if (IsKeyPress('W')) m_radY -= CAMERA_ROTATE;
	if (IsKeyPress('S')) m_radY += CAMERA_ROTATE;

	if (IsKeyPress('E')) m_radius += CAMERA_SPEED;
	if (IsKeyPress('Q')) m_radius -= CAMERA_SPEED;

	if (m_radius <= 10.0f) m_radius = 10.0f;

	m_f3Pos.x = cosf(m_radY) * sinf(m_radXZ) * m_radius + m_f3Look.x;
	m_f3Pos.y = sinf(m_radY) * m_radius + m_f3Look.y;
	m_f3Pos.z = cosf(m_radY) * cosf(m_radXZ) * m_radius + m_f3Look.z;
}
