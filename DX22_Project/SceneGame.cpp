// インクルード部
#include "SceneGame.h"
#include "Camera.h"
#include "Field.h"
#include "Player.h"
#include "Geometory.h"
#include "BillboardRenderer.h"
#include "EnemyGenerater.h"
#include "Timer.h"
#include "Score.h"
#include "BGMPlayer.h"
#include "SkyBox.h"
#include "SpriteRenderer.h"
#include "Oparation.h"

void CSceneGame::Init()
{


    // カメラの設定をインゲームモードに変更
    CCamera::SetCameraKind(CAM_PLAYER);

    AddGameObject<CPlayer>("Player", Tag::GameObject);
    AddGameObject<CTimer>("Timer", Tag::UI);
    AddGameObject<CScore>("Score", Tag::UI);
    AddGameObject<CField>("Field", Tag::Field);
    AddGameObject<CSkyBox>("SkyBox", Tag::SkyBox);

    CEnemyGenerater::GetInstance()->GenerateEnemy("Dragon", DirectX::XMFLOAT3(0.0f, 2.0f, 0.0f));
    CBGMPlayer* pPlayer = AddGameObject<CBGMPlayer>("BGM", Tag::Sound);
    pPlayer->Load(AUDIO_PATH("BGM/GameBGM.wav"));
    pPlayer->SetVolume(0.1f);
    pPlayer->Play();

    m_fTime = 0.0f;
    m_nLastSpawnTime = 0;
}

void CSceneGame::Update()
{
    GenerateSystem();
    CScene::Update();
}

void CSceneGame::Draw()
{
    CCamera* pCamera = CCamera::GetInstance().get();
    Geometory::SetView(pCamera->GetViewMatrix());
    Geometory::SetProjection(pCamera->GetProjectionMatrix());

    int i = 0;
    for (auto& list : m_pGameObject_List)
    {
        if (i != (int)Tag::UI)
        {
            list.sort([](CGameObject* a, CGameObject* b)
                {
                    DirectX::XMFLOAT3 posA = a->AccessorPos();
                    DirectX::XMVECTOR vecA = DirectX::XMLoadFloat3(&posA);
                    DirectX::XMFLOAT3 posB = b->AccessorPos();
                    DirectX::XMVECTOR vecB = DirectX::XMLoadFloat3(&posB);
                    DirectX::XMFLOAT3 posCamera = CCamera::GetInstance()->GetPos();
                    DirectX::XMVECTOR vecCamera = DirectX::XMLoadFloat3(&posCamera);
                    DirectX::XMVECTOR disCamA = DirectX::XMVectorSubtract(vecA, vecCamera);
                    DirectX::XMVECTOR disCamB = DirectX::XMVectorSubtract(vecB, vecCamera);
                    float disA = DirectX::XMVectorGetX(DirectX::XMVector3Length(disCamA));;
                    float disB = DirectX::XMVectorGetX(DirectX::XMVector3Length(disCamB));;

                    return disA > disB;
                });
        }
        for (auto obj : list)
        {
            // UIはカメラと関係なく描画する
            switch (i)
            {
            case (int)Tag::Field:
            case (int)Tag::SkyBox:
            case (int)Tag::UI:
                obj->Draw();
                break;
            default:
                // 通常のオブジェクトはチャンク内にあるかチェックして描画する
                DirectX::XMFLOAT3 objPos = obj->AccessorPos();
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
                            obj->Draw();
                        }
                    }
                }
                break;
            }
        }
        i++;
    }
}

void CSceneGame::GenerateSystem()
{
    m_fTime += fDeltaTime;

    if ((int)m_fTime % 10 == 0 && (int)m_fTime != m_nLastSpawnTime)
    {
        if ((int)m_fTime % 60 == 0)
        {
            CEnemyGenerater::GetInstance()->GenerateEnemy("Dragon", DirectX::XMFLOAT3(0.0f, 2.0f, 0.0f));
        }
        for (int i = 0; i < 5 * ((int)m_fTime / 60 + 1); i++)
        {
            int rundom = rand() % 2;
            switch (rundom)
            {
            case 0:
                CEnemyGenerater::GetInstance()->GenerateEnemy("Slime", DirectX::XMFLOAT3(GetRandOfRange(-20,20), 2.0f, GetRandOfRange(-20, 20)));
                break;
            case 1:
                CEnemyGenerater::GetInstance()->GenerateEnemy("Ghost", DirectX::XMFLOAT3(GetRandOfRange(-20, 20), 2.0f, GetRandOfRange(-20, 20)));
                break;
            default:
                break;
            }
        }

        m_nLastSpawnTime = (int)m_fTime;
    }
}
