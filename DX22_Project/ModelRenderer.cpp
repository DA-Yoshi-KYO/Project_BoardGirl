#include "ModelRenderer.h"
#include "ShaderList.h"
#include "Camera.h"

CModelRenderer::~CModelRenderer()
{
}

void CModelRenderer::Init()
{
    m_pModel = nullptr;
}

void CModelRenderer::Load(const char* inPath, float scale, Model::Flip flip)
{
    m_pModel = std::make_shared<Model>();
    if (!m_pModel->Load(inPath, scale, flip)) MessageBox(NULL, inPath, "Error", MB_OK);


    for (unsigned int i = 0; i < m_pModel->GetMeshNum(); i++)
    {
        Model::Mesh Mesh = *m_pModel->GetMesh(i);
        m_MeshVec.push_back(Mesh);
    }
}

void CModelRenderer::Draw()
{
    RenderTarget* pRTV = GetDefaultRTV();
    DepthStencil* pDSV = GetDefaultDSV();
    SetRenderTargets(1, &pRTV, pDSV);

    CCamera* pCamera = CCamera::GetInstance(CCamera::GetCameraKind()).get();
    DirectX::XMFLOAT4X4 wvp[3];
    DirectX::XMMATRIX world =
        DirectX::XMMatrixScaling(m_tParam.m_f3Size.x, m_tParam.m_f3Size.y, m_tParam.m_f3Size.z) *
        DirectX::XMMatrixRotationRollPitchYaw(m_tParam.m_f3Rotate.x, m_tParam.m_f3Rotate.y, m_tParam.m_f3Rotate.z) *
        DirectX::XMMatrixTranslation(m_tParam.m_f3Pos.x, m_tParam.m_f3Pos.y, m_tParam.m_f3Pos.z);
    DirectX::XMStoreFloat4x4(&wvp[0], world);
    wvp[1] = pCamera->GetViewMatrix();
    wvp[2] = pCamera->GetProjectionMatrix();

    ShaderList::SetWVP(wvp);

    m_pModel->SetVertexShader(ShaderList::GetVS(ShaderList::VS_WORLD));
    m_pModel->SetPixelShader(ShaderList::GetPS(ShaderList::PS_LAMBERT));

    for (unsigned int i = 0; i < m_pModel->GetMeshNum(); i++)
    {
        Model::Mesh Mesh = *m_pModel->GetMesh(i);
        Model::Material material = *m_pModel->GetMaterial(Mesh.materialID);

        ShaderList::SetMaterial(material);

        if (m_pModel) m_pModel->Draw(i);
    }
}

std::vector<Model::Mesh> CModelRenderer::GetMesh()
{
    return m_MeshVec;
}
