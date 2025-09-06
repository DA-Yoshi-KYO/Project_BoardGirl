#pragma once

#include "Camera.h"

class CCameraDebug : public CCamera
{
public:
	CCameraDebug();
	virtual ~CCameraDebug();
	void Update() final;
private:
	float m_radXZ;
	float m_radY;
	float m_radius;
};
