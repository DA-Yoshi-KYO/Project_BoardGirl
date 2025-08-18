#include "DebugSystem.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "DirectX.h"
#include "Main.h"

CDebugSystem* CDebugSystem::m_pInstance = nullptr;

CDebugSystem::CDebugSystem()
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
    DrawInspecter();

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

    std::list<ObjectID> objectList{};
    for (auto itr : Objects)
    {
        for (auto obj : itr)
        {
            objectList.push_back(obj->AccessorID());
        }
    }

    objectList.sort([](ObjectID a, ObjectID b)
        {
            return a.m_sName < b.m_sName;
        });

    for (auto itr : objectList)
    {
        std::string name = itr.m_sName;
        if (itr.m_nSameCount != 0) name += std::to_string(itr.m_nSameCount);

        if (ImGui::Button(name.c_str()))
        {
            m_pObject = GetScene()->GetGameObject(itr);
        }
    }

    ImGui::EndChild();
    ImGui::End();
}

void CDebugSystem::DrawInspecter()
{
    ImGui::SetNextWindowPos(ImVec2(SCREEN_WIDTH - 300, 20));
    ImGui::SetNextWindowSize(ImVec2(280, 300));
    ImGui::Begin("Inspecter");

    if (m_pObject)
    {
        ObjectID id = m_pObject->AccessorID();
        std::string name = id.m_sName;
        if (id.m_nSameCount != 0) name += std::to_string(id.m_nSameCount);
        name = "Name:" + name;
        ImGui::Text(name.c_str());
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
