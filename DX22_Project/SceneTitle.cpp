#include "SceneTitle.h"
#include "TitleBackGround.h"

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Init()
{
	AddGameObject<CTitleBackGround>(Collision::None,Tag::UI);
}
