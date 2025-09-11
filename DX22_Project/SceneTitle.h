#pragma once

// インクルード部
#include "Scene.h"
#include "Alphabet.h"

class CSceneTitle : public CScene
{
public:
	virtual ~CSceneTitle();
	void Init() override;
	void Update() override;

private:
    CAlphabet* m_pAplhaBoardFight[10];
    CAlphabet* m_pAplhaPressSpace[10];

    enum class TitleAnime
    {
        TitleLogo,
        StartButton,
        ButtonScaling,

        Max
    }m_eTitleAnim;
};

