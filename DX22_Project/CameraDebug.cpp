#include "CameraDebug.h"
#include "Defines.h"

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
	if (IsKeyPress(VK_UP))m_f3Look.z += CAMERA_SPEED;
	if (IsKeyPress(VK_DOWN))m_f3Look.z -= CAMERA_SPEED;
	if (IsKeyPress(VK_RIGHT))m_f3Look.x += CAMERA_SPEED;
	if (IsKeyPress(VK_LEFT))m_f3Look.x -= CAMERA_SPEED;
	if (IsKeyPress(VK_SHIFT))m_f3Look.y += CAMERA_SPEED;
	if (IsKeyPress(VK_CONTROL))m_f3Look.y -= CAMERA_SPEED;

	if (IsKeyPress('A')) m_radXZ -= CAMERA_ROTATE;
	if (IsKeyPress('D')) m_radXZ += CAMERA_ROTATE;
	if (IsKeyPress('W')) m_radY += CAMERA_ROTATE;
	if (IsKeyPress('S')) m_radY -= CAMERA_ROTATE;

	if (IsKeyPress('E')) m_radius += CAMERA_SPEED;
	if (IsKeyPress('Q')) m_radius -= CAMERA_SPEED;

	if (m_radius <= 10.0f) m_radius = 10.0f;

	m_f3Pos.x = cosf(m_radY) * sinf(m_radXZ) * m_radius + m_f3Look.x;
	m_f3Pos.y = sinf(m_radY) * m_radius + m_f3Look.y;
	m_f3Pos.z = cosf(m_radY) * cosf(m_radXZ) * m_radius + m_f3Look.z;
}
