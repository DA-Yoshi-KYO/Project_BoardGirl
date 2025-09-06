/// @file RendererComponent.cpp
/// @brief レンダラー用の仲介コンポーネントクラス

#include "RendererComponent.h"

std::map<std::string, Texture*> CRendererComponent::m_pTextureMap{};

CRendererComponent::~CRendererComponent()
{
}

void CRendererComponent::SetRendererParam(const RendererParam inParam)
{
	m_tParam = inParam;
}

void CRendererComponent::SetPos(const DirectX::XMFLOAT3 inPos)
{
	m_tParam.m_f3Pos = inPos;
}

void CRendererComponent::SetPos(DirectX::XMFLOAT2 inPos)
{
	m_tParam.m_f3Pos.x = inPos.x;
	m_tParam.m_f3Pos.y = inPos.y;
	m_tParam.m_f3Pos.z = 0.0f;
}

void CRendererComponent::SetSize(DirectX::XMFLOAT3 inSize)
{
	m_tParam.m_f3Size = inSize;
}

void CRendererComponent::SetSize(DirectX::XMFLOAT2 inSize)
{
	m_tParam.m_f3Size.x = inSize.x;
	m_tParam.m_f3Size.y = inSize.y;
	m_tParam.m_f3Size.z = 1.0f;
}

void CRendererComponent::SetRotation(DirectX::XMFLOAT3 inRotation)
{
	m_tParam.m_f3Rotate = inRotation;
}

void CRendererComponent::SetRotation(float inRotation)
{
	m_tParam.m_f3Rotate.x = 0.0f;
	m_tParam.m_f3Rotate.y = 0.0f;
	m_tParam.m_f3Rotate.z = inRotation;
}

void CRendererComponent::SetColor(DirectX::XMFLOAT4 inColor)
{
	m_tParam.m_f4Color = inColor;
}

void CRendererComponent::SetUVPos(DirectX::XMFLOAT2 inUVPos)
{
	m_tParam.m_f2UVPos = inUVPos;
}

void CRendererComponent::SetUVSize(DirectX::XMFLOAT2 inUVSize)
{
	m_tParam.m_f2UVSize = inUVSize;
}

void CRendererComponent::SetCullingMode(D3D11_CULL_MODE inCulling)
{
    m_tParam.m_eCulling = inCulling;
}

RendererParam CRendererComponent::GetRendererParam()
{
    return m_tParam;
}


void CRendererComponent::SetKey(std::string inKey)
{
    if (m_pTextureMap.find(inKey.c_str()) != m_pTextureMap.end())
    {
        m_sKey = inKey;
    }
    else
    {
        inKey = "NotFind:" + inKey;
        MessageBox(NULL, inKey.c_str(), "Error", MB_OK);
    }


}

void CRendererComponent::Load(const char* inPath, std::string inKey)
{
    std::string keyStr(inKey);

    auto itr = m_pTextureMap.find(keyStr.c_str());
    if (itr != m_pTextureMap.end())
    {
        return;
    }

    Texture* tex = new Texture();
    if (FAILED(tex->Create(inPath))) {
        assert(false); // Create失敗
        delete tex;
        return;
    }

    m_pTextureMap.emplace(keyStr, tex);
}

void CRendererComponent::Unload()
{
    for (auto& itr : m_pTextureMap)
    {
        delete itr.second;
        itr.second = nullptr;
    }
    m_pTextureMap.clear();
}
