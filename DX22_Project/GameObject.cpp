#include "GameObject.h"
#include "RendererComponent.h"

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