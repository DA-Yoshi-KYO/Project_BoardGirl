// インクルード部
#include "SelectArrow.h"
#include "DebugSystem.h"
#include "Oparation.h"
#include "Sprite3DRenderer.h"

CSelectArrow::CSelectArrow()
    : CGameObject()
    , m_pArrowSprite{}
    , m_f3ArrowPos{}, m_f3ArrowSize{}, m_f3ArrowRotate{}
{

}

CSelectArrow::~CSelectArrow()
{

}

void CSelectArrow::Init()
{
    // 使用するテクスチャのキー配列
    const char* chKey[] =
    {
        "ArrowLeft",
        "ArrowRight"
    };

    for (int i = 0; i < 2; i++)
    {
        // コンポーネントの追加
        m_pArrowSprite[i] = AddComponent<CSprite3DRenderer>();

        // 描画に使用するテクスチャのキーを設定
        m_pArrowSprite[i]->SetKey(chKey[i]);

        // 描画用パラメータの設定
        m_f3ArrowPos[i] = DirectX::XMFLOAT3(-4.0f + 8.0f * i, 0.0f, -5.0f);
        m_f3ArrowSize[i] = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
        m_f3ArrowRotate[i] = DirectX::XMFLOAT3(0.0f, 0.0f, DirectX::XMConvertToRadians(180.0f) * i);
    }
}

void CSelectArrow::Update()
{
    static float fTime = 0.0f;  // タイマー

    for (int i = 0; i < 2; i++)
    {
        // 時間に応じて矢印UIを拡縮させる
        m_f3ArrowSize[i] = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f) * (1 - fabsf(sinf(DirectX::XMConvertToRadians(fTime * 90.0f)) * 0.5f));
    }

    fTime += fDeltaTime;

    CGameObject::Update();
}

void CSelectArrow::Draw()
{
    for (int i = 0; i < 2; i++)
    {
        m_tParam.m_f3Pos = m_f3ArrowPos[i];
        m_tParam.m_f3Size = m_f3ArrowSize[i];
        m_tParam.m_f3Rotate = m_f3ArrowRotate[i];
        CGameObject::Draw();
    }
}

