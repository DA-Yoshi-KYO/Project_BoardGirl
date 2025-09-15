#include "SceneResult.h"
#include "BGMPlayer.h"
#include "SpriteRenderer.h"
#include "ResultBackGround.h"
#include "Oparation.h"
#include "ResultTime.h"
#include "ResultScore.h"

CSceneResult::~CSceneResult()
{
}

void CSceneResult::Init()
{
    CSpriteRenderer::Load(TEXTURE_PATH("Result.jpg"), "ResultBG");
    CSpriteRenderer::Load(TEXTURE_PATH("Number.png"), "Number");
    AddGameObject<CResultBackGround>("BackGround", Tag::UI);
    AddGameObject<CResultScore>("ResultScore", Tag::UI);
    AddGameObject<CResultTime>("ResultTime", Tag::UI);

    for (int i = 0; i < 8; i++)
    {
        m_pAplhaGameOver[i] = AddGameObject<CAlphabet>("Alphabet", Tag::UI);
        m_pAplhaGameOver[i]->AccessorPos(DirectX::XMFLOAT3(-300.0f + (i >= 4 ? i + 1 : i) * 75.0f, -300.0f, 0.0f));
        m_pAplhaGameOver[i]->AccessorSize(DirectX::XMFLOAT3(100.0f, 100.0f, 0.0f));
        m_pAplhaGameOver[i]->AccessorColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
    }
    m_pAplhaGameOver[0]->SetAlphabet(ALPHA_G);
    m_pAplhaGameOver[1]->SetAlphabet(ALPHA_A);
    m_pAplhaGameOver[2]->SetAlphabet(ALPHA_M);
    m_pAplhaGameOver[3]->SetAlphabet(ALPHA_E);
    m_pAplhaGameOver[4]->SetAlphabet(ALPHA_O);
    m_pAplhaGameOver[5]->SetAlphabet(ALPHA_V);
    m_pAplhaGameOver[6]->SetAlphabet(ALPHA_E);
    m_pAplhaGameOver[7]->SetAlphabet(ALPHA_R);

    for (int i = 0; i < 5; i++)
    {
        m_pAplhaScore[i] = AddGameObject<CAlphabet>("Alphabet", Tag::UI);
        m_pAplhaScore[i]->AccessorPos(DirectX::XMFLOAT3(-375.0f + i * 75.0f, -100.0f, 0.0f));
        m_pAplhaScore[i]->AccessorSize(DirectX::XMFLOAT3(100.0f, 100.0f, 0.0f));
        m_pAplhaScore[i]->AccessorColor(DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
    }
    m_pAplhaScore[0]->SetAlphabet(ALPHA_S);
    m_pAplhaScore[1]->SetAlphabet(ALPHA_C);
    m_pAplhaScore[2]->SetAlphabet(ALPHA_O);
    m_pAplhaScore[3]->SetAlphabet(ALPHA_R);
    m_pAplhaScore[4]->SetAlphabet(ALPHA_E);

    for (int i = 0; i < 4; i++)
    {
        m_pAplhaTime[i] = AddGameObject<CAlphabet>("Alphabet", Tag::UI);
        m_pAplhaTime[i]->AccessorPos(DirectX::XMFLOAT3(-375.0f + i * 75.0f, 100.0f, 0.0f));
        m_pAplhaTime[i]->AccessorSize(DirectX::XMFLOAT3(100.0f, 100.0f, 0.0f));
        m_pAplhaTime[i]->AccessorColor(DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
    }
    m_pAplhaTime[0]->SetAlphabet(ALPHA_T);
    m_pAplhaTime[1]->SetAlphabet(ALPHA_I);
    m_pAplhaTime[2]->SetAlphabet(ALPHA_M);
    m_pAplhaTime[3]->SetAlphabet(ALPHA_E);

    for (int i = 0; i < 10; i++)
    {
        m_pAplhaPressSpace[i] = AddGameObject<CAlphabet>("Alphabet", Tag::UI);
        m_pAplhaPressSpace[i]->AccessorPos(DirectX::XMFLOAT3(-375.0f + (i >= 5 ? i + 1 : i) * 75.0f, 300.0f, 0.0f));
        m_pAplhaPressSpace[i]->AccessorSize(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
        m_pAplhaPressSpace[i]->AccessorColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
    }
    m_pAplhaPressSpace[0]->SetAlphabet(ALPHA_P);
    m_pAplhaPressSpace[1]->SetAlphabet(ALPHA_R);
    m_pAplhaPressSpace[2]->SetAlphabet(ALPHA_E);
    m_pAplhaPressSpace[3]->SetAlphabet(ALPHA_S);
    m_pAplhaPressSpace[4]->SetAlphabet(ALPHA_S);
    m_pAplhaPressSpace[5]->SetAlphabet(ALPHA_S);
    m_pAplhaPressSpace[6]->SetAlphabet(ALPHA_P);
    m_pAplhaPressSpace[7]->SetAlphabet(ALPHA_A);
    m_pAplhaPressSpace[8]->SetAlphabet(ALPHA_C);
    m_pAplhaPressSpace[9]->SetAlphabet(ALPHA_E);

    CBGMPlayer* pPlayer = AddGameObject<CBGMPlayer>("BGM", Tag::Sound);
    pPlayer->Load(AUDIO_PATH("BGM/ResultBGM.wav"));
    pPlayer->SetVolume(0.1f);
    pPlayer->Play();
}

void CSceneResult::Update()
{
    static float fTime = 0.0f;
    fTime += fDeltaTime;
    for (int i = 0; i < 10; i++)
    {
        m_pAplhaPressSpace[i]->AccessorSize(DirectX::XMFLOAT3(100.0f, 100.0f, 100.0f) * (1 - fabsf(sinf(DirectX::XMConvertToRadians(fTime * 90.0f)) * 0.5f)));
    }

    CScene::Update();
}
