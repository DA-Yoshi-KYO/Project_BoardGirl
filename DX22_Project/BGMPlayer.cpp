#include "BGMPlayer.h"

CBGMPlayer::~CBGMPlayer()
{

}

void CBGMPlayer::Load(const char* inPath)
{
    m_pAudio = AddComponent<CAudio>();
    m_pAudio->Load(inPath);

    m_tState.m_sBGMName = inPath;
}

void CBGMPlayer::Play()
{
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
    int nChildCnt = 0;

    ImGui::SetNextWindowPos(ImVec2(SCREEN_WIDTH - 300, 20));
    ImGui::SetNextWindowSize(ImVec2(280, SCREEN_HEIGHT - 40));
    ImGui::Begin("Inspecter");

    ImGui::BeginChild(ImGui::GetID((void*)nChildCnt), ImVec2(250, 30), ImGuiWindowFlags_NoTitleBar);

    ObjectID id = m_tID;
    std::string name = id.m_sName;
    if (id.m_nSameCount != 0) name += std::to_string(id.m_nSameCount);
    name = "Name:" + name;
    ImGui::Text(name.c_str());

    ImGui::EndChild();
    nChildCnt++;

    if (ImGui::CollapsingHeader(std::string("Status").c_str()))
    {
        std::string sDebugSound;
        for (int i = 17; i < m_tState.m_sBGMName.size(); i++)
        {
            sDebugSound.push_back(m_tState.m_sBGMName[i]);
        }
        ImGui::Text(std::string("NowPlaying:" + sDebugSound).c_str());

        ImGui::Text(std::string("Volume:" + std::to_string(int(m_tState.m_fVolume * 100)) + "%%").c_str());
    }

    ImGui::End();
    return nChildCnt;
}
