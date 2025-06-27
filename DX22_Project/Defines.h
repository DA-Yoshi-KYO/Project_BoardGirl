#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <assert.h>
#include <Windows.h>
#include <stdarg.h>
#include <DirectXMath.h>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <array>

static const int FPS = 60;
static const float fFPS = static_cast<float>(FPS);

// ���\�[�X�p�X
#define TEXTURE_PATH(path) ("Assets/Texture/" path)

// 3D��Ԓ�`
#define CMETER(value) (value * 0.01f)
#define METER(value) (value * 1.0f)
#define KMETER(value) (value * 1000.0f)
#define MSEC(value) (value / fFPS)
#define CMSEC(value) MSEC(CMETER(value))
static const float GRAVITY = 0.98f;

// �^�C�g��
static const char* APP_TITLE = "BoardGirl";

// ��ʃT�C�Y
static const int SCREEN_WIDTH = 1280;
static const int SCREEN_HEIGHT = 720;

// �O���b�h�T�C�Y(�f�o�b�O�p
static const int	DEBUG_GRID_NUM = 10;			// �O���b�h���S����[�܂ł̐��̖{��
static const float	DEBUG_GRID_MARGIN = METER(1.0f);	// �O���b�h�z�u��

struct RendererParam
{
	DirectX::XMFLOAT3 m_f3Pos = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 m_f3Size = { 1.0f,1.0f,1.0f };
	DirectX::XMFLOAT3 m_f3Rotate = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT4 m_f4Color = { 1.0f,1.0f,1.0f,1.0f };
	DirectX::XMFLOAT2 m_f2UVPos = { 0.0f,0.0f };
	DirectX::XMFLOAT2 m_f2UVSize = {1.0f,1.0f};
};

#endif // __DEFINES_H__