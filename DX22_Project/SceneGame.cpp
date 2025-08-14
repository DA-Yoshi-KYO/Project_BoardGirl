// インクルード部
#include "SceneGame.h"
#include "Camera.h"
#include "Field.h"
#include "Player.h"
#include "Geometory.h"
#include "BillboardRenderer.h"
#include "EnemyGenerater.h"
#include "Timer.h"
#include "BGMPlayer.h"

void CSceneGame::Init()
{
    // シーンで使用するテクスチャの読み込み
    CBillboardRenderer::Load(TEXTURE_PATH("Jobs.png"), "Player");
    CBillboardRenderer::Load(TEXTURE_PATH("Slime.png"), "Slime");
    CBillboardRenderer::Load(TEXTURE_PATH("HPBar.jpg"), "HPBar");
    CBillboardRenderer::Load(TEXTURE_PATH("Number.png"), "Number");
    CBillboardRenderer::Load(TEXTURE_PATH("Ghost.png"), "Ghost");
    CBillboardRenderer::Load(TEXTURE_PATH("Dragon.png"), "Dragon");
    CBillboardRenderer::Load(TEXTURE_PATH("Effect/SwordNormalSkill.png"), "SwordNormalAttack");
    CBillboardRenderer::Load(TEXTURE_PATH("Effect/SwordQSkill.png"), "SwordQSkill");
    CBillboardRenderer::Load(TEXTURE_PATH("Effect/SwordESkill.png"), "SwordESkill");
    CBillboardRenderer::Load(TEXTURE_PATH("Effect/SwordRSkill.png"), "SwordRSkill");
    CBillboardRenderer::Load(TEXTURE_PATH("Effect/PlayerAttackHit.png"), "PlayerAttackHit");

    // カメラの設定をインゲームモードに変更
	CCamera::SetCameraKind(CAM_PLAYER);

    // オブジェクトの追加
    AddGameObject<CPlayer>();
    AddGameObject<CTimer>(Tag::UI);
    CBGMPlayer* pPlayer = AddGameObject<CBGMPlayer>(Tag::Sound);
    pPlayer->Load(AUDIO_PATH("BGM/GameBGM.wav"));
    pPlayer->SetVolume(0.1f);
    pPlayer->Play();
    //AddGameObject<CField>(Collision::None,Tag::Field);

    CEnemyGenerater::GetInstance()->GenerateEnemy("Slime", DirectX::XMFLOAT3(0.0f, 0.0f, 10.0f));
    CEnemyGenerater::GetInstance()->GenerateEnemy("Slime", DirectX::XMFLOAT3(0.0f, 0.0f, 20.0f));
    CEnemyGenerater::GetInstance()->GenerateEnemy("Ghost", DirectX::XMFLOAT3(0.0f, 0.0f, 30.0f));
    CEnemyGenerater::GetInstance()->GenerateEnemy("Ghost", DirectX::XMFLOAT3(0.0f, 0.0f, -10.0f));
    CEnemyGenerater::GetInstance()->GenerateEnemy("Slime", DirectX::XMFLOAT3(0.0f, 0.0f, -20.0f));
    CEnemyGenerater::GetInstance()->GenerateEnemy("Dragon", DirectX::XMFLOAT3(20.0f, 0.0f, 0.0f));
}

void CSceneGame::Draw()
{
    CCamera* pCamera = CCamera::GetInstance(CCamera::GetCameraKind()).get();
    Geometory::SetView(pCamera->GetViewMatrix());
    Geometory::SetProjection(pCamera->GetProjectionMatrix());

    for (auto& list : m_pGameObject_List)
    {
        list.sort([](CGameObject* a, CGameObject* b)
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
        for (auto obj : list)
        {
            // UIはカメラと関係なく描画する
            Tag objTag = obj->AccessorTag();
            if (objTag == Tag::UI || objTag == Tag::Field)
            {
                obj->Draw();
                continue;
            }
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
        }
    }

    for (int i = 0; i < m_pCollisionVec.size(); i++)
    {
        m_pCollisionVec[i]->Draw();
    }
}
