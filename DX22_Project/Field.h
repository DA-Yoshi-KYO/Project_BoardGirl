#pragma once

#include "GameObject.h"
#include "ModelRenderer.h"

struct HitResult
{
    bool        bHit = false;
    DirectX::XMFLOAT3 Position{};
    DirectX::XMFLOAT3 Normal{};
    float       Distance = FLT_MAX;
    size_t      MeshIndex = SIZE_MAX;
    size_t      TriIndex = SIZE_MAX;
};

class CField : public CGameObject
{
public:
    ~CField();
    void Init() override;
    static HitResult RayIntersectsTriangle(const DirectX::XMFLOAT3& rayOrigin, const DirectX::XMFLOAT3& rayDir);
    static bool Check(const DirectX::XMVECTOR& rayOrigin, const DirectX::XMVECTOR& rayDir, const DirectX::XMFLOAT3& v0, const DirectX::XMFLOAT3& v1, const DirectX::XMFLOAT3& v2, float& outT);
private:
    static std::vector<Model::Mesh> m_Mesh;
    static HitResult m_tResult;
};
