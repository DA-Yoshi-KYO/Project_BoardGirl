#include "CameraSelect.h"

CCameraSelect::~CCameraSelect()
{

}

void CCameraSelect::Update()
{
    m_f3Pos = { 0.0f, 0.0f, -10.0f };
    m_f3Look = { 0.0f, 0.0f, 0.0f };
    m_f3Up = { 0.0f, 1.0f, 0.0f };
}
