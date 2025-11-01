#pragma once

#include "GameObject.h"

class CResultBackGround : public CGameObject
{
public:
    void Init() override;
    void Update() override;

private:
    bool m_bEnd;
    bool m_bTransition;

};
