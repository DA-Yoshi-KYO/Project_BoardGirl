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
	}
    m_pGameObject_List.clear();
}

void CScene::Update()
{
    CCamera::GetInstance(CCamera::GetCameraKind())->Update();


    for (auto& list : m_pGameObject_List)
    {
        list->Update();
    }

    m_pGameObject_List.remove_if([](CGameObject* pObj) { return pObj->IsDestroy(); });
}

void CScene::Draw()
{
    CCamera* pCamera = CCamera::GetInstance(CCamera::GetCameraKind()).get();
    Geometory::SetView(pCamera->GetViewMatrix());
    Geometory::SetProjection(pCamera->GetProjectionMatrix());


    m_pGameObject_List.sort([](CGameObject* a, CGameObject* b)
        {
            DirectX::XMFLOAT3 posA = a->AccessorPos();
            DirectX::XMVECTOR vecA = DirectX::XMLoadFloat3(&posA);
            DirectX::XMFLOAT3 posB = b->AccessorPos();
            DirectX::XMVECTOR vecB = DirectX::XMLoadFloat3(&posB);
            DirectX::XMFLOAT3 posCamera = CCamera::GetInstance(CCamera::GetCameraKind())->GetPos();
            DirectX::XMVECTOR vecCamera = DirectX::XMLoadFloat3(&posCamera);
            DirectX::XMVECTOR disCamA = DirectX::XMVectorSubtract(vecA, vecCamera);
            DirectX::XMVECTOR disCamB = DirectX::XMVectorSubtract(vecB, vecCamera);
            float disA = DirectX::XMVectorGetX(DirectX::XMVector3Length(vecA));;
            float disB = DirectX::XMVectorGetX(DirectX::XMVector3Length(vecB));;

            return disA > disB;
        });

    for (auto& list : m_pGameObject_List)
    {
        // UIはカメラと関係なく描画する
        Tag objTag = list->AccessorTag();
        if (objTag == Tag::UI)
        {
            list->Draw();
            continue;
        }
        // 通常のオブジェクトはチャンク内にあるかチェックして描画する
        DirectX::XMFLOAT3 objPos = list->AccessorPos();
        DirectX::XMFLOAT3 camPos = pCamera->GetPos();
        DirectX::XMVECTOR vecCamPos = DirectX::XMLoadFloat3(&camPos);
        DirectX::XMVECTOR chanckSize = DirectX::XMLoadFloat3(&ChunkSize);
        chanckSize = DirectX::XMVectorScale(chanckSize, 0.5f);
        DirectX::XMVECTOR vMaxB = DirectX::XMVectorAdd(vecCamPos, chanckSize);
        DirectX::XMVECTOR vMinB = DirectX::XMVectorSubtract(vecCamPos, chanckSize);
        DirectX::XMFLOAT3 maxB, minB;
        DirectX::XMStoreFloat3(&maxB, vMaxB);
        DirectX::XMStoreFloat3(&minB, vMinB);
        if (objPos.x >= minB.x && objPos.x <= maxB.x)
        {
            if (objPos.y >= minB.y && objPos.y <= maxB.y)
            {
                if (objPos.z >= minB.z && objPos.z <= maxB.z)
                {
                    list->Draw();
                }
            }
        }
    }
}

