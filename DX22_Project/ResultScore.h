#pragma once

#include "GameObject.h"

class CResultScore : public CGameObject
{
public:
    virtual ~CResultScore();
    void Init() override;
    void Update() override;
    void Draw() override;

private:
    RendererParam m_tRenderParam[4];
    int m_nScore;
};
