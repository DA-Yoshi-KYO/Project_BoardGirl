#include "GameObject.h"
#include "RendererComponent.h"

CGameObject::CGameObject()
    : m_bDestroy(false)
    , m_eCollisionType(Collision::None)
    , m_eTag(Tag::None)
{
    m_tParam.m_f3Pos = { 0.0f, 0.0f, 0.0f };
    m_tParam.m_f3Size = { 1.0f, 1.0f, 1.0f };
    m_tParam.m_f3Rotate = { 0.0f, 0.0f, 0.0f };
    m_tParam.m_f4Color = { 1.0f, 1.0f, 1.0f, 1.0f };
    m_tParam.m_f2UVPos = { 0.0f, 0.0f };
    m_tParam.m_f2UVSize = { 1.0f, 1.0f };
}

CGameObject::~CGameObject()
{
}

void CGameObject::Init()
{

}

void CGameObject::Uninit()
{
	for (auto comp : m_pComponent_List)
	{
		comp->Uninit();
		delete comp;
	}
	m_pComponent_List.clear();
}

void CGameObject::Update()
{
	for (auto comp : m_pComponent_List)
	{
		comp->Update();
	}
}

void CGameObject::Draw()
{
	for (auto comp : m_pComponent_List)
	{
		if (dynamic_cast<CRendererComponent*>(comp))dynamic_cast<CRendererComponent*>(comp)->SetRendererParam(m_tParam);
		comp->Draw();
	}	
}

void CGameObject::OnColliderHit()
{

}

void CGameObject::OnDestroy()
{

}

void CGameObject::Destroy()
{
	m_bDestroy = true;
}

bool CGameObject::IsDestroy()
{
	return m_bDestroy;
}
