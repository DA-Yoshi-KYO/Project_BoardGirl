#include "Player.h"
#include "Input.h"
#include "BillboardRenderer.h"

void CPlayer::Init()
{
	AddComponent<CBillboardRenderer>();
	m_tParam.m_f3Pos = { 0.0f,0.0f,0.0f };
	m_tParam.m_f3Size = { 1.0f,1.0f,1.0f };
}

void CPlayer::Update()
{

}
