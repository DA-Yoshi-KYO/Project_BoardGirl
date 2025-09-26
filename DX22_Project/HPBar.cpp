// インクルード部
#include "HPBar.h"
#include "Camera.h"
#include "Oparation.h"
#include "Main.h"
#include "Player.h"
#include "DebugSystem.h"
#include "BillboardRenderer.h"

CHPBar::~CHPBar()
{
}

void CHPBar::Init()
{
    m_tValue.m_nMaxHP = m_tValue.m_nCurrentHP = 0;
    m_tParentID = {};

    for (int i = 0; i < (int)TextureKind::Max; i++)
    {
        m_pHPBar[i] = AddComponent<CBillboardRenderer>();
        m_pHPBar[i]->SetKey("HPBar");
        m_tRendererParam[i].m_f3Pos = {};
        m_tRendererParam[i].m_f3Size = { 2.0f,1.0f,0.0f };
        m_tRendererParam[i].m_f3Rotate = {};
        m_tRendererParam[i].m_f2UVPos = {};
        m_tRendererParam[i].m_f2UVSize = {1.0f,1.0f};

        switch (i)
        {
        case (int)TextureKind::Back:
            m_tRendererParam[i].m_f4Color = { 0.0f,0.0f,0.0f,1.0f };
            break;
        case (int)TextureKind::Flont:
            m_tRendererParam[i].m_f4Color = { 0.0f,1.0f,0.0f,1.0f };
            break;
        default:
            break;
        }
    }
}

void CHPBar::Update()
{
    CScene* pScene = GetScene();
    DirectX::XMFLOAT3 f3ObjectPos = pScene->GetGameObject(m_tParentID)->AccessorPos();
    float fOffsetY = pScene->GetGameObject(m_tParentID)->AccessorSize().y * 0.5f;
    f3ObjectPos.y += fOffsetY;
    for (int i = 0; i < (int)TextureKind::Max; i++)
    {
        m_tRendererParam[i].m_f3Pos = f3ObjectPos;
    }
    float fStep = (float)m_tValue.m_nCurrentHP / (float)m_tValue.m_nMaxHP;
    m_tRendererParam[(int)TextureKind::Flont].m_f3Size.x = m_tValue.m_fMaxSize * fStep;
    float fOffSetRatio = 1.0f - fStep;
    DirectX::XMFLOAT3 f3MovePos = pScene->GetGameObject<CPlayer>()->GetRight();
    f3MovePos.x *= m_tValue.m_fMaxSize * 0.5f;
    DirectX::XMFLOAT3 f3OffSetRight = f3MovePos * fOffSetRatio;

    m_tRendererParam[(int)TextureKind::Flont].m_f3Pos -= f3OffSetRight;
    m_tParam.m_f3Pos = m_tRendererParam[(int)TextureKind::Back].m_f3Pos;
    CGameObject::Update();
}

void CHPBar::Draw()
{
    for (int i = 0; i < (int)TextureKind::Max; i++)
    {
        m_pHPBar[i]->SetRendererParam(m_tRendererParam[i]);
        m_pHPBar[i]->Draw();
    }
}

void CHPBar::SetCurrentHP(int inCurrentHP)
{
    m_tValue.m_nCurrentHP = inCurrentHP;
}

void CHPBar::SetMaxHP(int inMaxHP)
{
    m_tValue.m_nMaxHP = inMaxHP;
}

void CHPBar::SetParentID(ObjectID inParent)
{
    m_tParentID = inParent;
}

void CHPBar::SetRenderState(DirectX::XMFLOAT3 inSize, DirectX::XMFLOAT4 inFlontColor)
{
    for (int i = 0; i < (int)TextureKind::Max; i++)
    {
        m_tRendererParam[i].m_f3Size = inSize;
    }
    m_tValue.m_fMaxSize = inSize.x;
    m_tRendererParam[(int)TextureKind::Flont].m_f4Color = inFlontColor;
}

