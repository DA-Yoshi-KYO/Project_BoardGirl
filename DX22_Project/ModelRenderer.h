#pragma once

#include "RendererComponent.h"
#include "Model.h"

/// <summary>
/// モデル描画を扱うコンポーネントクラス
/// </summary>
class CModelRenderer : public CRendererComponent
{
public:
	using CRendererComponent::CRendererComponent;
	~CModelRenderer();
    void Init() override;
	void Draw() override;

	/// <summary>
	/// Mesh情報を取得
	/// </summary>
	/// <returns>
    /// (std::vector<Model::Mesh>)読み込まれているモデルのメッシュ情報ベクター
    /// </returns>
	std::vector<Model::Mesh> GetMesh();

	/// <summary>
	/// 深度バッファを使用するかどうかの指定
	/// </summary>
	/// <param name="isDepth">
    /// true:深度バッファ使用 false:深度バッファ不使用
    /// </param>
	void SetDepth(bool isDepth) { m_bIsDepth = isDepth; }

private:
	bool m_bIsDepth;    // 深度バッファを使用するかどうか

};
