#pragma once

#include "RendererComponent.h"
#include "Model.h"

class CModelRenderer : public CRendererComponent
{
public:
    using CRendererComponent::CRendererComponent;
    ~CModelRenderer();
    void Draw() override;
    std::vector<Model::Mesh> GetMesh();
    void SetDepth(bool isDepth) { m_bIsDepth = isDepth; }

private:
    bool m_bIsDepth = true;

};

