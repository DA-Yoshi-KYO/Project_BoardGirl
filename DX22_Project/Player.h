#pragma once

#include "GameObject.h"

class CPlayer: public CGameObject
{
public: 
	void Init() override;
	void Update() override;
	DirectX::XMFLOAT3 GetForward();
	DirectX::XMFLOAT3 GetRight();
private:
	DirectX::XMFLOAT3 m_f3Velocity;
	bool m_bJump;
	void PlayerMove();
};

