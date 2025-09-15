#include "DebugSystem.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "DirectX.h"
#include "Main.h"
#include "Camera.h"
#include "Oparation.h"

#include "SceneTitle.h"
#include "SceneJobSelect.h"
#include "SceneGame.h"
#include "SceneResult.h"

#include "Input.h"

CDebugSystem* CDebugSystem::m_pInstance = nullptr;
constexpr float ce_fCharaSize = 30.0f;

CDebugSystem::CDebugSystem()
    : m_pObject(nullptr), m_bUpdate(true), m_bCollision(true)
{

}

CDebugSystem::~CDebugSystem()
{

}

void CDebugSystem::Init()
{
    m_pObject = nullptr;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplWin32_Init(GetMyWindow());
    ImGui_ImplDX11_Init(GetDevice(), GetContext());
}

void CDebugSystem::Uninit()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void CDebugSystem::Update()
{
    if (!m_bUpdate) CCamera::GetInstance(CCamera::GetCameraKind())->Update();
}

void CDebugSystem::Draw()
{
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    DrawHierarchy();
    DrawCameraParam();
    DrawUpdateTick();
    DrawSceneSelect();
    DrawCollision();
    DrawMousePos();
    DrawFPS();
    if (m_pObject) m_pObject->Inspecter();

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void CDebugSystem::DrawHierarchy()
{
    ImGui::SetNextWindowPos(ImVec2(20, 20));
    ImGui::SetNextWindowSize(ImVec2(280, 300));
    ImGui::Begin("Hierarchy");
    ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(250, 260), ImGuiWindowFlags_NoTitleBar);

    auto Objects = GetScene()->GetIDVec();

    std::list<ObjectID> objectIDList{};
    for (auto Id : Objects)
    {
        objectIDList.push_back(Id);
    }

    objectIDList.sort([](ObjectID a, ObjectID b)
        {
            return a.m_nSameCount < b.m_nSameCount;
        });

    objectIDList.sort([](ObjectID a, ObjectID b)
        {
            return a.m_sName < b.m_sName;
        });

    for (auto itr = objectIDList.begin(); itr != objectIDList.end();)
    {
        std::string name = itr->m_sName;

        int nItrCount = 0;
        for (auto idItr : objectIDList)
        {
            if (idItr.m_sName == name)
            {
                nItrCount++;
            }
        }
        ObjectID id;
        id.m_sName = name;

            if (ImGui::CollapsingHeader(std::string("[" + name + "]").c_str()))
            {
                for (int i = 0; i < nItrCount; i++)
                {
                    std::string sButtonName = name;
                    if (i != 0) sButtonName += std::to_string(i);
                    id.m_nSameCount = i;
                    if (ImGui::Button(sButtonName.c_str()))
                    {
                        m_pObject = GetScene()->GetGameObject(id);
                    }

                }

            }
        

        std::advance(itr, nItrCount);
    }

    ImGui::EndChild();
    ImGui::End();
}

void CDebugSystem::DrawCameraParam()
{
    CCamera* pCamera = CCamera::GetInstance(CCamera::GetCameraKind()).get();
    CScene* pScene = GetScene();

    if (dynamic_cast<CSceneGame*>(pScene))pCamera->SetCameraKind(CAM_PLAYER);
    else if (dynamic_cast<CSceneJobSelect*>(pScene))pCamera->SetCameraKind(CAM_SELECT);

    if (!pCamera) return;
    if (m_bUpdate) return;
    pCamera->SetCameraKind(CAM_DEBUG);
    ImGui::SetNextWindowPos(ImVec2(20, SCREEN_HEIGHT - 400));
    ImGui::SetNextWindowSize(ImVec2(280, 180));
    ImGui::Begin("Camera");
    ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(250, 160), ImGuiWindowFlags_NoTitleBar);


    if (ImGui::CollapsingHeader(std::string("[Transform]").c_str()))
    {
        ImGui::Text(std::string("Position").c_str());
        DirectX::XMFLOAT3 pos = pCamera->GetPos();
        ImGui::Text(std::string("PosX:" + std::to_string(pos.x)).c_str());
        ImGui::Text(std::string("PosY:" + std::to_string(pos.y)).c_str());
        ImGui::Text(std::string("PosZ:" + std::to_string(pos.z)).c_str());
        ImGui::Text("\n");

        ImGui::Text(std::string("Look").c_str());
        DirectX::XMFLOAT3 look = pCamera->GetLook();
        ImGui::Text(std::string("LookX:" + std::to_string(look.x)).c_str());
        ImGui::Text(std::string("LookY:" + std::to_string(look.y)).c_str());
        ImGui::Text(std::string("LookZ:" + std::to_string(look.z)).c_str());
        ImGui::Text("\n");

        ImGui::Text(std::string("UpVector").c_str());
        DirectX::XMFLOAT3 up = pCamera->GetUp();
        ImGui::Text(std::string("UpX:" + std::to_string(up.x)).c_str());
        ImGui::Text(std::string("UpY:" + std::to_string(up.y)).c_str());
        ImGui::Text(std::string("UpZ:" + std::to_string(up.z)).c_str());
    }


    ImGui::EndChild();
    ImGui::End();
}

