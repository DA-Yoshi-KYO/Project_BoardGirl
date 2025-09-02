#pragma once
#include <DirectXMath.h>

typedef struct Vector3
{
    float x;
    float y;
    float z;

    Vector3()
        : x(), y(), z()
    {

    }
    Vector3(float inX, float inY, float inZ)
        : x(inX), y(inY), z(inZ)
    {

    }
    Vector3(DirectX::XMFLOAT3 inFloat3)
        : x(inFloat3.x), y(inFloat3.y), z(inFloat3.z)
    {

    }

    void operator=(DirectX::XMFLOAT3 inFloat3)
    {
        x = inFloat3.x;
        y = inFloat3.y;
        z = inFloat3.z;
    }
    DirectX::XMFLOAT3 ConvertFloat3() { return DirectX::XMFLOAT3(x, y, z); }

};
