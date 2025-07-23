#pragma once

#include "Camera.h"

class CCameraSelect : public CCamera
{
public:
    virtual ~CCameraSelect();
    void Update() final;
};
