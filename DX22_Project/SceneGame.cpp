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
#include "SkyBox.h"
#include "SpriteRenderer.h"

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
    CBillboardRenderer::Load(TEXTURE_PATH("Effect/WizardNormalSkill.png"), "WizardNormalAttack");
    //CBillboardRenderer::Load(TEXTURE_PATH("Effect/SwordRSkill.png"), "SwordRSkill");
    CBillboardRenderer::Load(TEXTURE_PATH("Effect/PlayerAttackHit.png"), "PlayerAttackHit");

    CBillboardRenderer::Load(TEXTURE_PATH("Effect/SlimeAttack.png"), "SlimeAttack");
    CBillboardRenderer::Load(TEXTURE_PATH("Effect/DragonNormalAttack.png"), "DragonNormalAttack");

    CSpriteRenderer::Load(TEXTURE_PATH("Circle.png"), "Circle");
    CSpriteRenderer::Load(TEXTURE_PATH("Frame.png"), "Frame");

    // カメラの設定をインゲームモードに変更
	CCamera::SetCameraKind(CAM_PLAYER);

    AddGameObject<CPlayer>("Player", Tag::GameObject);
    AddGameObject<CTimer>("Timer", Tag::UI);
    AddGameObject<CField>("Field",Tag::Field);
    AddGameObject<CSkyBox>("SkyBox",Tag::SkyBox);
    CEnemyGenerater::GetInstance()->GenerateEnemy("Slime", DirectX::XMFLOAT3(0.0f, 2.0f, 10.0f));
    CEnemyGenerater::GetInstance()->GenerateEnemy("Slime", DirectX::XMFLOAT3(0.0f, 2.0f, 20.0f));
    CEnemyGenerater::GetInstance()->GenerateEnemy("Ghost", DirectX::XMFLOAT3(0.0f, 2.0f, 30.0f));
    CEnemyGenerater::GetInstance()->GenerateEnemy("Ghost", DirectX::XMFLOAT3(0.0f, 2.0f, -10.0f));
    CEnemyGenerater::GetInstance()->GenerateEnemy("Slime", DirectX::XMFLOAT3(0.0f, 2.0f, -20.0f));
    CEnemyGenerater::GetInstance()->GenerateEnemy("Dragon", DirectX::XMFLOAT3(20.0f, 2.0f, 0.0f));
    CBGMPlayer* pPlayer = AddGameObject<CBGMPlayer>("BGM",Tag::Sound);
    pPlayer->Load(AUDIO_PATH("BGM/GameBGM.wav"));
    pPlayer->SetVolume(0.1f);
    pPlayer->Play();
}

void CSceneGame::Draw()
{
    CCamera* pCamera = CCamera::GetInstance(CCamera::GetCameraKind()).get();
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
                    DirectX::XMFLOAT3 posCamera = CCamera::GetInstance(CCamera::GetCameraKind())->GetPos();
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
