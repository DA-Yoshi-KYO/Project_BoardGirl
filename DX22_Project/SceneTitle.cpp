// インクルード部
#include "SceneTitle.h"
#include "TitleBackGround.h"

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Init()
{
    // オブジェクトの追加
	AddGameObject<CTitleBackGround>(Tag::UI);   // タイトル画像
}
