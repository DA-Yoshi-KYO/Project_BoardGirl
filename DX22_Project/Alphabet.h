#pragma once

#include "GameObject.h"

#define ALPHA_A DirectX::XMFLOAT2(0.0f,0.0f)
#define ALPHA_B DirectX::XMFLOAT2(0.125f,0.0f)
#define ALPHA_C DirectX::XMFLOAT2(0.25f,0.0f)
#define ALPHA_D DirectX::XMFLOAT2(0.375f,0.0f)
#define ALPHA_E DirectX::XMFLOAT2(0.5f,0.0f)
#define ALPHA_F DirectX::XMFLOAT2(0.625f,0.0f)
#define ALPHA_G DirectX::XMFLOAT2(0.75f,0.0f)
#define ALPHA_H DirectX::XMFLOAT2(0.875f,0.0f)
#define ALPHA_I DirectX::XMFLOAT2(0.0f,0.25f)
#define ALPHA_J DirectX::XMFLOAT2(0.125f,0.25f)
#define ALPHA_K DirectX::XMFLOAT2(0.25f,0.25f)
#define ALPHA_L DirectX::XMFLOAT2(0.375f,0.25f)
#define ALPHA_M DirectX::XMFLOAT2(0.5f,0.25f)
#define ALPHA_N DirectX::XMFLOAT2(0.625f,0.25f)
#define ALPHA_O DirectX::XMFLOAT2(0.75f,0.25f)
#define ALPHA_P DirectX::XMFLOAT2(0.875f,0.25f)
#define ALPHA_Q DirectX::XMFLOAT2(0.0f,0.5f)
#define ALPHA_R DirectX::XMFLOAT2(0.125f,0.5f)
#define ALPHA_S DirectX::XMFLOAT2(0.25f,0.5f)
#define ALPHA_T DirectX::XMFLOAT2(0.375f,0.5f)
#define ALPHA_U DirectX::XMFLOAT2(0.5f,0.5f)
#define ALPHA_V DirectX::XMFLOAT2(0.625f,0.5f)
#define ALPHA_W DirectX::XMFLOAT2(0.75f,0.5f)
#define ALPHA_X DirectX::XMFLOAT2(0.875f,0.5f)
#define ALPHA_Y DirectX::XMFLOAT2(0.0f,0.75f)
#define ALPHA_Z DirectX::XMFLOAT2(0.125f,0.75f)
#define ALPHA_EX DirectX::XMFLOAT2(0.25f,0.75f)
#define ALPHA_QUE DirectX::XMFLOAT2(0.375f,0.75f)
#define ALPHA_AND DirectX::XMFLOAT2(0.5f,0.75f)
#define ALPHA_PER DirectX::XMFLOAT2(0.625f,0.75f)
#define ALPHA_DUSH DirectX::XMFLOAT2(0.75f,0.75f)
#define ALPHA_AT DirectX::XMFLOAT2(0.875f,0.75f)

class CAlphabet : public CGameObject
{
public:
    ~CAlphabet();
    void Init() override;

    void SetAlphabet(DirectX::XMFLOAT2 inAlpha) { m_tParam.m_f2UVPos = inAlpha; };

private:
    DirectX::XMFLOAT2 m_f2CharUV;

};
