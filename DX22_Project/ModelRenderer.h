#pragma once

#include "RendererComponent.h"
#include "Model.h"

class CModelRenderer : public CRendererComponent
{
public:
    using CRendererComponent::CRendererComponent;
    ~CModelRenderer();
    void Init() override;
    void Load(const char* inPath, float scale = 1.0f, Model::Flip flip = Model::Flip::None);
    void Draw() override;

private:
    std::shared_ptr<Model> m_pModel;

};

