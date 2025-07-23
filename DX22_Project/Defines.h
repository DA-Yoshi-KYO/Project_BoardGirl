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

// フレーム定義
static const int FPS = 60;
static const float fFPS = static_cast<float>(FPS);
static const float fDeltaTime = 1.0f / fFPS; // フレーム時間(秒)

// リソースパス
#define TEXTURE_PATH(path) ("Assets/Texture/" path)
#define MODEL_PATH(path) ("Assets/Model/" path)

// 3D空間定義
#define CMETER(value) (value * 0.01f)
#define METER(value) (value * 1.0f)
#define KMETER(value) (value * 1000.0f)
#define MSEC(value) (value / fFPS)
#define CMSEC(value) MSEC(CMETER(value))
#define TERRAIN_HEIGHT_MAX KMETER(6.0f)
#define TERRAIN_SCALE (0.1f)
#define TERRAIN_CALC(value) (value * TERRAIN_SCALE)
#define TERRAIN_SIZE KMETER(1.0f * TERRAIN_SCALE)

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

// オブジェクト汎用パラメータ
struct RendererParam
{
	DirectX::XMFLOAT3 m_f3Pos = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 m_f3Size = { 1.0f,1.0f,1.0f };
	DirectX::XMFLOAT3 m_f3Rotate = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT4 m_f4Color = { 1.0f,1.0f,1.0f,1.0f };
	DirectX::XMFLOAT2 m_f2UVPos = { 0.0f,0.0f };
	DirectX::XMFLOAT2 m_f2UVSize = {1.0f,1.0f};
};

inline DirectX::XMFLOAT2 operator+(const DirectX::XMFLOAT2& lhs, const DirectX::XMFLOAT2& rhs)
{
    return { lhs.x + rhs.x, lhs.y + rhs.y };
}

inline DirectX::XMFLOAT2 operator-(const DirectX::XMFLOAT2& lhs, const DirectX::XMFLOAT2& rhs)
{
    return { lhs.x - rhs.x, lhs.y - rhs.y };
}

inline DirectX::XMFLOAT2 operator*(const DirectX::XMFLOAT2& lhs, const DirectX::XMFLOAT2& rhs)
{
    return { lhs.x * rhs.x, lhs.y * rhs.y };
}

inline DirectX::XMFLOAT2 operator/(const DirectX::XMFLOAT2& lhs, const DirectX::XMFLOAT2& rhs)
{
    return { lhs.x / rhs.x, lhs.y / rhs.y };
}

inline DirectX::XMFLOAT2 operator*(const DirectX::XMFLOAT2& lhs, float rhs)
{
    return { lhs.x * rhs, lhs.y * rhs };
}

inline DirectX::XMFLOAT2 operator/(const DirectX::XMFLOAT2& lhs, float rhs)
{
    return { lhs.x / rhs, lhs.y / rhs };
}

inline DirectX::XMFLOAT2 operator*(float lhs, const DirectX::XMFLOAT2& rhs)
{
    return { lhs * rhs.x, lhs * rhs.y };
}

inline DirectX::XMFLOAT2 operator/(float lhs, const DirectX::XMFLOAT2& rhs)
{
    return { lhs / rhs.x, lhs / rhs.y };
}

//inline DirectX::XMFLOAT2 operator+=(DirectX::XMFLOAT2& lhs, const DirectX::XMFLOAT2& rhs)
//{
//    lhs.x += rhs.x;
//    lhs.y += rhs.y;
//    return lhs;
//}

inline DirectX::XMFLOAT2 operator-=(DirectX::XMFLOAT2& lhs, const DirectX::XMFLOAT2& rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}

inline DirectX::XMFLOAT2 operator*=(DirectX::XMFLOAT2& lhs, const DirectX::XMFLOAT2& rhs)
{
    lhs.x *= rhs.x;
    lhs.y *= rhs.y;
    return lhs;
}

inline DirectX::XMFLOAT2 operator/=(DirectX::XMFLOAT2& lhs, const DirectX::XMFLOAT2& rhs)
{
    lhs.x /= rhs.x;
    lhs.y /= rhs.y;
    return lhs;
}

inline DirectX::XMFLOAT2 operator*=(DirectX::XMFLOAT2& lhs, float rhs)
{
    lhs.x *= rhs;
    lhs.y *= rhs;
    return lhs;
}

inline DirectX::XMFLOAT2 operator/=(DirectX::XMFLOAT2& lhs, float rhs)
{
    lhs.x /= rhs;
    lhs.y /= rhs;
    return lhs;
}

inline DirectX::XMFLOAT3 operator+(const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs)
{
    return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
}

inline DirectX::XMFLOAT3 operator-(const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs)
{
    return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
}

inline DirectX::XMFLOAT3 operator*(const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs)
{
    return { lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z };
}

inline DirectX::XMFLOAT3 operator/(const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs)
{
    return { lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z };
}

inline DirectX::XMFLOAT3 operator*(const DirectX::XMFLOAT3& lhs, float rhs)
{
    return { lhs.x * rhs, lhs.y * rhs, lhs.z * rhs };
}

inline DirectX::XMFLOAT3 operator/(const DirectX::XMFLOAT3& lhs, float rhs)
{
    return { lhs.x / rhs, lhs.y / rhs, lhs.z / rhs };
}

inline DirectX::XMFLOAT3 operator*(float lhs, const DirectX::XMFLOAT3& rhs)
{
    return { lhs * rhs.x, lhs * rhs.y, lhs * rhs.z };
}

inline DirectX::XMFLOAT3 operator/(float lhs, const DirectX::XMFLOAT3& rhs)
{
    return { lhs / rhs.x, lhs / rhs.y, lhs / rhs.z };
}

