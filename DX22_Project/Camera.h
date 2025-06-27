#pragma once

#include <DirectXMath.h>
#include <memory>

//#define _CAM_DEBUG

enum CameraKind
{
	CAM_DEBUG,
	MAX_CAMERA // �J�����ő吔 
};

class CCamera
{	
public:
	CCamera();
	virtual ~CCamera();
	virtual void Update() = 0;
	/*Getter*/
	DirectX::XMFLOAT4X4 GetViewMatrix(bool transpose = true);
	DirectX::XMFLOAT4X4 GetProjectionMatrix(bool transpose = true);
	DirectX::XMFLOAT3 GetPos() { return m_pos; }
	DirectX::XMFLOAT3 GetLook() { return m_look; }
	DirectX::XMFLOAT3 GetForward() { return m_look; }

	static const DirectX::XMFLOAT4X4 Get2DWolrdMatrix(float rotate = 0.0f,bool transpose = true);
	static const DirectX::XMFLOAT4X4 Get2DViewMatrix(bool transpose = true);
	static const DirectX::XMFLOAT4X4 Get2DProjectionMatrix(bool transpose = true);
	static std::unique_ptr<CCamera>& GetInstance(int CamKind);
	static void SetCameraKind(CameraKind kind);
	static CameraKind GetCameraKind();
protected:
	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_look;
	DirectX::XMFLOAT3 m_up;
	float m_fovy;
	float m_aspect;
	float m_near;
	float m_far;
private:
	static CameraKind m_eCameraKind;
};

