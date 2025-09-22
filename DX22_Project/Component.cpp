#include "Component.h"

CComponent::CComponent(CGameObject* inGameObject)
    : m_pGameObject(nullptr)
{
    m_pGameObject = inGameObject;
}
CComponent::~CComponent()
{
}

void CComponent::Init()
{

}

void CComponent::Uninit()
{

}

void CComponent::Update()
{

}

void CComponent::Draw()
{

}
