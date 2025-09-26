// インクルード部
#include "SelectJobs.h"
#include "Easing.h"
#include "Input.h"
#include "Main.h"
#include "SceneGame.h"
#include "Oparation.h"
#include "DebugSystem.h"

// 定数・マクロ定義
constexpr DirectX::XMINT2 ce_n2Split = { 6, 6 };    // スプライトシートの分割数
constexpr float ce_fRadius = 5.0f;  // ジョブの配置する円状の半径

// 静的変数初期化
JobKind CSelectJobs::m_eSelectedJob = JobKind::Soldier;

// SEの種類
enum class SEKind
{
    Decision,   // 決定音
    Select,      // 選択音

    Max
};

CSelectJobs::CSelectJobs()
    : CGameObject()
    , m_pRenderer{}
    , m_tJobsParam{ m_tParam, m_tParam, m_tParam }, m_tTempParam{ m_tParam, m_tParam, m_tParam }
    , m_bEnd(false), m_bTransition(false)
    , m_bMove(false), m_bNext(false)
{

}

void CSelectJobs::Init()
{
    // Jobの初期選択肢
    m_eSelectedJob = JobKind::Soldier;

    for (int i = 0; i < (int)JobKind::Max; i++)
    {
        // コンポーネントの追加
        m_pRenderer[i] = AddComponent<CBillboardRenderer>();
        // 描画に使用するテクスチャのキーをセット
        m_pRenderer[i]->SetKey("Player");   
    }

    // ジョブのUV座標を指定
    m_tJobsParam[(int)JobKind::Soldier].m_f2UVPos = { 0.0f / (float)ce_n2Split.x , 1.0f / (float)ce_n2Split.y };
    m_tJobsParam[(int)JobKind::Wizard].m_f2UVPos = { 3.0f / (float)ce_n2Split.x , 1.0f / (float)ce_n2Split.y };
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

    // 使用するSEのパス
    const char* SEPath[] =
    {
        AUDIO_PATH("SE/Decision.wav"),
        AUDIO_PATH("SE/Select.wav")
    };
    // SEの追加
    for (int i = 0; i < (int)SEKind::Max; i++)
    {
        m_pSE.push_back(AddComponent<CAudio>());
        m_pSE[i]->Load(SEPath[i]);
        m_pSE[i]->SetVolume(0.1f);
    }
}

