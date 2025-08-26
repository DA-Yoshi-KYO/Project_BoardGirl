#pragma once

#include "GameObject.h"
#include "imgui.h"

constexpr ImVec2 ce_f2InspecterSize = ImVec2(250, 30);

class CDebugSystem
{
private:
    CDebugSystem();
public:
    ~CDebugSystem();
    CDebugSystem(const CDebugSystem&) = delete;
    CDebugSystem& operator=(const CDebugSystem&) = delete;
    static CDebugSystem* GetInstance();
    void ReleaseInstance();
    void ReleaseGameObject();

    void Init();
    void Uninit();
    void Update();
    void Draw();

    bool IsUpdate() { return m_bUpdate; }
private:
    static CDebugSystem* m_pInstance;
    CGameObject* m_pObject;
    bool m_bUpdate;

private:
    void DrawHierarchy();
    void DrawCameraParam();
    void DrawUpdateTick();
    void DrawSceneSelect();

};