//DirectX::XMFLOAT3 operator+=(DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs)
//{
//    lhs.x += rhs.x;
//    lhs.y += rhs.y;
//    lhs.z += rhs.z;
//    return lhs;
//}

inline DirectX::XMFLOAT3 operator-=(DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    lhs.z -= rhs.z;
    return lhs;
}

inline DirectX::XMFLOAT3 operator*=(DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs)
{
    lhs.x *= rhs.x;
    lhs.y *= rhs.y;
    lhs.z *= rhs.z;
    return lhs;
}

inline DirectX::XMFLOAT3 operator/=(DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs)
{
    lhs.x /= rhs.x;
    lhs.y /= rhs.y;
    lhs.z /= rhs.z;
    return lhs;
}

inline DirectX::XMFLOAT3 operator*=(DirectX::XMFLOAT3& lhs, float rhs)
{
    lhs.x *= rhs;
    lhs.y *= rhs;
    lhs.z *= rhs;
    return lhs;
}

inline DirectX::XMFLOAT3 operator/=(DirectX::XMFLOAT3& lhs, float rhs)
{
    lhs.x /= rhs;
    lhs.y /= rhs;
    lhs.z /= rhs;
    return lhs;
}

inline DirectX::XMFLOAT4 operator+(const DirectX::XMFLOAT4& lhs, const DirectX::XMFLOAT4& rhs)
{
    return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w };
}

inline DirectX::XMFLOAT4 operator-(const DirectX::XMFLOAT4& lhs, const DirectX::XMFLOAT4& rhs)
{
    return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w };
}

inline DirectX::XMFLOAT4 operator*(const DirectX::XMFLOAT4& lhs, const DirectX::XMFLOAT4& rhs)
{
    return { lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w };
}

inline DirectX::XMFLOAT4 operator/(const DirectX::XMFLOAT4& lhs, const DirectX::XMFLOAT4& rhs)
{
    return { lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w };
}

inline DirectX::XMFLOAT4 operator*(const DirectX::XMFLOAT4& lhs, float rhs)
{
    return { lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs };
}

inline DirectX::XMFLOAT4 operator/(const DirectX::XMFLOAT4& lhs, float rhs)
{
    return { lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs };
}

inline DirectX::XMFLOAT4 operator*(float lhs, const DirectX::XMFLOAT4& rhs)
{
    return { lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w };
}

inline DirectX::XMFLOAT4 operator/(float lhs, const DirectX::XMFLOAT4& rhs)
{
    return { lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.w };
}

//inline DirectX::XMFLOAT4 operator+=(DirectX::XMFLOAT4& lhs, const DirectX::XMFLOAT4& rhs)
//{
//    lhs.x += rhs.x;
//    lhs.y += rhs.y;
//    lhs.z += rhs.z;
//    lhs.w += rhs.w;
//    return lhs;
//}

inline DirectX::XMFLOAT4 operator-=(DirectX::XMFLOAT4& lhs, const DirectX::XMFLOAT4& rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    lhs.z -= rhs.z;
    lhs.w -= rhs.w;
    return lhs;
}

inline DirectX::XMFLOAT4 operator*=(DirectX::XMFLOAT4& lhs, const DirectX::XMFLOAT4& rhs)
{
    lhs.x *= rhs.x;
    lhs.y *= rhs.y;
    lhs.z *= rhs.z;
    lhs.w *= rhs.w;
    return lhs;
}

inline DirectX::XMFLOAT4 operator/=(DirectX::XMFLOAT4& lhs, const DirectX::XMFLOAT4& rhs)
{
    lhs.x /= rhs.x;
    lhs.y /= rhs.y;
    lhs.z /= rhs.z;
    lhs.w /= rhs.w;
    return lhs;
}

inline DirectX::XMFLOAT4 operator*=(DirectX::XMFLOAT4& lhs, float rhs)
{
    lhs.x *= rhs;
    lhs.y *= rhs;
    lhs.z *= rhs;
    lhs.w *= rhs;
    return lhs;
}

inline DirectX::XMFLOAT4 operator/=(DirectX::XMFLOAT4& lhs, float rhs)
{
    lhs.x /= rhs;
    lhs.y /= rhs;
    lhs.z /= rhs;
    lhs.w /= rhs;
    return lhs;
}

inline DirectX::XMVECTOR operator+(const DirectX::XMVECTOR& lhs, const DirectX::XMVECTOR& rhs)
{
    return DirectX::XMVectorAdd(lhs, rhs);
}

inline DirectX::XMVECTOR operator-(const DirectX::XMVECTOR& lhs, const DirectX::XMVECTOR& rhs)
{
    return DirectX::XMVectorSubtract(lhs, rhs);
}

inline DirectX::XMVECTOR operator*(const DirectX::XMVECTOR& lhs, const DirectX::XMVECTOR& rhs)
{
    return DirectX::XMVectorMultiply(lhs, rhs);
}

inline DirectX::XMVECTOR operator/(const DirectX::XMVECTOR& lhs, const DirectX::XMVECTOR& rhs)
{
    return DirectX::XMVectorDivide(lhs, rhs);
}

inline DirectX::XMVECTOR operator*(const DirectX::XMVECTOR& lhs, float rhs)
{
    return DirectX::XMVectorScale(lhs, rhs);
}

inline DirectX::XMVECTOR operator/(const DirectX::XMVECTOR& lhs, float rhs)
{
    return DirectX::XMVectorScale(lhs, 1.0f / rhs);
}

#endif // __DEFINES_H__
