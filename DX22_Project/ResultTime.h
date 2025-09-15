#pragma once

#include "GameObject.h"

class CResultTime : public CGameObject
{
public:
    virtual ~CResultTime();
    void Init() override;
    void Update() override;
    void Draw() override;
    
private:
    RendererParam m_tRenderParam[5];
    int m_nTimeCount;
};
