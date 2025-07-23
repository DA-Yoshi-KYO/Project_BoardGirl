#include "Camera.h"
#include "Defines.h"
#include "CameraDebug.h"
#include "CameraPlayer.h"
#include "CameraSelect.h"

CameraKind CCamera::m_eCameraKind = CameraKind::CAM_DEBUG;

CCamera::CCamera()
	: m_f3Pos{ 0.0f, 10.0f, 0.0f }, m_f3Look{ 0.0f ,0.0f,0.0f }, m_f3Up{ 0.0f,1.0f,0.0f }
	, m_fFovy(DirectX::XMConvertToRadians(60.0f)), m_fAspect(16.0f / 9.0f)
	, m_fNear(CMETER(30.0f)), m_fFar(METER(1000.0f))
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
		DirectX::XMVectorSet(m_f3Pos.x, m_f3Pos.y, m_f3Pos.z, 0.0f),
		DirectX::XMVectorSet(m_f3Look.x, m_f3Look.y, m_f3Look.z, 0.0f),
		DirectX::XMVectorSet(m_f3Up.x, m_f3Up.y, m_f3Up.z, 0.0f));

	if (transpose) view = DirectX::XMMatrixTranspose(view);

	DirectX::XMStoreFloat4x4(&mat, view);

	return mat;
}

DirectX::XMFLOAT4X4 CCamera::GetProjectionMatrix(bool transpose)
{
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX proj;
	proj = DirectX::XMMatrixPerspectiveFovLH(m_fFovy, m_fAspect, m_fNear, m_fFar);

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
		std::make_unique<CCameraPlayer>(),
        std::make_unique<CCameraSelect>(),
    };

	switch (CamKind)
	{
	case CAM_DEBUG:		return CamInstance[CAM_DEBUG];		break;
	case CAM_PLAYER:	return CamInstance[CAM_PLAYER];		break;
    case CAM_SELECT:	return CamInstance[CAM_SELECT];		break;
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
