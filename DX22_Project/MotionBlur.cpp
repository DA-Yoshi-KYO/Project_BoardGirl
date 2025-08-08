#include "MotionBlur.h"
#include "Camera.h"

CMotionBlur* CMotionBlur::m_pInstance = nullptr;

CMotionBlur* CMotionBlur::GetInstance()
{
    if (m_pInstance == nullptr)
    {
        m_pInstance = new CMotionBlur();
    }
    return m_pInstance;
}

void CMotionBlur::ReleaseInstance()
{
    if (m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }
}

void CMotionBlur::Init()
{
    m_pPS = std::make_unique<PixelShader>();

    m_pPS->Load("Shader/PS_MotionBlur.cso");

    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = SCREEN_WIDTH;
    desc.Height = SCREEN_HEIGHT;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

    ID3D11Texture2D* colorTex = nullptr;
    GetDevice()->CreateTexture2D(&desc, nullptr, &colorTex);

    GetDevice()->CreateShaderResourceView(colorTex, nullptr, &m_pTexture[0]);

    // 深度バッファ
    D3D11_TEXTURE2D_DESC depthDesc = {};
    depthDesc.Width = SCREEN_WIDTH;
    depthDesc.Height = SCREEN_HEIGHT;
    depthDesc.MipLevels = 1;
    depthDesc.ArraySize = 1;
    depthDesc.Format = DXGI_FORMAT_R24G8_TYPELESS; 
    depthDesc.SampleDesc.Count = 1;
    depthDesc.Usage = D3D11_USAGE_DEFAULT;
    depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;

    ID3D11Texture2D* depthTex = nullptr;
    GetDevice()->CreateTexture2D(&depthDesc, nullptr, &depthTex);

    D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
    dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;

    GetDevice()->CreateShaderResourceView(depthTex, &srvDesc, &m_pTexture[1]);

    m_bExec = false;
}

void CMotionBlur::Update()
{
    if (m_bExec)
    {
        DirectX::XMFLOAT4X4 view = CCamera::GetInstance(CCamera::GetCameraKind())->GetViewMatrix(false);
        DirectX::XMFLOAT4X4 proj = CCamera::GetInstance(CCamera::GetCameraKind())->GetProjectionMatrix(false);
        DirectX::XMMATRIX mView;
        mView = DirectX::XMLoadFloat4x4(&view);
        DirectX::XMMATRIX mProj;
        mProj = DirectX::XMLoadFloat4x4(&proj);
        DirectX::XMMATRIX mViewProj = mView * mProj;
        m_tState.m_mInvCurrentViewProj = DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, mViewProj));
        m_tState.m_mInvPrevViewProj = DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, m_mPrevViewProj));
        m_tState.m_f2ScreenSize = DirectX::XMFLOAT2(SCREEN_WIDTH, SCREEN_HEIGHT);

        m_pPS->WriteBuffer(0, &m_tState);
        m_pPS->SetTexture(0, m_pTexture[0]);
        m_pPS->SetTexture(1, m_pTexture[1]);

        m_mPrevViewProj = mViewProj;
    }
}

void CMotionBlur::ExecMotionBlur()
{
    m_bExec = true;
}

void CMotionBlur::StopMotionBlur()
{
    m_bExec = false;
}
