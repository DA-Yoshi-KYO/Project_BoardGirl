#include "SelectJobs.h"
#include "Easing.h"
#include "Input.h"
#include "Main.h"
#include "SceneGame.h"
#include "Oparation.h"
#include "DebugSystem.h"

constexpr DirectX::XMINT2 ce_n2Split = { 6, 6 };
constexpr float ce_fRadius = 5.0f;
JobKind CSelectJobs::m_eSelectedJob = JobKind::Soldier;

enum class SEKind
{
    Decision,
    Select
};

void CSelectJobs::Init()
{
    m_eSelectedJob = JobKind::Soldier;

    m_tRendererParam[(int)JobKind::Soldier] = AddComponent<CBillboardRenderer>();
    m_tRendererParam[(int)JobKind::Soldier]->SetKey("Player");
    m_tJobsParam[(int)JobKind::Soldier].m_f2UVPos = { 0.0f / (float)ce_n2Split.x , 1.0f / (float)ce_n2Split.y };
    m_tRendererParam[(int)JobKind::Wizard] = AddComponent<CBillboardRenderer>();
    m_tRendererParam[(int)JobKind::Wizard]->SetKey("Player");
    m_tJobsParam[(int)JobKind::Wizard].m_f2UVPos = { 3.0f / (float)ce_n2Split.x , 1.0f / (float)ce_n2Split.y };
    m_tRendererParam[(int)JobKind::Fighter] = AddComponent<CBillboardRenderer>();
    m_tRendererParam[(int)JobKind::Fighter]->SetKey("Player");
    m_tJobsParam[(int)JobKind::Fighter].m_f2UVPos = { 1.0f / (float)ce_n2Split.x , 1.0f / (float)ce_n2Split.y };

    // 戦士の位置を初期値(手前)として、円状にキャラを配置する
    // 円の中心をXZ(0,0)とした時、各キャラの位置は
    // XZ = (0 + r * cos(θ) , 0 + r * sin(θ))となる

    for (int i = 0; i < (int)JobKind::Max; i++)
    {
        m_tJobsParam[i].m_f2UVSize = { 1.0f / (float)ce_n2Split.x, 1.0f / (float)ce_n2Split.y };
        m_tJobsParam[i].m_f3Pos.z = -(0.0f + ce_fRadius * cosf(DirectX::XMConvertToRadians((360.0f / (int)JobKind::Max) * i)));
        m_tJobsParam[i].m_f3Pos.x = 0.0f + ce_fRadius * sinf(DirectX::XMConvertToRadians((360.0f / (int)JobKind::Max) * i));
    }

    m_pSE.push_back(AddComponent<CAudio>());
    m_pSE[(int)SEKind::Decision]->Load(AUDIO_PATH("SE/Decision.wav"));
    m_pSE[(int)SEKind::Decision]->SetVolume(0.1f);

    m_pSE.push_back(AddComponent<CAudio>());
    m_pSE[(int)SEKind::Select]->Load(AUDIO_PATH("SE/Select.wav"));
    m_pSE[(int)SEKind::Select]->SetVolume(0.1f);

    m_bEnd = false;
    m_bTransition = false;
}

void CSelectJobs::Update()
{
    static float fTime = 0.0f;

    if (!m_bEnd)
    {
        if (!isMove)
        {
            fTime = 0.0f;
            m_tJobsParam[(int)m_eSelectedJob].m_f3Size = { 3.0f, 3.0f, 1.0f };
            for (int i = 0; i < (int)JobKind::Max; i++)
            {
                m_tTempParam[i] = m_tJobsParam[i];
            }

            int nSelect = (int)m_eSelectedJob;
            if (!isMove)
            {
                if (IsKeyTrigger(VK_RIGHT))
                {
                    m_pSE[(int)SEKind::Select]->Play();
                    nSelect++;
                    if (nSelect == (int)JobKind::Max)
                    {
                        nSelect = 0;
                    }
                    isNext = true;
                    isMove = true;
                }
                else if (IsKeyTrigger(VK_LEFT))
                {
                    m_pSE[(int)SEKind::Select]->Play();
                    nSelect--;
                    if (nSelect < 0)
                    {
                        nSelect = (int)JobKind::Max - 1;
                    }
                    isNext = false;
                    isMove = true;
                }
                else if (IsKeyTrigger(VK_SPACE))
                {
                    m_pSE[(int)SEKind::Decision]->Play();
                    m_bEnd = true;
                }
            }
            m_eSelectedJob = (JobKind)nSelect;
        }
        else
        {
            for (int i = 0; i < (int)JobKind::Max; ++i)
            {
                m_tJobsParam[i].m_f3Size = { 1.0f, 1.0f, 1.0f };
            }
            if (isNext)
            {
                for (int i = 0; i < (int)JobKind::Max; i++)
                {
                    int backIndex = (i - 1 + (int)JobKind::Max) % (int)JobKind::Max;
                    DirectX::XMFLOAT3 f3Disance = m_tTempParam[backIndex].m_f3Pos - m_tTempParam[i].m_f3Pos;
                    m_tJobsParam[i].m_f3Pos = (CEasing::EaseOutBack(fTime, 1.0f) * f3Disance) + m_tTempParam[i].m_f3Pos;
                }
            }
            else
            {
                for (int i = 0; i < (int)JobKind::Max; i++)
                {
                    int nextIndex = (i + 1) % (int)JobKind::Max;
                    DirectX::XMFLOAT3 f3Disance = m_tTempParam[nextIndex].m_f3Pos - m_tTempParam[i].m_f3Pos;
                    m_tJobsParam[i].m_f3Pos = (CEasing::EaseOutBack(fTime, 1.0f) * f3Disance) + m_tTempParam[i].m_f3Pos;
                }
            }

            if (fTime >= 1.0f)
            {
                isMove = false;
            }

            fTime += fDeltaTime;
        }
    }
    else
    {
        if (!m_pSE[(int)SEKind::Decision]->IsPlay() && !m_bTransition && m_bEnd)
        {
            m_bTransition = true;
            ChangeScene(new CSceneGame());
        }
    }
 
    CGameObject::Update();
}

