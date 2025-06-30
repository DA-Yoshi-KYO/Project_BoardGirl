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

	pScene->GetGameObject<CPlayer>()->
}