#include "CameraPlayer.h"
#include "Main.h"
#include "SceneGame.h"
#include "Player.h"
#include "Oparation.h"

CCameraPlayer::~CCameraPlayer()
{
}

void CCameraPlayer::Update()
{
	CScene* pScene = GetScene();
	if (!dynamic_cast<CSceneGame*>(pScene)) return;

	CPlayer* pPlayer = pScene->GetGameObject<CPlayer>();
	DirectX::XMFLOAT3 f3PlayerPos = pPlayer->AccessorPos();
	DirectX::XMFLOAT3 f3PlayerForWard = pPlayer->GetForward();

	constexpr DirectX::XMFLOAT3 ce_f3CameraLookOffset = {0.0f,0.0f,0.0f};
	constexpr float ce_fCameraDistance = 8.0f;
	constexpr DirectX::XMFLOAT3 ce_f3CameraOffset = { 0.0f,4.0f,0.0f };

	m_f3Look = f3PlayerPos;
	m_f3Look += ce_f3CameraLookOffset;

	m_f3Pos = f3PlayerPos - f3PlayerForWard * ce_fCameraDistance + ce_f3CameraOffset;
}
