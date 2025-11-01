// インクルード部
#include "BGMPlayer.h"
#include "Audio.h"

CBGMPlayer::CBGMPlayer()
    : CGameObject()
    , m_pAudio(nullptr)
    , m_tState{"None", 1.0f}
{

}

CBGMPlayer::~CBGMPlayer()
{

}

void CBGMPlayer::Load(const char* inPath)
{
    // コンポーネントの追加
    m_pAudio = AddComponent<CAudio>();
    // パスの読み込み
    m_pAudio->Load(inPath);

    // 名前の登録
    m_tState.m_sBGMName = inPath;
}

void CBGMPlayer::Play()
{
    // ループ再生を有効にする
    m_pAudio->Play(true);
}

void CBGMPlayer::Stop()
{
    m_pAudio->Stop();
}

void CBGMPlayer::SetVolume(float inVolume)
{
    m_tState.m_fVolume = inVolume;
    m_pAudio->SetVolume(m_tState.m_fVolume);
}

int CBGMPlayer::Inspecter(bool isEnd)
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

    // 子要素の初期化
    ImGui::BeginChild(ImGui::GetID((void*)nChildCnt), ImVec2(250, 180), ImGuiWindowFlags_NoTitleBar);

    // サウンドデータの表示
    if (ImGui::CollapsingHeader(std::string("Status").c_str()))
    {
        // 名前の表示
        std::string sDebugSound;
        for (int i = 17; i < m_tState.m_sBGMName.size(); i++)
        {
            sDebugSound.push_back(m_tState.m_sBGMName[i]);
        }
        ImGui::Text(std::string("NowPlaying:" + sDebugSound).c_str());

        // ボリュームの表示
        ImGui::Text(std::string("Volume:" + std::to_string(int(m_tState.m_fVolume * 100)) + "%%").c_str());
    }

    // 子要素の終了
    ImGui::EndChild();
    // 子要素の数をインクリメント
    nChildCnt++;

    // IMGUIウィンドウの終了
    if (isEnd) ImGui::End();
    return nChildCnt;
}
