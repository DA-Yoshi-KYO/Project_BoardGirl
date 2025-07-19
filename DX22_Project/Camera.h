#pragma once

#include <DirectXMath.h>
#include <memory>

//#define _CAM_DEBUG

enum CameraKind
{
	CAM_DEBUG,
	CAM_PLAYER,
	MAX_CAMERA // ÉJÉÅÉâç≈ëÂêî 
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
	DirectX::XMFLOAT3 GetPos() { return m_f3Pos; }
	DirectX::XMFLOAT3 GetLook() { return m_f3Look; }
	
	static const DirectX::XMFLOAT4X4 Get2DWolrdMatrix(float rotate = 0.0f,bool transpose = true);
	static const DirectX::XMFLOAT4X4 Get2DViewMatrix(bool transpose = true);
	static const DirectX::XMFLOAT4X4 Get2DProjectionMatrix(bool transpose = true);
	static std::unique_ptr<CCamera>& GetInstance(int CamKind);
	static void SetCameraKind(CameraKind kind);
	static CameraKind GetCameraKind();
protected:
	DirectX::XMFLOAT3 m_f3Pos;
	DirectX::XMFLOAT3 m_f3Look;
	DirectX::XMFLOAT3 m_f3Up;
	float m_fFovy;
	float m_fAspect;
	float m_fNear;
	float m_fFar;
private:
	static CameraKind m_eCameraKind;
};
