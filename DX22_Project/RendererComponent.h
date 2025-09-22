#pragma once

// インクルード部
#include "Component.h"
#include "Texture.h"
#include "Model.h"
#include <variant>

// 描画するオブジェクトの種類
enum class RendererKind
{
	Texture,
	Model,
};

// オブジェクトの汎用パラメータ
struct RendererParam
{
	DirectX::XMFLOAT3 m_f3Pos;
	DirectX::XMFLOAT3 m_f3Size;
	DirectX::XMFLOAT3 m_f3Rotate;
	DirectX::XMFLOAT4 m_f4Color;
	DirectX::XMFLOAT2 m_f2UVPos;
	DirectX::XMFLOAT2 m_f2UVSize;
	D3D11_CULL_MODE m_eCulling;
};

// モデル用の使用パラメータ
struct ModelParam
{
    Model* m_pModel;
    std::vector<Model::Mesh> m_tMeshVec;
};

// 描画するオブジェクトの情報
struct RendererObject
{
	RendererKind m_eKind;
    std::variant<Texture*, ModelParam> m_Data;
};

/// <summary>
/// レンダラー用の仲介コンポーネントクラス
/// </summary>
class CRendererComponent : public CComponent
{
public:
	using CComponent::CComponent;
	virtual ~CRendererComponent();

	// 各種パラメータの設定
	/// <summary>
	/// レンダラーの統合パラメータを設定
	/// </summary>
	/// <param name="inParam">
    /// 設定するレンダラーのパラメータ
    /// </param>
	void SetRendererParam(const RendererParam inParam);

	/// <summary>
	/// 表示するローカル座標を設定
	/// </summary>
	/// <param name="inPos">
    /// 設定する座標の値(DirectX::XMFLOAT3)
    /// </param>
	void SetPos(DirectX::XMFLOAT3 inPos);

	/// <summary>
	/// 表示する2D座標を設定
	/// </summary>
	/// <param name="inPos">
    /// 設定する座標の値(DirectX::XMFLOAT2)
    /// </param>
	void SetPos(DirectX::XMFLOAT2 inPos);

	/// <summary>
	/// 表示するローカルサイズを設定
	/// </summary>
	/// <param name="inSize">
    /// 設定するサイズの値(DirectX::XMFLOAT3)
    /// </param>
	void SetSize(DirectX::XMFLOAT3 inSize);

	/// <summary>
	/// 表示する2Dサイズを設定
	/// </summary>
	/// <param name="inSize">
    /// 設定するサイズの値(DirectX::XMFLOAT2)
    /// </param>
	void SetSize(DirectX::XMFLOAT2 inSize);

	/// <summary>
	/// 表示するローカル回転を設定
	/// </summary>
	/// <param name="inRotation">
    /// 設定する回転の値(DirectX::XMFLOAT3)
    /// </param>
	void SetRotation(DirectX::XMFLOAT3 inRotation);

	/// <summary>
	/// 表示する2D回転を設定
	/// </summary>
	/// <param name="inRotation">
    /// 設定する回転の値(DirectX::XMFLOAT2)
    /// </param>
	void SetRotation(float inRotation);

	/// <summary>
	/// 表示する色を設定
	/// </summary>
	/// <param name="inColor">
    /// 設定する色の値(DirectX::XMFLOAT4)
    /// </param>
	void SetColor(DirectX::XMFLOAT4 inColor);

	/// <summary>
	/// UV座標の位置を設定
	/// </summary>
	/// <param name="inUVPos">
    /// 設定するUV座標の位置(DirectX::XMFLOAT2)
    /// </param>
	void SetUVPos(DirectX::XMFLOAT2 inUVPos);

	/// <summary>
	/// UV座標のサイズを設定
	/// </summary>
	/// <param name="inUVSize">
    /// 設定するUV座標のサイズ(DirectX::XMFLOAT2)
    /// </param>
	void SetUVSize(DirectX::XMFLOAT2 inUVSize);

	/// <summary>
	/// 表現技法の変更
	/// </summary>
	/// <param name="inCulling">
	/// カリングモード
	/// </param>
	/// <param name="・D3D11_CULL_NONE">
	/// カリングしない(表裏どちらも描画)
	/// </param>
	/// <param name="・D3D11_CULL_FRONT">
	/// 表面カリング(裏面のみ描画)
	/// </param>
	/// <param name="・D3D11_CULL_BACK">
	/// 裏面カリング(表面のみ描画)
	/// </param>
	void SetCullingMode(D3D11_CULL_MODE inCulling);

	/// <summary>
	/// 描画用のパラメータを取得
	/// </summary>
	/// <returns>
	/// 描画用パラメータをまとめた構造体
	/// </returns>
	RendererParam GetRendererParam();

	/// <summary>
	/// モデル・テクスチャをロードし、キー位置に登録する
	/// </summary>
    /// <param name="inKind">
    /// モデルorテクスチャ
    /// </param>
	/// <param name="inPath">
	/// テクスチャのパス
	/// </param>
	/// <param name="inKey">
	/// 登録するキー
	/// </param>
	/// <param name="scale">
	/// モデルのスケール(scale倍)
	/// </param>
	/// <param name="flip">
	/// モデルのフリップ
	/// </param>
	static void Load(RendererKind inKind, const char* inPath, std::string inKey, float scale = 1.0f, Model::Flip flip = Model::Flip::None);

	/// <summary>
	/// 読み込んだテクスチャの解放
	/// </summary>
	static void UnLoad();

	/// <summary>
	/// 描画に使用するテクスチャのキーをセット
	/// </summary>
	/// <param name="inKey">
	/// ロードする際に同時に登録したキー
	/// </param>
	void SetKey(std::string inKey);

protected:
	RendererParam m_tParam;	// レンダラーの統合パラメータ
	static std::map<std::string, RendererObject> m_RendererObjectMap;   // 読み込んだオブジェクトをキー位置に保存するマップ
	std::string m_sKey; // 呼び出し用のキー

};
