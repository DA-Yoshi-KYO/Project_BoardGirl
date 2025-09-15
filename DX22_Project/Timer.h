#pragma once

#include "GameObject.h"

class CTimer : public CGameObject
{
public:
    virtual ~CTimer();
    void Init() override;
    void Update() override;
    void Draw() override;
    static int GetTime() { return m_nTimeCount; }

private:
    RendererParam m_tRenderParam[5];
    float m_fTime;
    static int m_nTimeCount;

};