void CSelectJobs::Update()
{
    static float fTime = 0.0f;  // タイマー

    if (!m_bEnd)
    {
        if (!m_bMove)
        {
            // タイマーをリセット
            fTime = 0.0f;

            // 選択中のジョブは強調表示する
            m_tJobsParam[(int)m_eSelectedJob].m_f3Size = DirectX::XMFLOAT3(3.0f, 3.0f, 1.0f);
            for (int i = 0; i < (int)JobKind::Max; i++)
            {
                // 現在の座標を保存しておく
                m_tTempParam[i] = m_tJobsParam[i];
            }

            int nSelect = (int)m_eSelectedJob;  // 現在の選択

            // 右選択
            if ((IsMouseHover(DirectX::XMFLOAT2(500.0f, 0.0f), DirectX::XMFLOAT2(150.0f, 150.0f)) && IsMouseButtonTrigger(MOUSEBUTTON_L))
                || IsKeyTrigger('D'))
            {
                // 選択音を鳴らす
                m_pSE[(int)SEKind::Select]->Play();

                // 選択をインクリメント
                nSelect++;
                // 最大数になったら0(Soldier)に戻す
                if (nSelect >= (int)JobKind::Max)
                {
                    nSelect = 0;
                }

                // Moveフラグをオン
                m_bMove = true;
                // Nextフラグをオン
                m_bNext = true;
            }
            // 左選択
            else if ((IsMouseHover(DirectX::XMFLOAT2(-500.0f, 0.0f), DirectX::XMFLOAT2(150.0f, 150.0f)) && IsMouseButtonTrigger(MOUSEBUTTON_L))
                || IsKeyTrigger('A'))
            {
                // 選択音を鳴らす
                m_pSE[(int)SEKind::Select]->Play();

                // 選択をデクリメント
                nSelect--;
                // 最大数になったらMax - 1に戻す
                if (nSelect < 0)
                {
                    nSelect = (int)JobKind::Max - 1;
                }

                // Moveフラグをオン
                m_bMove = true;
                // Nextフラグをオフ
                m_bNext = true;
            }
            // 決定
            else if ((IsMouseHover(DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(600.0f, 600.0f)) && IsMouseButtonTrigger(MOUSEBUTTON_L))
                || IsKeyTrigger(VK_SPACE))
            {
                // 決定音を鳴らす
                m_pSE[(int)SEKind::Decision]->Play();
                // 選択完了フラグをオン
                m_bEnd = true;
            }

            // 選択中のジョブの更新
            m_eSelectedJob = (JobKind)nSelect;
        }
        else
        {
            for (int i = 0; i < (int)JobKind::Max; ++i)
            {
                // サイズをリセットする
                m_tJobsParam[i].m_f3Size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
            }

            // 次への選択
            if (m_bNext)
            {
                for (int i = 0; i < (int)JobKind::Max; i++)
                {
                    // 
                    int backIndex = (i - 1 + (int)JobKind::Max) % (int)JobKind::Max;
                    DirectX::XMFLOAT3 f3Disance = m_tTempParam[backIndex].m_f3Pos - m_tTempParam[i].m_f3Pos;
                    m_tJobsParam[i].m_f3Pos = (CEasing::EaseOutBack(fTime, 1.0f) * f3Disance) + m_tTempParam[i].m_f3Pos;
                }
            }
            // 前への選択
            else
            {
                for (int i = 0; i < (int)JobKind::Max; i++)
                {
                    int nextIndex = (i + 1) % (int)JobKind::Max;
                    DirectX::XMFLOAT3 f3Disance = m_tTempParam[nextIndex].m_f3Pos - m_tTempParam[i].m_f3Pos;
                    m_tJobsParam[i].m_f3Pos = (CEasing::EaseOutBack(fTime, 1.0f) * f3Disance) + m_tTempParam[i].m_f3Pos;
                }
            }

            // 1秒かけて移動させる
            if (fTime >= 1.0f)
            {
                m_bMove = false;
            }

            // タイマーの加算
            fTime += fDeltaTime;
        }
    }
    else
    {
        // 選択が終わってSEが再生完了したらシーン遷移する
        if (!m_pSE[(int)SEKind::Decision]->IsPlay() && !m_bTransition && m_bEnd)
        {
            // 遷移フラグをオンにする
            m_bTransition = true;

            // シーン遷移
            FadeOut([]()
                {
                    ChangeScene(new CSceneGame());
                    FadeIn(nullptr);
                });
        }
    }
 
    CGameObject::Update();
}

void CSelectJobs::Draw()
{
    for (int i = 0; i < (int)JobKind::Max; ++i)
    {
        m_pRenderer[i]->SetRendererParam(m_tJobsParam[i]);
        m_pRenderer[i]->Draw();
    }
}

int CSelectJobs::Inspecter(bool isEnd)
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
    std::string sJobName[(int)JobKind::Max] =
    {
        "Soldier",
        "Wizard",
        "Fighter",
    };

    for (int i = 0; i < (int)JobKind::Max; i++)
    {
        // HPバーの表裏のパラメータを描画
        if (ImGui::CollapsingHeader(sJobName[i].c_str()))
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
                DirectX::XMFLOAT3 pos = m_tJobsParam[i].m_f3Pos;
                ImGui::Text(std::string("PosX:" + std::to_string(pos.x)).c_str());
                ImGui::Text(std::string("PosY:" + std::to_string(pos.y)).c_str());
                ImGui::Text(std::string("PosZ:" + std::to_string(pos.z)).c_str());
                ImGui::Text("\n");

                // サイズの描画
                ImGui::Text(std::string("Size").c_str());
                DirectX::XMFLOAT3 size = m_tJobsParam[i].m_f3Size;
                ImGui::Text(std::string("SizeX:" + std::to_string(size.x)).c_str());
                ImGui::Text(std::string("SizeY:" + std::to_string(size.y)).c_str());
                ImGui::Text(std::string("SizeZ:" + std::to_string(size.z)).c_str());
                ImGui::Text("\n");

                // 回転の描画
                ImGui::Text(std::string("Rotation").c_str());
                DirectX::XMFLOAT3 rotate = m_tJobsParam[i].m_f3Rotate;
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

    // IMGUIウィンドウの終了
    if (isEnd) ImGui::End();

    return nChildCnt;
}
