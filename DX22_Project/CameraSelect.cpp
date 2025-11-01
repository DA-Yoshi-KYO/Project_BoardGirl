// インクルード部
#include "CameraSelect.h"

CCameraSelect::~CCameraSelect()
{

}

void CCameraSelect::Update()
{
	m_f3Pos = DirectX::XMFLOAT3(0.0f, 0.0f, -10.0f);
	m_f3Look = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_f3Up = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
}
