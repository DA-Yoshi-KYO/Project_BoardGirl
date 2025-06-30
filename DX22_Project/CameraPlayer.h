#pragma once

#include "Camera.h"

class CCameraPlayer : public CCamera
{
public:
	virtual ~CCameraPlayer();
	void Update() final;
};

