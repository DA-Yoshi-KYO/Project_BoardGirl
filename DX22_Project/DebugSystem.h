#pragma once

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

    void Init();
    void Uninit();
    void Update();
    void Draw();

private:
    static CDebugSystem* m_pInstance;

};
