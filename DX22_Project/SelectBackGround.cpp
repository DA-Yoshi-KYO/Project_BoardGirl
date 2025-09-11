#include "SelectBackGround.h"
#include "Sprite3DRenderer.h"

CSelectBackGround::~CSelectBackGround()
{
}

void CSelectBackGround::Init()
{
    AddComponent<CSprite3DRenderer>()->SetKey("SelectBG");
    m_tParam.m_f3Size = { 25.0f, 15.0f, 0.0f };
}
