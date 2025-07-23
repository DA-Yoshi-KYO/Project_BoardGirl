#pragma once

#include "GameObject.h"
#include "Job.h"
#include "Sprite3DRenderer.h"

class CSelectJobs : public CGameObject
{
public:
    void Init() override;
    void Draw() override;

private:
    CSprite3DRenderer* m_pSpriteRenderer[(int)JobKind::Max];
    RendererParam m_tJobsParam[(int)JobKind::Max];
};

