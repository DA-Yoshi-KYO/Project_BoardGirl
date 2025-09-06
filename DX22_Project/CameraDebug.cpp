#include "CameraDebug.h"
#include "Defines.h"
#include "Oparation.h"
#include "Input.h"

#define CAMERA_SPEED (0.001f)

CCameraDebug::CCameraDebug()
	: m_radXZ(0.0f), m_radY(DirectX::XMConvertToRadians(0.0f)), m_radius(10.0f)
{
	m_f3Pos = { 0.0f,0.0f, -50.0f };
	m_f3Look = { 0.0f,3.5f,0.0f };
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
	if (IsKeyPress('W'))f3Velocity += f3Forward;
	if (IsKeyPress('S'))f3Velocity -= f3Forward;
	if (IsKeyPress('D'))f3Velocity += f3Right;
	if (IsKeyPress('A'))f3Velocity -= f3Right;
	if (IsKeyPress('Q'))f3Velocity += fUp;
	if (IsKeyPress('E'))f3Velocity -= fUp;
    m_f3Look += f3Velocity;

    if (IsMouseButtonTrigger(MOUSEBUTTON_R))
    {
        POINT center;
        center.x = 0;
        center.y = 0;
        ShowCursor(false);
        SetMousePosition(center);
    }

    if (IsMouseButtonPress(MOUSEBUTTON_R))
    {
        POINT mousePos = *GetMousePosition();
        m_radXZ += mousePos.x * CAMERA_SPEED;
        m_radY += mousePos.y * CAMERA_SPEED;

        POINT center;
        center.x = 0;
        center.y = 0;
        SetMousePosition(center);
    }

    if (IsMouseButtonRelease(MOUSEBUTTON_R))
    {
        ShowCursor(true);
    }

	m_f3Pos.x = cosf(m_radY) * sinf(m_radXZ) * m_radius + m_f3Look.x;
	m_f3Pos.y = sinf(m_radY) * m_radius + m_f3Look.y;
	m_f3Pos.z = cosf(m_radY) * cosf(m_radXZ) * m_radius + m_f3Look.z;
}
