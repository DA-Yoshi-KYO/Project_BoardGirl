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
#include "Transition.h"

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
CTransition* g_pTransition;
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
	g_pTransition = new CTransition();
	g_pTransition->Init();
	FadeIn(nullptr);

	return hr;
}

void Uninit()
{
	g_pScene->Uninit();
	delete g_pScene;
	g_pScene = nullptr;
	g_pTransition->Uninit();
	delete g_pTransition;
	g_pTransition = nullptr;

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
		}

		CCamera* pCamera = CCamera::GetInstance().get();
		pCamera->Update();
		g_pScene->Update();
		g_pTransition->Update();
	}

	if (IsKeyPress('U'))
	{
		if (IsKeyTrigger('I'))
		{
			g_bDebugMode ^= true;
		}
	}
	CDebugSystem::GetInstance()->Update();
}

void Draw()
{
	BeginDrawDirectX();

	g_pScene->Draw();
	g_pTransition->Draw();
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

void FadeIn(std::function<void()> onFadeComplete)
{
	g_pTransition->FadeIn(50, onFadeComplete);
}

void FadeOut(std::function<void()> onFadeComplete)
{
	g_pTransition->FadeOut(50, onFadeComplete);
}

bool IsDebugMode()
{
	return g_bDebugMode;
}
