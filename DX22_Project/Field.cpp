// インクルード部
#include "Field.h"
#include "Main.h"
#include "Oparation.h"

std::vector<Model::Mesh> CField::m_Mesh = {};
HitResult CField::m_tResult = {};

CField::~CField()
{
}

void CField::Init()
{
    CModelRenderer* pRenderer = AddComponent<CModelRenderer>();
    pRenderer->Load(MODEL_PATH("Ground.obj"), 1.0f, Model::Flip::XFlip);
    pRenderer->SetDepth(false);
    m_Mesh = pRenderer->GetMesh();
    m_tParam.m_f3Pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
}

HitResult CField::RayIntersectsTriangle(const DirectX::XMFLOAT3& rayOrigin, const DirectX::XMFLOAT3& rayDir)
{
    DirectX::XMVECTOR ro = DirectX::XMLoadFloat3(&rayOrigin);
    DirectX::XMVECTOR rd = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&rayDir));

    m_tResult.bHit = false;
    m_tResult.Position = {};
    m_tResult.Normal = {};
    m_tResult.Distance = FLT_MAX;
    m_tResult.MeshIndex = SIZE_MAX;
    m_tResult.TriIndex = SIZE_MAX;
    
    for (unsigned int idx = 0; idx < m_Mesh.size(); idx++)
    {
        Model::Vertices ver = m_Mesh[idx].vertices;
        Model::Indices ind = m_Mesh[idx].indices;

        for (unsigned int i = 0; i < ind.size(); i+=3)
        {
            const DirectX::XMFLOAT3& v0 = ver[ind[i]].pos;
            const DirectX::XMFLOAT3& v1 = ver[ind[i + 1]].pos;
            const DirectX::XMFLOAT3& v2 = ver[ind[i + 2]].pos;

            float t = 0.0f;
            if (Check(ro, rd, v0, v1, v2, t))
            {
                if (t < m_tResult.Distance)
                {
                    m_tResult.bHit = true;
                    m_tResult.Distance = t;
                    m_tResult.MeshIndex = idx;
                    m_tResult.TriIndex = i / 3;

                    DirectX::XMVECTOR hitPos = ro + rd * t;
                    DirectX::XMStoreFloat3(&m_tResult.Position, hitPos);

                    DirectX::XMVECTOR normal = DirectX::XMVector3Normalize(
                        DirectX::XMVector3Cross(XMLoadFloat3(&v1) - XMLoadFloat3(&v0),
                            XMLoadFloat3(&v2) - XMLoadFloat3(&v0)));
                    DirectX::XMStoreFloat3(&m_tResult.Normal, normal);
                }
            }

        }
    }
    return m_tResult;
}

bool CField::Check(const DirectX::XMVECTOR& rayOrigin, const DirectX::XMVECTOR& rayDir, const DirectX::XMFLOAT3& v0, const DirectX::XMFLOAT3& v1, const DirectX::XMFLOAT3& v2, float& outT)
{
    const float EPSILON = 1e-6f;
    DirectX::XMVECTOR V0 = DirectX::XMLoadFloat3(&v0);
    DirectX::XMVECTOR V1 = DirectX::XMLoadFloat3(&v1);
    DirectX::XMVECTOR V2 = DirectX::XMLoadFloat3(&v2);

    DirectX::XMVECTOR v0v1 = V1 - V0;
    DirectX::XMVECTOR v0v2 = V2 - V0;
    DirectX::XMVECTOR pvec = DirectX::XMVector3Cross(rayDir, v0v2);
    float det = DirectX::XMVectorGetX(DirectX::XMVector3Dot(v0v1, pvec));

    if (fabs(det) < EPSILON) return false;

    float invDet = 1.0f / det;
    DirectX::XMVECTOR tvec = rayOrigin - V0;
    float u = DirectX::XMVectorGetX(DirectX::XMVector3Dot(tvec, pvec)) * invDet;
    if (u < 0 || u > 1) return false;

    DirectX::XMVECTOR qvec = DirectX::XMVector3Cross(tvec, v0v1);
    float v = DirectX::XMVectorGetX(DirectX::XMVector3Dot(rayDir, qvec)) * invDet;
    if (v < 0 || u + v > 1) return false;

    float t = DirectX::XMVectorGetX(DirectX::XMVector3Dot(v0v2, qvec)) * invDet;
 
    outT = t;
    return true;
}

