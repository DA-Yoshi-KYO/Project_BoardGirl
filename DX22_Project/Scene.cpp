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
	for (auto& list : m_pGameObject_List)
	{
		for (auto& obj : list)
		{
			obj->Uninit();
		}
		list.clear();
	}
}

void CScene::Update()
{
	CCamera::GetInstance(CCamera::GetCameraKind())->Update();


	for (auto& list : m_pGameObject_List)
	{
		for (auto& obj : list)
		{
			obj->Update();
		}
	}

	//for (int i = 0; i < m_pCollider_Vec.size(); i++)
	//{
	//	for (int j = i + 1; j < m_pCollider_Vec.size(); j++)
	//	{	
	//		if (m_pCollider_Vec[i]->CheckHit(m_pCollider_Vec[j]))
	//		{
	//			m_pCollider_Vec[i]->GetGameObject()->OnColliderHit();
	//			m_pCollider_Vec[j]->GetGameObject()->OnColliderHit();
	//			break;
	//		}
	//	}
	//}

	//for (int i = 0; i < m_pCollider_Vec.size(); i++)
	//{
	//	if (m_pCollider_Vec[i]->GetGameObject()->IsDestroy())
	//	{
	//		m_pCollider_Vec.erase(m_pCollider_Vec.begin() + i);
	//	}
	//}

	for (auto& list : m_pGameObject_List)
	{
		list.remove_if([](CGameObject* pObj) { return pObj->IsDestroy(); });
	}
}

void CScene::Draw()
{
	CCamera* pCamera = CCamera::GetInstance(CCamera::GetCameraKind()).get();
	Geometory::SetView(pCamera->GetViewMatrix());
	Geometory::SetProjection(pCamera->GetProjectionMatrix());


	for (auto& list : m_pGameObject_List)
	{
		list.sort([](CGameObject* a, CGameObject* b)
			{
				DirectX::XMFLOAT3 posA = a->PosAccessor();
				DirectX::XMVECTOR vecA = DirectX::XMLoadFloat3(&posA);
				DirectX::XMFLOAT3 posB = b->PosAccessor();
				DirectX::XMVECTOR vecB = DirectX::XMLoadFloat3(&posB);
				DirectX::XMFLOAT3 posCamera = CCamera::GetInstance(CCamera::GetCameraKind())->GetPos();
				DirectX::XMVECTOR vecCamera = DirectX::XMLoadFloat3(&posCamera);
				DirectX::XMVECTOR disCamA = DirectX::XMVectorSubtract(vecA, vecCamera);
				DirectX::XMVECTOR disCamB = DirectX::XMVectorSubtract(vecB, vecCamera);
				float disA = DirectX::XMVectorGetX(DirectX::XMVector3Length(vecA));;
				float disB = DirectX::XMVectorGetX(DirectX::XMVector3Length(vecB));;

				return disA > disB;
			});
		for (auto& obj : list)
		{
			obj->Draw();
		}
	}
}
