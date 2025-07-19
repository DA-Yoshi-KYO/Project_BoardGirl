#include "SceneGame.h"
#include "Camera.h"
#include "Player.h"

void CSceneGame::Init()
{
	CCamera::SetCameraKind(CAM_PLAYER);
	AddGameObject<CPlayer>();
}
