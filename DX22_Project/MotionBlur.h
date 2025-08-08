#pragma once

#include "DirectX.h"
#include "Defines.h"
#include "Shader.h"

class CMotionBlur
{
private:
    CMotionBlur() {};

public:
    CMotionBlur(const CMotionBlur&) = delete;
    CMotionBlur& operator=(const CMotionBlur&) = delete;
    static CMotionBlur* GetInstance();
    void ReleaseInstance();

    void Init();
    void Update();
    void ExecMotionBlur();
    void StopMotionBlur();

private:
    static CMotionBlur* m_pInstance;
    struct MotionBlurState
    {
        DirectX::XMMATRIX m_mInvCurrentViewProj;
        DirectX::XMMATRIX m_mInvPrevViewProj;
        DirectX::XMFLOAT2 m_f2ScreenSize;
        DirectX::XMFLOAT2 _padding; // 16バイト境界
    }m_tState;

    DirectX::XMMATRIX m_mPrevViewProj;
    std::unique_ptr<PixelShader> m_pPS;

    ID3D11ShaderResourceView* m_pTexture[2];
    bool m_bExec;
};
