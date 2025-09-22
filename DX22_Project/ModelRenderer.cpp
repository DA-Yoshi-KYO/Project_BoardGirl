#include "ModelRenderer.h"
#include "ShaderList.h"
#include "Camera.h"

CModelRenderer::~CModelRenderer()
{

}

void CModelRenderer::Draw()
{
    RenderTarget* pRTV = GetDefaultRTV();
    DepthStencil* pDSV = GetDefaultDSV();
    if (m_bIsDepth) SetRenderTargets(1, &pRTV, pDSV);
    else SetRenderTargets(1, &pRTV, nullptr);
    SetCullingMode(m_tParam.m_eCulling);

    CCamera* pCamera = CCamera::GetInstance().get();
    DirectX::XMFLOAT4X4 wvp[3];
    DirectX::XMMATRIX world =
        DirectX::XMMatrixScaling(m_tParam.m_f3Size.x, m_tParam.m_f3Size.y, m_tParam.m_f3Size.z) *
        DirectX::XMMatrixRotationRollPitchYaw(m_tParam.m_f3Rotate.x, m_tParam.m_f3Rotate.y, m_tParam.m_f3Rotate.z) *
        DirectX::XMMatrixTranslation(m_tParam.m_f3Pos.x, m_tParam.m_f3Pos.y, m_tParam.m_f3Pos.z);
    world = DirectX::XMMatrixTranspose(world);
    DirectX::XMStoreFloat4x4(&wvp[0], world);
    wvp[1] = pCamera->GetViewMatrix();
    wvp[2] = pCamera->GetProjectionMatrix();

    ShaderList::SetWVP(wvp);

    Model* pModel = std::get<ModelParam>(m_RendererObjectMap.find(m_sKey.c_str())->second.m_Data).m_pModel;
    pModel->SetVertexShader(ShaderList::GetVS(ShaderList::VS_WORLD));
    pModel->SetPixelShader(ShaderList::GetPS(ShaderList::PS_SPECULAR));

    for (unsigned int i = 0; i < pModel->GetMeshNum(); i++)
    {
        Model::Mesh Mesh = *pModel->GetMesh(i);
        Model::Material material = *pModel->GetMaterial(Mesh.materialID);

        ShaderList::SetMaterial(material);

        if (pModel) pModel->Draw(i);
    }
}

std::vector<Model::Mesh> CModelRenderer::GetMesh()
{
    return std::get<ModelParam>(m_RendererObjectMap.find(m_sKey)->second.m_Data).m_tMeshVec;
}
