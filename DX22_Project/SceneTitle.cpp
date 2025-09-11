#include "SceneTitle.h"
#include "TitleBackGround.h"
#include "BGMPlayer.h"
#include "SpriteRenderer.h"
#include "Oparation.h"
#include "Easing.h"

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Init()
{
    CSpriteRenderer::Load(TEXTURE_PATH("Title.jpg"), "TitleBG");
    CSpriteRenderer::Load(TEXTURE_PATH("Alphabet.png"), "Alphabet");
    
    AddGameObject<CTitleBackGround>("BackGround",Tag::UI);
    for (int i = 0; i < 10; i++)
    {
        m_pAplhaBoardFight[i] = AddGameObject<CAlphabet>("Alphabet", Tag::UI);
        m_pAplhaBoardFight[i]->AccessorPos(DirectX::XMFLOAT3(-375.0f + (i >= 5 ? i + 1 : i) * 75.0f, -300.0f, 0.0f));
        m_pAplhaBoardFight[i]->AccessorSize(DirectX::XMFLOAT3(100.0f, 100.0f, 0.0f));
        m_pAplhaBoardFight[i]->AccessorColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
    }
    m_pAplhaBoardFight[0]->SetAlphabet(ALPHA_B);
    m_pAplhaBoardFight[1]->SetAlphabet(ALPHA_O);
    m_pAplhaBoardFight[2]->SetAlphabet(ALPHA_A);
    m_pAplhaBoardFight[3]->SetAlphabet(ALPHA_R);
    m_pAplhaBoardFight[4]->SetAlphabet(ALPHA_D);
    m_pAplhaBoardFight[5]->SetAlphabet(ALPHA_F);
    m_pAplhaBoardFight[6]->SetAlphabet(ALPHA_I);
    m_pAplhaBoardFight[7]->SetAlphabet(ALPHA_G);
    m_pAplhaBoardFight[8]->SetAlphabet(ALPHA_H);
    m_pAplhaBoardFight[9]->SetAlphabet(ALPHA_T);

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
    m_pAplhaPressSpace[6]->SetAlphabet(ALPHA_T);
    m_pAplhaPressSpace[7]->SetAlphabet(ALPHA_A);
    m_pAplhaPressSpace[8]->SetAlphabet(ALPHA_R);
    m_pAplhaPressSpace[9]->SetAlphabet(ALPHA_T);

    CBGMPlayer* pPlayer = AddGameObject<CBGMPlayer>("BGM",Tag::Sound);
    pPlayer->Load(AUDIO_PATH("BGM/TitleBGM.wav"));
    pPlayer->SetVolume(0.1f);
    pPlayer->Play();

    m_eTitleAnim = TitleAnime::TitleLogo;
}

void CSceneTitle::Update()
{
    const DirectX::XMFLOAT3 c_f3InitPos = DirectX::XMFLOAT3(SCREEN_WIDTH + 200.0f, -300.0f, 0.0f);
    const DirectX::XMFLOAT3 c_f3TargetPos = DirectX::XMFLOAT3(-375.0f, -300.0f, 0.0f);
    static float fTime = 0.0f;

    switch (m_eTitleAnim)
    {
    case CSceneTitle::TitleAnime::TitleLogo:
        fTime += fDeltaTime;
        for (int i = 0; i < 10; i++)
        {
            DirectX::XMFLOAT3 f3OriginPos = c_f3InitPos + (c_f3TargetPos - c_f3InitPos) * CEasing::EaseOutBounce(fTime, 2.0f);
            m_pAplhaBoardFight[i]->AccessorPos(DirectX::XMFLOAT3(f3OriginPos.x + (i >= 5 ? i + 1 : i) * 75.0f, f3OriginPos.y, f3OriginPos.z));
        }
        if (fTime >= 3.0f)
        {
            fTime = 0.0f;
            m_eTitleAnim = TitleAnime::StartButton;
        }
        break;
    case CSceneTitle::TitleAnime::StartButton:
        fTime += fDeltaTime;
        for (int i = 0; i < 10; i++)
        {
            m_pAplhaPressSpace[i]->AccessorSize(DirectX::XMFLOAT3(100.0f,100.0f,100.0f) * CEasing::EaseOutQuint(fTime,1.0f));
        }
        if (fTime >= 2.0f)
        {
            fTime = 0.0f;
            m_eTitleAnim = TitleAnime::ButtonScaling;
        }
        break;
    case CSceneTitle::TitleAnime::ButtonScaling:
        fTime += fDeltaTime;
        for (int i = 0; i < 10; i++)
        {
            m_pAplhaPressSpace[i]->AccessorSize(DirectX::XMFLOAT3(100.0f, 100.0f, 100.0f) * (1 - fabsf(sinf(DirectX::XMConvertToRadians(fTime * 90.0f))) + 0.5f));
        }
        break;
    case CSceneTitle::TitleAnime::Max:
        break;
    default:
        break;
    }

}
