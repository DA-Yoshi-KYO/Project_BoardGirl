#include "TitleBackGround.h"
#include "SpriteRenderer.h"
#include "Input.h"
#include "Sprite.h"
#include "Main.h"
#include "SceneJobSelect.h"

void CTitleBackGround::Init()
{
	CSpriteRenderer* pRenderer = AddComponent<CSpriteRenderer>();
	pRenderer->SetKey("TitleBG");

	m_tParam.m_f3Size = { SCREEN_WIDTH, SCREEN_HEIGHT,0.0f };
}

void CTitleBackGround::Update()
{
	if (IsKeyTrigger(VK_SPACE))
	{
		ChangeScene(new CSceneJobSelect());
	}
}