int CHPBar::Inspecter(bool isEnd)
{
    // 子要素の数
    int nChildCnt = 0;

    // IMGUIウィンドウの初期化
    ImGui::SetNextWindowPos(ImVec2(SCREEN_WIDTH - 300, 20));
    ImGui::SetNextWindowSize(ImVec2(280, SCREEN_HEIGHT - 140));
    ImGui::Begin("Inspecter");

    // 子要素の初期化
    ImGui::BeginChild(ImGui::GetID((void*)nChildCnt), ImVec2(250, 30), ImGuiWindowFlags_NoTitleBar);

    // インスペクターに名前を表示
    ObjectID id = m_tID;
    std::string name = id.m_sName;

    // 同オブジェクトが2つ以上ある場合、そのindexも名前に表示する
    if (id.m_nSameCount != 0) name += std::to_string(id.m_nSameCount);
    name = "Name:" + name;
    ImGui::Text(name.c_str());

    // 子要素の終了
    ImGui::EndChild();
    // 子要素の数をインクリメント
    nChildCnt++;

    // 描画の名前を定義
    std::string sHPBarName[(int)TextureKind::Max] =
    {
        "Back",
        "Fill",
    };

    for (int i = 0; i < (int)TextureKind::Max; i++)
    {
        // HPバーの表裏のパラメータを描画
        if (ImGui::CollapsingHeader(sHPBarName[i].c_str()))
        {
            // 子要素の初期化
            ImGui::BeginChild(ImGui::GetID((void*)nChildCnt), ImVec2(ce_f2InspecterSize.x, ce_f2InspecterSize.y * 9), ImGuiWindowFlags_NoTitleBar);

            // トランスフォームの描画
            if (ImGui::CollapsingHeader(std::string("[Transform]").c_str()))
            {
                // 子要素の初期化
                ImGui::BeginChild(ImGui::GetID((void*)nChildCnt), ImVec2(ce_f2InspecterSize.x, ce_f2InspecterSize.y * 9), ImGuiWindowFlags_NoTitleBar);

                // 座標の描画
                ImGui::Text(std::string("Position").c_str());
                DirectX::XMFLOAT3 pos = m_tRendererParam[i].m_f3Pos;
                ImGui::Text(std::string("PosX:" + std::to_string(pos.x)).c_str());
                ImGui::Text(std::string("PosY:" + std::to_string(pos.y)).c_str());
                ImGui::Text(std::string("PosZ:" + std::to_string(pos.z)).c_str());
                ImGui::Text("\n");

                // サイズの描画
                ImGui::Text(std::string("Size").c_str());
                DirectX::XMFLOAT3 size = m_tRendererParam[i].m_f3Size;
                ImGui::Text(std::string("SizeX:" + std::to_string(size.x)).c_str());
                ImGui::Text(std::string("SizeY:" + std::to_string(size.y)).c_str());
                ImGui::Text(std::string("SizeZ:" + std::to_string(size.z)).c_str());
                ImGui::Text("\n");

                // 回転の描画
                ImGui::Text(std::string("Rotation").c_str());
                DirectX::XMFLOAT3 rotate = m_tRendererParam[i].m_f3Rotate;
                ImGui::Text(std::string("RotateX:" + std::to_string(rotate.x)).c_str());
                ImGui::Text(std::string("RotateY:" + std::to_string(rotate.y)).c_str());
                ImGui::Text(std::string("RotateZ:" + std::to_string(rotate.z)).c_str());

                // 子要素の終了
                ImGui::EndChild();
                // 子要素の数をインクリメント
                nChildCnt++;
            }

            // 子要素の終了
            ImGui::EndChild();
            // 子要素の数をインクリメント
            nChildCnt++;
        }
    }

    // HPパラメータの描画
    if (ImGui::CollapsingHeader(std::string("HP").c_str()))
    {
        // HP数値と割合の表示
        ImGui::Text(std::string(std::to_string(m_tValue.m_nCurrentHP) + "/" + std::to_string(m_tValue.m_nMaxHP)).c_str());
        ImGui::SameLine();
        ImGui::Text(std::string(std::to_string((int)((m_tValue.m_nCurrentHP / (float)m_tValue.m_nMaxHP) * 100)) + "%%").c_str());
    }

    // IMGUIウィンドウの終了
    if (isEnd) ImGui::End();

    return nChildCnt;
}
