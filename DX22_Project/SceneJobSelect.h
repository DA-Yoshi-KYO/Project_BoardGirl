#pragma once

#include "Scene.h"
#include "Job.h"

class CSceneJobSelect : public CScene
{
public:
    void Init() override;
    void Update() override;

    static JobKind GetSelectedJob() { return m_eSelectedJob; }

private:
    static JobKind m_eSelectedJob; // 選択されたジョブの種類

};
