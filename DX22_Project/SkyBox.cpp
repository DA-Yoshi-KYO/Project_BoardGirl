#include "SkyBox.h"
#include "Main.h"

CSkyBox::~CSkyBox()
{
}

void CSkyBox::Init()
{
    CModelRenderer* pRenderer = AddComponent<CModelRenderer>();
    pRenderer->Load(MODEL_PATH("SkyBox.obj"),1);
    //pRenderer->SetDepth(false);
    //m_tParam.m_eCulling = D3D11_CULL_FRONT;
}

void CSkyBox::Update()
{
    //m_tParam.m_f3Pos = GetScene()->GetGameObject<CPlayer>()->AccessorPos();
    //m_tParam.m_f3Pos.y += 1.0f;
    CGameObject::Update();
}

void CSkyBox::Draw()
{
    CGameObject::Draw();
}