void CSelectJobs::Draw()
{
    for (int i = 0; i < (int)JobKind::Max; ++i)
    {
        m_tRendererParam[i]->SetRendererParam(m_tJobsParam[i]);
        m_tRendererParam[i]->Draw();
    }
}

int CSelectJobs::Inspecter(bool isEnd)
{
    ImGui::SetNextWindowPos(ImVec2(SCREEN_WIDTH - 300, 20));
    ImGui::SetNextWindowSize(ImVec2(280, SCREEN_HEIGHT - 40));
    ImGui::Begin("Inspecter");

    int nChildCnt = 0;
    std::string name = m_tID.m_sName;
    if (m_tID.m_nSameCount != 0) name += std::to_string(m_tID.m_nSameCount);
    name = "Name:" + name;
    ImGui::BeginChild(ImGui::GetID((void*)nChildCnt), ImVec2(250, 30), ImGuiWindowFlags_NoTitleBar);
    ImGui::Text(name.c_str());
    ImGui::EndChild();
    nChildCnt++;

    std::string sJobName[(int)JobKind::Max] =
    {
        "Soldier",
        "Wizard",
        "Fighter",
    };

    for (int i = 0; i < (int)JobKind::Max; i++)
    {
        if (ImGui::CollapsingHeader(sJobName[i].c_str()))
        {
            ImGui::BeginChild(ImGui::GetID((void*)nChildCnt), ImVec2(ce_f2InspecterSize.x, ce_f2InspecterSize.y * 9), ImGuiWindowFlags_NoTitleBar);

            if (ImGui::CollapsingHeader(std::string("[Transform]").c_str()))
            {
                ImGui::BeginChild(ImGui::GetID((void*)nChildCnt), ImVec2(ce_f2InspecterSize.x, ce_f2InspecterSize.y * 9), ImGuiWindowFlags_NoTitleBar);

                RendererParam tParam = m_tRendererParam[i]->GetRendererParam();
                ImGui::Text(std::string("Position").c_str());
                DirectX::XMFLOAT3 pos = tParam.m_f3Pos;
                ImGui::Text(std::string("PosX:" + std::to_string(pos.x)).c_str());
                ImGui::Text(std::string("PosY:" + std::to_string(pos.y)).c_str());
                ImGui::Text(std::string("PosZ:" + std::to_string(pos.z)).c_str());
                ImGui::Text("\n");

                ImGui::Text(std::string("Size").c_str());
                DirectX::XMFLOAT3 size = tParam.m_f3Size;
                ImGui::Text(std::string("SizeX:" + std::to_string(size.x)).c_str());
                ImGui::Text(std::string("SizeY:" + std::to_string(size.y)).c_str());
                ImGui::Text(std::string("SizeZ:" + std::to_string(size.z)).c_str());
                ImGui::Text("\n");

                ImGui::Text(std::string("Rotation").c_str());
                DirectX::XMFLOAT3 rotate = tParam.m_f3Rotate;
                ImGui::Text(std::string("RotateX:" + std::to_string(rotate.x)).c_str());
                ImGui::Text(std::string("RotateY:" + std::to_string(rotate.y)).c_str());
                ImGui::Text(std::string("RotateZ:" + std::to_string(rotate.z)).c_str());

                ImGui::EndChild();
                nChildCnt++;
            }

            ImGui::EndChild();
            nChildCnt++;
        }
    }

    if (isEnd) ImGui::End();

    return nChildCnt;
}
