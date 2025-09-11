#include "Main.h"
#include "DirectX.h"

#include "Geometory.h"
#include "Sprite.h"
#include "Input.h"
#include "ShaderList.h"
#include "Audio.h"

#include "Scene.h"
#include "SceneTitle.h"
#include "SceneJobSelect.h"
#include "SceneGame.h"

#include "Defines.h"

#include "EnemyGenerater.h"
#include "DebugSystem.h"
#include "Camera.h"

#include "BillboardRenderer.h"
#include "SpriteRenderer.h"
#include "Sprite3DRenderer.h"
#include "ModelRenderer.h"

CScene* g_pScene;
CScene* g_pNextScene;
bool g_bSceneChanging = false;
bool g_bDebugMode = false;
CameraKind g_ekind;

HRESULT Init(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr;
	// DirectX初期化
	hr = InitDirectX(hWnd, width, height, false);
	// 初期化の例
	if (FAILED(hr)) { return hr; }

    CDebugSystem::GetInstance()->Init();
    CAudio::InitMaster();
	Geometory::Init();
	Sprite::Init();
	ShaderList::Init();
	InitInput();

	g_pScene = new CSceneTitle();
	g_pScene->Init();
    g_ekind = CCamera::GetCameraKind();

	return hr;
}

void Uninit()
{
	g_pScene->Uninit();
	delete g_pScene;
	g_pScene = nullptr;
    CEnemyGenerater::GetInstance()->ReleaseInstance();


	UninitInput();
	ShaderList::Uninit();
	Sprite::Uninit();
	Geometory::Uninit();
    CAudio::UninitMaster();
    CRendererComponent::UnLoad();
    CDebugSystem::GetInstance()->Uninit();
    CDebugSystem::GetInstance()->ReleaseInstance();

	UninitDirectX();
}

void Update()
{
	UpdateInput();
	srand(timeGetTime());

    if (CDebugSystem::GetInstance()->IsUpdate())
    {
        if (g_bSceneChanging)
        {
            CDebugSystem::GetInstance()->ReleaseGameObject();

            g_pScene->Uninit();
            delete g_pScene;
            g_pScene = g_pNextScene;
            g_pScene->Init();
            g_bSceneChanging = false;
            g_ekind = CCamera::GetCameraKind();
        }

        CCamera* pCamera = CCamera::GetInstance(CCamera::GetCameraKind()).get();
        pCamera->Update();
        g_pScene->Update();
    }

    if (IsKeyPress(VK_SPACE))
    {
        if (IsKeyTrigger(VK_RETURN))
        {
            if (!g_bDebugMode) g_ekind = CCamera::GetCameraKind();
            g_bDebugMode ^= true;
        }
    }
    CDebugSystem::GetInstance()->Update();
}

void Draw()
{
	BeginDrawDirectX();

	// 軸線の表示
#if 1
	// グリッド
	DirectX::XMFLOAT4 lineColor(0.5f, 0.5f, 0.5f, 1.0f);
	float size = DEBUG_GRID_NUM * DEBUG_GRID_MARGIN;
	for (int i = 1; i <= DEBUG_GRID_NUM; ++i)
	{
		float grid = i * DEBUG_GRID_MARGIN;
		DirectX::XMFLOAT3 pos[2] = {
			DirectX::XMFLOAT3(grid, 0.0f, size),
			DirectX::XMFLOAT3(grid, 0.0f,-size),
		};
		Geometory::AddLine(pos[0], pos[1], lineColor);
		pos[0].x = pos[1].x = -grid;
		Geometory::AddLine(pos[0], pos[1], lineColor);
		pos[0].x = size;
		pos[1].x = -size;
		pos[0].z = pos[1].z = grid;
		Geometory::AddLine(pos[0], pos[1], lineColor);
		pos[0].z = pos[1].z = -grid;
		Geometory::AddLine(pos[0], pos[1], lineColor);
	}
	// 軸
	Geometory::AddLine(DirectX::XMFLOAT3(0,0,0), DirectX::XMFLOAT3(size,0,0), DirectX::XMFLOAT4(1,0,0,1));
	Geometory::AddLine(DirectX::XMFLOAT3(0,0,0), DirectX::XMFLOAT3(0,size,0), DirectX::XMFLOAT4(0,1,0,1));
	Geometory::AddLine(DirectX::XMFLOAT3(0,0,0), DirectX::XMFLOAT3(0,0,size), DirectX::XMFLOAT4(0,0,1,1));
	Geometory::AddLine(DirectX::XMFLOAT3(0,0,0), DirectX::XMFLOAT3(-size,0,0),  DirectX::XMFLOAT4(0,0,0,1));
	Geometory::AddLine(DirectX::XMFLOAT3(0,0,0), DirectX::XMFLOAT3(0,0,-size),  DirectX::XMFLOAT4(0,0,0,1));

	Geometory::DrawLines();

	// カメラの値
	static bool camPosSwitch = false;
	if (IsKeyTrigger(VK_RETURN)) {
		camPosSwitch ^= true;
	}

	DirectX::XMVECTOR camPos;
	if (camPosSwitch) {
		camPos = DirectX::XMVectorSet(2.5f, 30.5f, -40.0f, 0.0f);
	}
	else {
		camPos = DirectX::XMVectorSet(2.5f, 3.5f, -4.0f, 0.0f);
	}

	// ジオメトリ用カメラ初期化
	DirectX::XMFLOAT4X4 mat[2];
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(
		DirectX::XMMatrixLookAtLH(
			camPos,
			DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
			DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
		)));
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixTranspose(
		DirectX::XMMatrixPerspectiveFovLH(
			DirectX::XMConvertToRadians(60.0f), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f)
	));
	Geometory::SetView(mat[0]);
	Geometory::SetProjection(mat[1]);
#endif
	g_pScene->Draw();
    if (g_bDebugMode) CDebugSystem::GetInstance()->Draw();

	EndDrawDirectX();
}

CScene* GetScene()
{
	return g_pScene;
}

void ChangeScene(CScene* inScene)
{
	g_pNextScene = inScene;
	g_bSceneChanging = true;
}

