#pragma once

#include "Scene.h"
#include "Job.h"
#include "SelectJobs.h"

class CSceneJobSelect : public CScene
{
public:
    void Init() override;
    void Update() override;

    static JobKind GetSelectedJob() { return m_eSelectedJob; }

private:
    static JobKind m_eSelectedJob;
    CSelectJobs* m_pSelectJobs;
};
