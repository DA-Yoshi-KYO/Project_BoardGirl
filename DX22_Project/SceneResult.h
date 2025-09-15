#pragma once

#include "Scene.h"
#include "Alphabet.h"

class CSceneResult : public CScene
{
public:
    virtual ~CSceneResult();
    void Init() override;
    void Update() override;

private:
    CAlphabet* m_pAplhaGameOver[8];
    CAlphabet* m_pAplhaScore[5];
    CAlphabet* m_pAplhaTime[4];
    CAlphabet* m_pAplhaPressSpace[10];
};

