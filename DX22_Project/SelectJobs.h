#pragma once

#include "GameObject.h"
#include "Job.h"
#include "BillboardRenderer.h"

class CSelectJobs : public CGameObject
{
public:
    void Init() override;
    void Update() override;
    void Draw() override;
    void SetMove(bool next) { if (isMove) return; isMove = true; isNext = next; }
    bool IsMove() const { return isMove; }

    static JobKind GetSelectedJob() { return m_eSelectedJob; }

private:
    CBillboardRenderer* m_pSpriteRenderer[(int)JobKind::Max];
    RendererParam m_tJobsParam[(int)JobKind::Max];
    RendererParam m_tTempParam[(int)JobKind::Max];
    bool isMove;
    bool isNext;
    static JobKind m_eSelectedJob;
    bool m_bEnd;
    bool m_bTransition;
};

