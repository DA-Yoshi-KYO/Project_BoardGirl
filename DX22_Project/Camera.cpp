#include "Camera.h"
#include "Defines.h"
#include "CameraDebug.h"

CameraKind CCamera::m_eCameraKind = CameraKind::CAM_DEBUG;

CCamera::CCamera()
	: m_pos{ 0.0f, 10.0f, 0.0f }, m_look{ 0.0f ,0.0f,0.0f }, m_up{ 0.0f,1.0f,0.0f }
	, m_fovy(DirectX::XMConvertToRadians(60.0f)), m_aspect(16.0f / 9.0f)
	, m_near(CMETER(30.0f)), m_far(METER(1000.0f))
{
}

CCamera::~CCamera()
{
}

DirectX::XMFLOAT4X4 CCamera::GetViewMatrix(bool transpose)
{
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX view;

	view = DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(m_pos.x, m_pos.y, m_pos.z, 0.0f),
		DirectX::XMVectorSet(m_look.x, m_look.y, m_look.z, 0.0f),
		DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f));

	if (transpose) view = DirectX::XMMatrixTranspose(view);

	DirectX::XMStoreFloat4x4(&mat, view);

	return mat;
}

DirectX::XMFLOAT4X4 CCamera::GetProjectionMatrix(bool transpose)
{
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX proj;
	proj = DirectX::XMMatrixPerspectiveFovLH(m_fovy, m_aspect, m_near, m_far);

	if (transpose)proj = DirectX::XMMatrixTranspose(proj);

	DirectX::XMStoreFloat4x4(&mat, proj);

	return mat;
}

const DirectX::XMFLOAT4X4 CCamera::Get2DWolrdMatrix(float rotate, bool transpose)
{
	DirectX::XMMATRIX mWorld = 
		DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f) *
		DirectX::XMMatrixRotationZ(rotate) *
		DirectX::XMMatrixTranslation(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);

	if (transpose) mWorld = DirectX::XMMatrixTranspose(mWorld);

	DirectX::XMFLOAT4X4 world;
	DirectX::XMStoreFloat4x4(&world, mWorld);

	return world;
}

const DirectX::XMFLOAT4X4 CCamera::Get2DViewMatrix(bool transpose)
{
	DirectX::XMFLOAT4X4 view;
	DirectX::XMMATRIX mView = DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(0.0f, 0.0f, -0.3f, 0.0f),
		DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	if (transpose)mView = DirectX::XMMatrixTranspose(mView);
	DirectX::XMStoreFloat4x4(&view, mView);
	return view;
}

const DirectX::XMFLOAT4X4 CCamera::Get2DProjectionMatrix(bool transpose)
{
	DirectX::XMFLOAT4X4 proj;
	DirectX::XMMATRIX mProj = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.1f, 100.0f);
	if (transpose)mProj = DirectX::XMMatrixTranspose(mProj);
	DirectX::XMStoreFloat4x4(&proj, mProj);
	return proj;
}

std::unique_ptr<CCamera>& CCamera::GetInstance(int CamKind)
{
	static std::unique_ptr<CCamera> CamInstance[] = {
		std::make_unique<CCameraDebug>(),
	};

	switch (CamKind)
	{
	case CAM_DEBUG:		return CamInstance[CAM_DEBUG];		break;
	default: return CamInstance[CAM_DEBUG]; break;
	}
}

void CCamera::SetCameraKind(CameraKind kind)
{
	m_eCameraKind = kind;
}

CameraKind CCamera::GetCameraKind()
{
	return m_eCameraKind;
}
