// インクルード部
#include "CameraPlayer.h"
#include "Main.h"
#include "SceneGame.h"
#include "Player.h"
#include "Oparation.h"

// 定数・マクロ定義
constexpr DirectX::XMFLOAT3 ce_f3CameraLookOffset = DirectX::XMFLOAT3(0.0f,0.0f,0.0f);  // カメラの注視点をどれだけずらすか
constexpr float ce_fCameraDistance = 8.0f;  // カメラの距離の係数
constexpr DirectX::XMFLOAT3 ce_f3CameraOffset = DirectX::XMFLOAT3(0.0f,4.0f,0.0f);  // カメラの位置をどれだけずらすか

CCameraPlayer::~CCameraPlayer()
{

}

void CCameraPlayer::Update()
{
	// シーンがインゲーム以外なら処理をしない
	CScene* pScene = GetScene();
	if (!dynamic_cast<CSceneGame*>(pScene)) return;

	// プレイヤーの前方向ベクトルを取得する
	CPlayer* pPlayer = pScene->GetGameObject<CPlayer>();
	DirectX::XMFLOAT3 f3PlayerPos = pPlayer->AccessorPos();
	DirectX::XMFLOAT3 f3PlayerForWard = pPlayer->GetForward();

	// 注視点をプレイヤーの位置にする
	m_f3Look = f3PlayerPos;
	// 必要に応じてプレイヤーの位置からずらす
	m_f3Look += ce_f3CameraLookOffset;

	// 座標をプレイヤー位置の後方にする
	m_f3Pos = f3PlayerPos - f3PlayerForWard * ce_fCameraDistance + ce_f3CameraOffset;
}