int CSelectArrow::Inspecter(bool isEnd)
{
    int nChildCnt = 0;

    ImGui::SetNextWindowPos(ImVec2(SCREEN_WIDTH - 300, 20));
    ImGui::SetNextWindowSize(ImVec2(280, SCREEN_HEIGHT - 140));
    ImGui::Begin("Inspecter");

    ImGui::BeginChild(ImGui::GetID((void*)nChildCnt), ImVec2(250, 30), ImGuiWindowFlags_NoTitleBar);

    ObjectID id = m_tID;
    std::string name = id.m_sName;
    if (id.m_nSameCount != 0) name += std::to_string(id.m_nSameCount);
    name = "Name:" + name;
    ImGui::Text(name.c_str());

    ImGui::EndChild();
    nChildCnt++;

    ImGui::BeginChild(ImGui::GetID((void*)nChildCnt), ImVec2(250, 270), ImGuiWindowFlags_NoTitleBar);
    if (ImGui::CollapsingHeader(std::string("[LeftArrow]").c_str()))
    {
        if (CDebugSystem::GetInstance()->IsUpdate())
        {
            if (ImGui::CollapsingHeader(std::string("[Transform]").c_str()))
            {
                ImGui::Text(std::string("Position").c_str());
                DirectX::XMFLOAT3 pos = m_f3ArrowPos[0];
                ImGui::Text(std::string("PosX:" + std::to_string(pos.x)).c_str());
                ImGui::Text(std::string("PosY:" + std::to_string(pos.y)).c_str());
                ImGui::Text(std::string("PosZ:" + std::to_string(pos.z)).c_str());
                ImGui::Text("\n");

                ImGui::Text(std::string("Size").c_str());
                DirectX::XMFLOAT3 size = m_f3ArrowSize[0];
                ImGui::Text(std::string("SizeX:" + std::to_string(size.x)).c_str());
                ImGui::Text(std::string("SizeY:" + std::to_string(size.y)).c_str());
                ImGui::Text(std::string("SizeZ:" + std::to_string(size.z)).c_str());
                ImGui::Text("\n");

                ImGui::Text(std::string("Rotation").c_str());
                DirectX::XMFLOAT3 rotate = m_f3ArrowRotate[0];
                ImGui::Text(std::string("RotateX:" + std::to_string(rotate.x)).c_str());
                ImGui::Text(std::string("RotateY:" + std::to_string(rotate.y)).c_str());
                ImGui::Text(std::string("RotateZ:" + std::to_string(rotate.z)).c_str());

            }
        }
        else
        {
            if (ImGui::CollapsingHeader(std::string("[Transform]").c_str()))
            {
                DirectX::XMFLOAT3* pos = &m_f3ArrowPos[0];
                float inputPos[3] = { pos->x,pos->y,pos->z };
                ImGui::InputFloat3("Position", inputPos);
                ImGui::Text("\n");
                *pos = DirectX::XMFLOAT3(inputPos[0], inputPos[1], inputPos[2]);

                DirectX::XMFLOAT3* size = &m_f3ArrowSize[0];
                float inputSize[3] = { size->x,size->y,size->z };
                ImGui::InputFloat3("Size", inputSize);
                ImGui::Text("\n");
                *size = DirectX::XMFLOAT3(inputSize[0], inputSize[1], inputSize[2]);

                DirectX::XMFLOAT3* rotate = &m_f3ArrowRotate[0];
                float inputRotate[3] = { rotate->x,rotate->y,rotate->z };
                ImGui::InputFloat3("Rotate", inputRotate);
                ImGui::Text("\n");
                *rotate = DirectX::XMFLOAT3(inputRotate[0], inputRotate[1], inputRotate[2]);

            }
        }
    }
    if (ImGui::CollapsingHeader(std::string("[RightArrow]").c_str()))
    {
        if (CDebugSystem::GetInstance()->IsUpdate())
        {
            if (ImGui::CollapsingHeader(std::string("[Transform]").c_str()))
            {
                ImGui::Text(std::string("Position").c_str());
                DirectX::XMFLOAT3 pos = m_f3ArrowPos[1];
                ImGui::Text(std::string("PosX:" + std::to_string(pos.x)).c_str());
                ImGui::Text(std::string("PosY:" + std::to_string(pos.y)).c_str());
                ImGui::Text(std::string("PosZ:" + std::to_string(pos.z)).c_str());
                ImGui::Text("\n");

                ImGui::Text(std::string("Size").c_str());
                DirectX::XMFLOAT3 size = m_f3ArrowSize[1];
                ImGui::Text(std::string("SizeX:" + std::to_string(size.x)).c_str());
                ImGui::Text(std::string("SizeY:" + std::to_string(size.y)).c_str());
                ImGui::Text(std::string("SizeZ:" + std::to_string(size.z)).c_str());
                ImGui::Text("\n");

                ImGui::Text(std::string("Rotation").c_str());
                DirectX::XMFLOAT3 rotate = m_f3ArrowRotate[1];
                ImGui::Text(std::string("RotateX:" + std::to_string(rotate.x)).c_str());
                ImGui::Text(std::string("RotateY:" + std::to_string(rotate.y)).c_str());
                ImGui::Text(std::string("RotateZ:" + std::to_string(rotate.z)).c_str());

            }
        }
        else
        {
            if (ImGui::CollapsingHeader(std::string("[Transform]").c_str()))
            {
                DirectX::XMFLOAT3* pos = &m_f3ArrowPos[1];
                float inputPos[3] = { pos->x,pos->y,pos->z };
                ImGui::InputFloat3("Position", inputPos);
                ImGui::Text("\n");
                *pos = DirectX::XMFLOAT3(inputPos[0], inputPos[1], inputPos[2]);

                DirectX::XMFLOAT3* size = &m_f3ArrowSize[1];
                float inputSize[3] = { size->x,size->y,size->z };
                ImGui::InputFloat3("Size", inputSize);
                ImGui::Text("\n");
                *size = DirectX::XMFLOAT3(inputSize[0], inputSize[1], inputSize[2]);

                DirectX::XMFLOAT3* rotate = &m_f3ArrowRotate[1];
                float inputRotate[3] = { rotate->x,rotate->y,rotate->z };
                ImGui::InputFloat3("Rotate", inputRotate);
                ImGui::Text("\n");
                *rotate = DirectX::XMFLOAT3(inputRotate[0], inputRotate[1], inputRotate[2]);

            }
        }
    }
    ImGui::EndChild();
    nChildCnt++;

    if (isEnd) ImGui::End();

    return nChildCnt;
}
