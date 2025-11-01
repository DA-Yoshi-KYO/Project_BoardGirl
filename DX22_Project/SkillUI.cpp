#include "SkillUI.h"
#include "DebugSystem.h"
#include "Oparation.h"

CSkillUI::~CSkillUI()
{
}

void CSkillUI::Init()
{
    const std::string key[] =
    {
        "Circle",
        "Circle",
        "Frame",
    };

    for (int i = 0; i < eTexture::Max; i++)
    {
        m_pSprite[i] = AddComponent<CSpriteRenderer>();
        m_pSprite[i]->SetKey(key[i]);
        m_tSpriteParam[i] = m_tParam;
    }

    m_fCurrentValue = m_fMaxValue = 0.0f;
    fTime = 0.0f;
    m_f3FillSize = {};
}

void CSkillUI::Update()
{
    m_tSpriteParam[eTexture::Front].m_f3Size = ((m_fCurrentValue / m_fMaxValue)) * m_f3FillSize;
    if (m_fMaxValue == m_fCurrentValue)
    {
        fTime += fDeltaTime;
        m_tSpriteParam[eTexture::Frame].m_f4Color.w = fabsf(sinf(DirectX::XMConvertToRadians(fTime * 90.0f)));
        m_tSpriteParam[eTexture::Front].m_f4Color.w = 1.0f;
    }
    else
    {
        m_tSpriteParam[eTexture::Frame].m_f4Color.w = 0.0f;
        m_tSpriteParam[eTexture::Front].m_f4Color.w = 0.5f;
        fTime = 0.0f;
    }

    CGameObject::Update();
}

void CSkillUI::Draw()
{
    for (int i = 0; i < eTexture::Max; i++)
    {
        m_tParam = m_tSpriteParam[i];
        CGameObject::Draw();
    }
}

int CSkillUI::Inspecter(bool isEnd)
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

    for (int i = 0; i < eTexture::Max; i++)
    {
        ImGui::BeginChild(ImGui::GetID((void*)nChildCnt), ImVec2(250, 270), ImGuiWindowFlags_NoTitleBar);
            std::string headerString = "";
            switch (i)
            {
            case eTexture::Back: headerString = "[Transform_Back]"; break;
            case eTexture::Front: headerString = "[Transform_Front]"; break;
            case eTexture::Frame: headerString = "[Transform_Frame]"; break;
            }
        if (CDebugSystem::GetInstance()->IsUpdate())
        {

            if (ImGui::CollapsingHeader(std::string(headerString).c_str()))
            {
                ImGui::Text(std::string("Position").c_str());
                DirectX::XMFLOAT3 pos = m_tSpriteParam[i].m_f3Pos;
                ImGui::Text(std::string("PosX:" + std::to_string(pos.x)).c_str());
                ImGui::Text(std::string("PosY:" + std::to_string(pos.y)).c_str());
                ImGui::Text(std::string("PosZ:" + std::to_string(pos.z)).c_str());
                ImGui::Text("\n");

                ImGui::Text(std::string("Size").c_str());
                DirectX::XMFLOAT3 size = m_tSpriteParam[i].m_f3Size;
                ImGui::Text(std::string("SizeX:" + std::to_string(size.x)).c_str());
                ImGui::Text(std::string("SizeY:" + std::to_string(size.y)).c_str());
                ImGui::Text(std::string("SizeZ:" + std::to_string(size.z)).c_str());
                ImGui::Text("\n");

                ImGui::Text(std::string("Rotation").c_str());
                DirectX::XMFLOAT3 rotate = m_tSpriteParam[i].m_f3Rotate;
                ImGui::Text(std::string("RotateX:" + std::to_string(rotate.x)).c_str());
                ImGui::Text(std::string("RotateY:" + std::to_string(rotate.y)).c_str());
                ImGui::Text(std::string("RotateZ:" + std::to_string(rotate.z)).c_str());

            }
        }
        else
        {
            if (ImGui::CollapsingHeader(std::string(headerString).c_str()))
            {
                DirectX::XMFLOAT3* pos = &m_tSpriteParam[i].m_f3Pos;
                float inputPos[3] = { pos->x,pos->y,pos->z };
                ImGui::InputFloat3("Position", inputPos);
                ImGui::Text("\n");
                *pos = DirectX::XMFLOAT3(inputPos[0], inputPos[1], inputPos[2]);

                DirectX::XMFLOAT3* size = &m_tSpriteParam[i].m_f3Size;
                float inputSize[3] = { size->x,size->y,size->z };
                ImGui::InputFloat3("Size", inputSize);
                ImGui::Text("\n");
                *size = DirectX::XMFLOAT3(inputSize[0], inputSize[1], inputSize[2]);

                DirectX::XMFLOAT3* rotate = &m_tSpriteParam[i].m_f3Rotate;
                float inputRotate[3] = { rotate->x,rotate->y,rotate->z };
                ImGui::InputFloat3("Rotate", inputRotate);
                ImGui::Text("\n");
                *rotate = DirectX::XMFLOAT3(inputRotate[0], inputRotate[1], inputRotate[2]);

            }
        }
        ImGui::EndChild();
        nChildCnt++;
    }

    if (isEnd) ImGui::End();

    return nChildCnt;
}

void CSkillUI::SetTransform(DirectX::XMFLOAT3 inPos, DirectX::XMFLOAT3 inSize)
{
    for (int i = 0; i < eTexture::Max; i++)
    {
        m_tSpriteParam[i].m_f3Pos = inPos;
        m_tSpriteParam[i].m_f3Size = inSize;
    }
    m_f3FillSize = inSize;
}
