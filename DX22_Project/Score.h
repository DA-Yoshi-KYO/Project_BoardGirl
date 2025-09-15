#pragma once

#include "GameObject.h"

class CScore : public CGameObject
{
public:
    virtual ~CScore();
    void Init() override;
    void Update() override;
    void Draw() override;
    static int GetScore() { return m_nScore; }
    static void AddScore(int inScore) { m_nScore += inScore; }

private:
    RendererParam m_tRenderParam[4];
    static int m_nScore;

};
