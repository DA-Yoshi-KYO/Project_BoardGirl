/// @file RendererComponent.cpp
/// @brief レンダラー用の仲介コンポーネントクラス

#include "RendererComponent.h"

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
