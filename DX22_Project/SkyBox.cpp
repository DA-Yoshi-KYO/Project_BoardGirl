#include "SkyBox.h"
#include "Main.h"
#include "Camera.h"

CSkyBox::~CSkyBox()
{
}

void CSkyBox::Init()
{
    CModelRenderer* pRenderer = AddComponent<CModelRenderer>();
    pRenderer->Load(MODEL_PATH("SkyBox.obj"),100000);
    pRenderer->SetDepth(false);
    m_tParam.m_eCulling = D3D11_CULL_FRONT;
}

void CSkyBox::Update()
{
    m_tParam.m_f3Pos = CCamera::GetInstance(CCamera::GetCameraKind())->GetPos();
    CGameObject::Update();
}

void CSkyBox::Draw()
{
    CGameObject::Draw();
}
