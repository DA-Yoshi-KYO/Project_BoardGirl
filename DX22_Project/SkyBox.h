#pragma once

#include "GameObject.h"
#include "ModelRenderer.h"
#include "Player.h"

class CSkyBox : public CGameObject
{
public:
    ~CSkyBox();
    void Init() override;
    void Update() override;
    void Draw() override;

private:
    CPlayer* m_pPlayer;

};
