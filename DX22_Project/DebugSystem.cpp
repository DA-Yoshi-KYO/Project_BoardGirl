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
    ImGui::ShowDemoWindow();

    DrawHierarchy();


    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void CDebugSystem::DrawHierarchy()
{
    ImGui::SetNextWindowPos(ImVec2(20, 20));
    ImGui::SetNextWindowSize(ImVec2(280, 300));
    ImGui::Begin("Hierarchy");
    ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(250, 100), ImGuiWindowFlags_NoTitleBar);

    auto Objects = GetScene()->GetNameList();

    for (auto itr : Objects)
    {
        ImGui::Button(itr.c_str());
    }

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
