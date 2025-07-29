/// @file RendererComponent.h
/// @brief レンダラー用の仲介コンポーネントクラス

#pragma once

#include "Component.h"
#include "Defines.h"
#include "Texture.h"

class CRendererComponent : public CComponent
{
public:
	using CComponent::CComponent;
    virtual ~CRendererComponent();

	// 各種パラメータの設定
	/// <summary>
	/// レンダラーの統合パラメータを設定
	/// </summary>
	/// <param name="inParam">設定するレンダラーのパラメータ</param>
	void SetRendererParam(const RendererParam inParam);
	/// <summary>
	/// 表示するローカル座標を設定
	/// </summary>
	/// <param name="inPos">設定する座標の値(DirectX::XMFLOAT3)</param>
	void SetPos(DirectX::XMFLOAT3 inPos);
	/// <summary>
	/// 表示する2D座標を設定
	/// </summary>
	/// <param name="inPos">設定する座標の値(DirectX::XMFLOAT2)</param>
	void SetPos(DirectX::XMFLOAT2 inPos);
	/// <summary>
	/// 表示するローカルサイズを設定
	/// </summary>
	/// <param name="inSize">設定するサイズの値(DirectX::XMFLOAT3)</param>
	void SetSize(DirectX::XMFLOAT3 inSize);
	/// <summary>
	/// 表示する2Dサイズを設定
	/// </summary>
	/// <param name="inSize">設定するサイズの値(DirectX::XMFLOAT2)</param>
	void SetSize(DirectX::XMFLOAT2 inSize);
	/// <summary>
	/// 表示するローカル回転を設定
	/// </summary>
	/// <param name="inRotation">設定する回転の値(DirectX::XMFLOAT3)</param>
	void SetRotation(DirectX::XMFLOAT3 inRotation);
	/// <summary>
	/// 表示する2D回転を設定
	/// </summary>
	/// <param name="inRotation">設定する回転の値(DirectX::XMFLOAT2)</param>
	void SetRotation(float inRotation);
	/// <summary>
	/// 表示する色を設定
	/// </summary>
	/// <param name="inColor">設定する色の値(DirectX::XMFLOAT4)</param>
	void SetColor(DirectX::XMFLOAT4 inColor);
	/// <summary>
	/// UV座標の位置を設定
	/// </summary>
	/// <param name="inUVPos">設定するUV座標の位置(DirectX::XMFLOAT2)</param>
	void SetUVPos(DirectX::XMFLOAT2 inUVPos);
	/// <summary>
	/// UV座標のサイズを設定
	/// </summary>
	/// <param name="inUVSize">設定するUV座標のサイズ(DirectX::XMFLOAT2)</param>
	void SetUVSize(DirectX::XMFLOAT2 inUVSize);

    void SetKey(std::string inKey);
    static void Load(const char* inPath, std::string inKey);
    static void Unload();

protected:
    static std::map<std::string, Texture*> m_pTextureMap;
    std::string m_sKey;
	RendererParam m_tParam;	// レンダラーの統合パラメータ

};
