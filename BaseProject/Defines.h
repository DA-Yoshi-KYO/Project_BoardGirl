#ifndef __DEFINES_H__
#define __DEFINES_H__

// インクルード部
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
#include <algorithm>
#include <functional>
#include <d3d11.h>

// std::min, std::maxを使用するための定義
#undef min
#undef max

// フレーム定義
static const int FPS = 60;
static const float fFPS = static_cast<float>(FPS);
static const float fDeltaTime = 1.0f / fFPS; // フレーム時間(秒)

// リソースパス
#define TEXTURE_PATH(path) ("Assets/Texture/" path)
#define MODEL_PATH(path) ("Assets/Model/" path)
#define AUDIO_PATH(path) ("Assets/Audio/" path)

// 3D空間定義
#define CMETER(value) (value * 0.01f)
#define METER(value) (value * 1.0f)
#define KMETER(value) (value * 1000.0f)
#define MSEC(value) (value / fFPS)
#define CMSEC(value) MSEC(CMETER(value))

// フィールド定義
static const DirectX::XMFLOAT3 ChunkSize = { 100.0f, 100.0f, 100.0f };  // 描画するチャンクのサイズ

// タイトル
static const char* APP_TITLE = "BoardGirl";

// 画面サイズ
static const int SCREEN_WIDTH = 1280;
static const int SCREEN_HEIGHT = 720;

// グリッドサイズ(デバッグ用
static const int	DEBUG_GRID_NUM = 10;			// グリッド中心から端までの線の本数
static const float	DEBUG_GRID_MARGIN = METER(1.0f);	// グリッド配置幅

#endif // __DEFINES_H__
