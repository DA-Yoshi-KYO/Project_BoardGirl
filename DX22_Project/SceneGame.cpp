// インクルード部
#include "SceneGame.h"
#include "Camera.h"
#include "Field.h"
#include "Player.h"

void CSceneGame::Init()
{
    // カメラの設定をインゲームモードに変更
	CCamera::SetCameraKind(CAM_PLAYER);

    // オブジェクトの追加
    AddGameObject<CPlayer>();
    AddGameObject<CField>();
}
