#include "TitleBackGround.h"
#include "SpriteRenderer.h"
#include "Input.h"
#include "Sprite.h"

void CTitleBackGround::Init()
{
	CSpriteRenderer* pRenderer = AddComponent<CSpriteRenderer>();
	pRenderer->Init();
	pRenderer->Load(TEXTURE_PATH("Title.jpg"));

	m_tParam.m_f3Size = { SCREEN_WIDTH, SCREEN_HEIGHT,0.0f };
}

void CTitleBackGround::Update()
{
	if (IsKeyPress('7'))
	{
		m_tParam.m_f3Rotate.x -= 0.01f;
	}
}