void CDebugSystem::DrawUpdateTick()
{
    ImGui::SetNextWindowPos(ImVec2(20,SCREEN_HEIGHT - 120));
    ImGui::SetNextWindowSize(ImVec2(280, 100));
    ImGui::Begin("UpdateTick");

    ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(ce_f2InspecterSize), ImGuiWindowFlags_NoTitleBar);
    ImGui::Checkbox("Use Update", &m_bUpdate);
    ImGui::EndChild();

    if (!m_bUpdate)
    {
        ImGui::BeginChild(ImGui::GetID((void*)1), ImVec2(ce_f2InspecterSize), ImGuiWindowFlags_NoTitleBar);
        if (ImGui::Button("Step"))
        {
            GetScene()->Update();
        }
        ImGui::EndChild();
    }

    ImGui::End();
}

void CDebugSystem::DrawSceneSelect()
{
    ImGui::SetNextWindowPos(ImVec2(20, SCREEN_HEIGHT - 220));
    ImGui::SetNextWindowSize(ImVec2(280, 100));
    ImGui::Begin("Scene");

    ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(ce_f2InspecterSize), ImGuiWindowFlags_NoTitleBar);
    static int nSelect = 0;
    ImGui::Combo("kind", &nSelect, "Title\0JobSelect\0Game\0Result\0");
    ImGui::EndChild();

    if (ImGui::Button("Go"))
    {
        switch (nSelect)
        {
        case 0:
            ChangeScene(new CSceneTitle());
            break;
        case 1:
            ChangeScene(new CSceneJobSelect());
            break;
        case 2:
            ChangeScene(new CSceneGame());
            break;
        case 3:
            ChangeScene(new CSceneResult());
            break;
        default:
            break;
        }
    }

    ImGui::End();
}

void CDebugSystem::DrawCollision()
{
    ImGui::SetNextWindowPos(ImVec2(SCREEN_WIDTH - 300, SCREEN_HEIGHT - 120));
    ImGui::SetNextWindowSize(ImVec2(280, 100));
    ImGui::Begin("Collision");

    ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(ce_f2InspecterSize), ImGuiWindowFlags_NoTitleBar);
    ImGui::Checkbox("DrawCollision", &m_bCollision);
    ImGui::EndChild();
    ImGui::End();
    if (!m_bCollision)return;

    auto CollisionVec = GetScene()->GetCollisionVec();
    for (int i = 0; i < CollisionVec.size(); i++)
    {
        CollisionVec[i]->Draw();
    }
}

void CDebugSystem::DrawMousePos()
{
    ImGui::SetNextWindowPos(ImVec2(SCREEN_WIDTH / 2 - 140, 20.0f));
    ImGui::SetNextWindowSize(ImVec2(280, 70));
    ImGui::Begin("Mouse");
    ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(ce_f2InspecterSize), ImGuiWindowFlags_NoTitleBar);

    POINT mousePos = *GetMousePosition();
    ImGui::Text(std::string("MouseX:" + std::to_string(mousePos.x)).c_str());
    ImGui::SameLine();
    ImGui::Text(std::string("MouseY:" + std::to_string(mousePos.y)).c_str());

    ImGui::EndChild();
    ImGui::End();
}

void CDebugSystem::DrawFPS()
{
    ImGui::SetNextWindowPos(ImVec2(SCREEN_WIDTH / 2 + 170, 20.0f));
    ImGui::SetNextWindowSize(ImVec2(140, 70));
    ImGui::Begin("FPS");
    ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(120.0f,30.0f), ImGuiWindowFlags_NoTitleBar);

    int fps = GetFPS();
    ImGui::Text(std::string("FPS:" + std::to_string(fps)).c_str());
    
    ImGui::EndChild();
    ImGui::End();
}

CDebugSystem* CDebugSystem::GetInstance()
{
    if (m_pInstance == nullptr)
    {
        m_pInstance = new CDebugSystem();
    }
    return m_pInstance;
}

void CDebugSystem::ReleaseInstance()
{
    if (m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }
}

void CDebugSystem::ReleaseGameObject()
{
    m_pObject = nullptr;
}
