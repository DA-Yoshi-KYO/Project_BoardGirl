#pragma once

#include "GameObject.h"

class CPlayer: public CGameObject
{
public: 
	void Init() override;
	void Update() override;
};

