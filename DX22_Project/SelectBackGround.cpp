#include "SelectBackGround.h"
#include "SpriteRenderer.h"

CSelectBackGround::~CSelectBackGround()
{
}

void CSelectBackGround::Init()
{
    CSpriteRenderer* pRenderer = AddComponent<CSpriteRenderer>();
    pRenderer->Init();
    pRenderer->Load(TEXTURE_PATH("Select.jpg"));
    m_tParam.m_f3Size = { SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f };
}
