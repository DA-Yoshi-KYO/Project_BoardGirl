#include "SkyBox.h"
#include "Main.h"

CSkyBox::~CSkyBox()
{
}

void CSkyBox::Init()
{
    CModelRenderer* pRenderer = AddComponent<CModelRenderer>();
    pRenderer->Load(MODEL_PATH("SkyBox.obj"));
}

void CSkyBox::Update()
{
    m_tParam.m_f3Pos = GetScene()->GetGameObject<CPlayer>()->AccessorPos();
    CGameObject::Update();
}

void CSkyBox::Draw()
{
    CGameObject::Draw();
}
