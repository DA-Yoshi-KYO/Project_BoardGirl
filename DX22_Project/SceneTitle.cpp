#include "SceneTitle.h"
#include "TitleBackGround.h"

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Init()
{
    CSpriteRenderer::Load(TEXTURE_PATH("Title.jpg"), "TitleBG");

    AddGameObject<CTitleBackGround>(Tag::UI);
}
