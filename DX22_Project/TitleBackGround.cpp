#include "TitleBackGround.h"
#include "SpriteRenderer.h"
#include "Input.h"
#include "Sprite.h"
#include "Main.h"
#include "SceneJobSelect.h"

enum class SEKind
{
    Decision,
};

void CTitleBackGround::Init()
{
	CSpriteRenderer* pRenderer = AddComponent<CSpriteRenderer>();
	pRenderer->SetKey("TitleBG");

	m_tParam.m_f3Size = { SCREEN_WIDTH, SCREEN_HEIGHT,0.0f };

    m_pSE.push_back(AddComponent<CAudio>());
    m_pSE[(int)SEKind::Decision]->Load(AUDIO_PATH("SE/Decision.wav"));
    m_pSE[(int)SEKind::Decision]->SetVolume(0.1f);

    m_bEnd = false;
    m_bTransition = false;
}

void CTitleBackGround::Update()
{
	if (IsKeyTrigger(VK_SPACE) && !m_bEnd)
	{
        m_bEnd = true;
        m_pSE[(int)SEKind::Decision]->Play();
	}

    if (!m_pSE[(int)SEKind::Decision]->IsPlay() && !m_bTransition && m_bEnd)
    {
        m_bTransition = true;
        FadeOut([]()
            {
                ChangeScene(new CSceneJobSelect());
                FadeIn(nullptr);
            });
    }
}
