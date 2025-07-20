#pragma once

#include "RendererComponent.h"
#include "Model.h"

class CModelRenderer : public CRendererComponent
{
public:
    using CRendererComponent::CRendererComponent;
    ~CModelRenderer();
    void Init() override;
    void Load(const char* inPath);
    void Draw() override;

private:
    std::shared_ptr<Model> m_pModel;

};

