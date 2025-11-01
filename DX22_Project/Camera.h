#pragma once

// インクルード部
#include <DirectXMath.h>
#include <memory>

// カメラの種類
enum CameraKind
{
	CAM_DEBUG,
	CAM_PLAYER,
	CAM_SELECT,

	MAX_CAMERA // カメラ最大数 
};

/// <summary>
/// カメラを扱うシングルトンクラス
/// </summary>
class CCamera
{	
public:
	CCamera();
	virtual ~CCamera();
	virtual void Update() = 0;

	/// <summary>
	/// カメラのView座標を取得
	/// </summary>
	/// <param name="transpose">
	/// 転置を行うかどうか
	/// </param>
	/// <returns>
	/// (DirectX::XMFLOAT4X4)カメラのView座標
	/// </returns>
	DirectX::XMFLOAT4X4 GetViewMatrix(bool transpose = true);

	/// <summary>
	/// カメラのProjection座標を取得
	/// </summary>
	/// <param name="transpose">
	/// 転置を行うかどうか
	/// </param>
	/// <returns>
	/// (DirectX::XMFLOAT4X4)カメラのProjection座標
	/// </returns>
	DirectX::XMFLOAT4X4 GetProjectionMatrix(bool transpose = true);

	/// <summary>
	/// カメラの座標を取得
	/// </summary>
	/// <returns>
	/// (DirectX::XMFLOAT3)カメラの座標
	/// </returns>
	DirectX::XMFLOAT3 GetPos() { return m_f3Pos; }

	/// <summary>
	/// カメラの注視点を取得
	/// </summary>
	/// <returns>
	/// (DirectX::XMFLOAT3)カメラの注視点
	/// </returns>
	DirectX::XMFLOAT3 GetLook() { return m_f3Look; }

	/// <summary>
	/// カメラの上方向ベクトルを取得
	/// </summary>
	/// <returns>
	/// (DirectX::XMFLOAT3)カメラの上方向ベクトル
	/// </returns>
	DirectX::XMFLOAT3 GetUp() { return m_f3Up; }

	/// <summary>
	/// カメラの2DWorld座標を取得
	/// </summary>
	/// <param name="rotate">
	/// z軸回転(ラジアン角)
	/// </param>
	/// <param name="transpose">
	/// 転置を行うかどうか
	/// </param>
	/// <returns>
	/// (DirectX::XMFLOAT4X4)カメラの2DWorld座標
	/// </returns>
	static const DirectX::XMFLOAT4X4 Get2DWolrdMatrix(float rotate = 0.0f, bool transpose = true);

	/// <summary>
	/// カメラの2DView座標を取得
	/// </summary>
	/// <param name="transpose">
	/// 転置を行うかどうか
	/// </param>
	/// <returns>
	/// (DirectX::XMFLOAT4X4)カメラの2DView座標
	/// </returns>
	static const DirectX::XMFLOAT4X4 Get2DViewMatrix(bool transpose = true);

	/// <summary>
	/// カメラの2DProjection座標を取得
	/// </summary>
	/// <param name="transpose">
	/// 転置を行うかどうか
	/// </param>
	/// <returns>
	/// (DirectX::XMFLOAT4X4)カメラの2DProjection座標
	/// </returns>
	static const DirectX::XMFLOAT4X4 Get2DProjectionMatrix(bool transpose = true);

	/// <summary>
	/// CCameraのシングルトンインスタンスを取得
	/// </summary>
	/// <returns>
	/// (std::unique_ptr<CCamera>&)CCameraのインスタンス
	/// </returns>
	static std::unique_ptr<CCamera>& GetInstance();

	/// <summary>
	/// 使用するカメラの種類を指定
	/// </summary>
	/// <param name="kind">
	/// カメラの種類
	/// </param>
	static void SetCameraKind(CameraKind kind);

protected:
	DirectX::XMFLOAT3 m_f3Pos;  // 座標
	DirectX::XMFLOAT3 m_f3Look; // 注視点
	DirectX::XMFLOAT3 m_f3Up;   // 上方向ベクトル
	float m_fFovy;      // 縦方向視野角
	float m_fAspect;    // アスペクト比
	float m_fNear;      // 最近距離
	float m_fFar;       // 最遠距離

private:
	static CameraKind m_eCameraKind;    // 現在のカメラの種類

};
