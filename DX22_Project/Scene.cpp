#include "GameObject.h"
#include "Scene.h"
#include "Camera.h"
#include "Geometory.h"

CScene::~CScene()
{

}

void CScene::Init()
{

}

void CScene::Uninit()
{
	for (auto list : m_pGameObject_List)
	{
        for (auto obj : list)
        {
            obj->Uninit();
            delete obj;
        }
        list.clear();
	}

    m_tIDVec.clear();
    m_pCollisionVec.clear();
}

void CScene::Update()
{
    for (auto& list : m_pGameObject_List)
    {
        for (auto obj : list)
        {
            obj->Update();
        }
    }

    for (int i = 0; i < m_pCollisionVec.size(); i++)
    {
        CCollisionBase* pCollisionA = m_pCollisionVec[i];
        if (!pCollisionA->AccessorActive()) continue;
        for (int j = i + 1; j < m_pCollisionVec.size(); j++)
        {
            CCollisionBase* pCollisionB = m_pCollisionVec[j];
            if (!pCollisionB->AccessorActive()) continue;
            if (pCollisionA->GetCollisionKind() != pCollisionB->GetCollisionKind()) continue;

            if (pCollisionA->IsHit(pCollisionB))
            {
                CGameObject* pObjA = pCollisionA->GetGameObject();
                CGameObject* pObjB = pCollisionB->GetGameObject();
                pObjA->OnColliderHit(pCollisionB, pCollisionA->AccessorTag());
                pObjB->OnColliderHit(pCollisionA, pCollisionB->AccessorTag());
            }
        }
    }

    for (int i = 0; i < m_pCollisionVec.size(); i++)
    {
        if (!m_pCollisionVec[i]) continue;
        if (m_pCollisionVec[i]->GetGameObject()->IsDestroy())
        {
            m_pCollisionVec.erase(m_pCollisionVec.begin() + i);
        }
    }

    for (auto& list : m_pGameObject_List)
    {
        list.remove_if([](CGameObject* pObj)
            {
                bool bDestroy = pObj->IsDestroy();
                if (bDestroy) pObj->OnDestroy();
                return pObj->IsDestroy();
            });

    }
}

void CScene::Draw()
{
    CCamera* pCamera = CCamera::GetInstance(CCamera::GetCameraKind()).get();
    Geometory::SetView(pCamera->GetViewMatrix());
    Geometory::SetProjection(pCamera->GetProjectionMatrix());

    for (auto& list : m_pGameObject_List)
    {
        for (auto obj : list)
        {
            obj->Draw();
        }
    }

     for (int i = 0; i < m_pCollisionVec.size(); i++)
    {
        m_pCollisionVec[i]->Draw();
    }
}

void CScene::DequeCollision(CGameObject* inThis)
{
    for (int i = 0; i < m_pCollisionVec.size(); i++)
    {
        if (m_pCollisionVec[i]->GetGameObject() == inThis)
        {
            m_pCollisionVec.erase(m_pCollisionVec.begin() + i);
        }
    }
}

std::array<std::list<CGameObject*>, (int)Tag::Max> CScene::GetGameObjectList()
{
    return m_pGameObject_List;
}
