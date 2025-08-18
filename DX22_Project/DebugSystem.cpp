#include "DebugSystem.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "DirectX.h"
#include "Main.h"

CDebugSystem* CDebugSystem::m_pInstance = nullptr;
constexpr float ce_fCharaSize = 30.0f;

CDebugSystem::CDebugSystem()
    : m_pObject(nullptr)
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
        int nChildCnt = 0;
        ObjectID id = m_pObject->AccessorID();
        std::string name = id.m_sName;
        if (id.m_nSameCount != 0) name += std::to_string(id.m_nSameCount);
        name = "Name:" + name;
        ImGui::BeginChild(ImGui::GetID((void*)nChildCnt), ImVec2(250, ce_fCharaSize), ImGuiWindowFlags_NoTitleBar);
        nChildCnt++;
        ImGui::Text(name.c_str());
        ImGui::EndChild();

        std::list<CRendererComponent*> pRenderer = m_pObject->GetSameComponents<CRendererComponent>();
        int nCompCnt = 0;
        if (!pRenderer.empty())
        {
            for (auto itr : pRenderer)
            {
                RendererParam param = itr->GetRendererParam();
                ImGui::BeginChild(ImGui::GetID((void*)nChildCnt), ImVec2(250, ce_fCharaSize * 9), ImGuiWindowFlags_NoTitleBar);

                ImGui::Text(std::string("[Position" + std::to_string(nCompCnt) + "]").c_str());
                DirectX::XMFLOAT3 pos = param.m_f3Pos;
                ImGui::Text(std::string("PosX:" + std::to_string(pos.x)).c_str());
                ImGui::Text(std::string("PosY:" + std::to_string(pos.y)).c_str());
                ImGui::Text(std::string("PosZ:" + std::to_string(pos.z)).c_str());
                ImGui::Text("\n");

                ImGui::Text(std::string("[Size" + std::to_string(nCompCnt) + "]").c_str());
                DirectX::XMFLOAT3 size = param.m_f3Size;
                ImGui::Text(std::string("SizeX:" + std::to_string(size.x)).c_str());
                ImGui::Text(std::string("SizeY:" + std::to_string(size.y)).c_str());
                ImGui::Text(std::string("SizeZ:" + std::to_string(size.z)).c_str());
                ImGui::Text("\n");

                ImGui::Text(std::string("[Rotation" + std::to_string(nCompCnt) + "]").c_str());
                DirectX::XMFLOAT3 rotate = param.m_f3Rotate;
                ImGui::Text(std::string("RotateX:" + std::to_string(rotate.x)).c_str());
                ImGui::Text(std::string("RotateY:" + std::to_string(rotate.y)).c_str());
                ImGui::Text(std::string("RotateZ:" + std::to_string(rotate.z)).c_str());

                ImGui::EndChild();
                nChildCnt++;
                nCompCnt++;
            }
        }
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
