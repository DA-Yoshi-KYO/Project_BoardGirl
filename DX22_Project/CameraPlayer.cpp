#include "CameraPlayer.h"
#include "Main.h"
#include "SceneGame.h"
#include "Player.h"

CCameraPlayer::~CCameraPlayer()
{
}

void CCameraPlayer::Update()
{
	CScene* pScene = GetScene();
	if (!dynamic_cast<CSceneGame*>(pScene)) return;

	CPlayer* pPlayer = pScene->GetGameObject<CPlayer>();
	DirectX::XMFLOAT3 f3PlayerPos = pPlayer->PosAccessor();
	DirectX::XMFLOAT3 f3PlayerForWard = pPlayer->GetForward();

	constexpr DirectX::XMFLOAT3 ce_f3CameraLookOffset = {0.0f,0.0f,0.0f};
	constexpr float ce_fCameraDistance = 8.0f;
	constexpr DirectX::XMFLOAT3 ce_f3CameraOffset = { 0.0f,4.0f,0.0f };

	m_f3Look = f3PlayerPos;
	m_f3Look.x += ce_f3CameraLookOffset.x;
	m_f3Look.y += ce_f3CameraLookOffset.y;
	m_f3Look.z += ce_f3CameraLookOffset.z;

	m_f3Pos.x = f3PlayerPos.x - f3PlayerForWard.x * ce_fCameraDistance + ce_f3CameraOffset.x;
	m_f3Pos.y = f3PlayerPos.y - f3PlayerForWard.y * ce_fCameraDistance + ce_f3CameraOffset.y;
	m_f3Pos.z = f3PlayerPos.z - f3PlayerForWard.z * ce_fCameraDistance + ce_f3CameraOffset.z;
}