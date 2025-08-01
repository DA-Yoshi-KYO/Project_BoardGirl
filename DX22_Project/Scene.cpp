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
        list->Uninit();
        delete list;
	}

    m_pGameObject_List.clear();
    m_pCollisionVec.clear();
}

void CScene::Update()
{
    CCamera::GetInstance(CCamera::GetCameraKind())->Update();

    for (auto& list : m_pGameObject_List)
    {
        list->Update();
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
                pObjA->OnColliderHit(pCollisionB,pCollisionA->AccessorTag());
                pObjB->OnColliderHit(pCollisionA,pCollisionB->AccessorTag());
            }
        }
    }

    for (int i = 0; i < m_pCollisionVec.size(); i++)
    {
        if (m_pCollisionVec[i]->GetGameObject()->IsDestroy())
        {
            m_pCollisionVec.erase(m_pCollisionVec.begin() + i);
        }
    }
    m_pGameObject_List.remove_if([](CGameObject* pObj)
        {
            bool bDestroy = pObj->IsDestroy();
            if (bDestroy) pObj->OnDestroy();
            return bDestroy;
        });
}

void CScene::Draw()
{
    CCamera* pCamera = CCamera::GetInstance(CCamera::GetCameraKind()).get();
    Geometory::SetView(pCamera->GetViewMatrix());
    Geometory::SetProjection(pCamera->GetProjectionMatrix());

    for (auto& list : m_pGameObject_List)
    {
        list->Draw();
    }

    for (int i = 0; i < m_pCollisionVec.size(); i++)
    {
        m_pCollisionVec[i]->Draw();
    }
}
