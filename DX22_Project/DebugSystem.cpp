#include "DebugSystem.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "DirectX.h"
#include "Main.h"
#include "Camera.h"
#include "Oparation.h"

CDebugSystem* CDebugSystem::m_pInstance = nullptr;
constexpr float ce_fCharaSize = 30.0f;

CDebugSystem::CDebugSystem()
    : m_pObject(nullptr), m_bUpdate(true)
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

}

void CDebugSystem::Draw()
{
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    DrawHierarchy();
    if (m_pObject) m_pObject->Inspecter();
    //DrawCameraParam();
    DrawUpdateTick();

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void CDebugSystem::DrawHierarchy()
{
    ImGui::SetNextWindowPos(ImVec2(20, 20));
    ImGui::SetNextWindowSize(ImVec2(280, 300));
    ImGui::Begin("Hierarchy");
    ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(250, 280), ImGuiWindowFlags_NoTitleBar);

    auto Objects = GetScene()->GetGameObjectList();

    std::list<ObjectID> objectIDList{};
    for (auto list : Objects)
    {
        for (auto obj : list)
        {
            objectIDList.push_back(obj->AccessorID());
        }
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

        if (ImGui::CollapsingHeader(std::string("[" + name + "]").c_str()))
        {
            for (int i = 0; i < nItrCount; i++)
            {
                std::string sButtonName = name;
                if (i != 0) sButtonName += std::to_string(i + 1);
                ObjectID id;
                id.m_sName = name;
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

    if (!pCamera) return;

    DirectX::XMFLOAT3 pos = pCamera->GetPos();
    DirectX::XMFLOAT3 look = pCamera->GetLook();
    pCamera->SetCameraKind(CameraKind::CAM_DEBUG);
    pCamera->SetPos(pos);
    pCamera->SetLook(look);

    ImGui::SetNextWindowPos(ImVec2(340, 20));
    ImGui::SetNextWindowSize(ImVec2(280, 300));
    ImGui::Begin("Camera");

    if (ImGui::CollapsingHeader(std::string("Position").c_str()))
    {
        DirectX::XMFLOAT3 pos = pCamera->GetPos();
        float value[3] = { pos.x,pos.y, pos.z };
        ImGui::SliderFloat3("pos", value, -1000.0f, 1000.0f);
        DirectX::XMFLOAT3 newPos = DirectX::XMFLOAT3(value[0], value[1], value[2]);
        pCamera->SetPos(newPos);
        pCamera->SetLook(pCamera->GetLook() - (newPos - pos));
    }

    if (ImGui::CollapsingHeader(std::string("Look").c_str()))
    {
        DirectX::XMFLOAT3 look = pCamera->GetLook();
        float value[3] = { look.x,look.y, look.z };
        ImGui::SliderFloat3("look", value, -1000.0f, 1000.0f);
    }

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
