// インクルード部
#include "RendererComponent.h"

// 静的変数の初期化
std::map<std::string, RendererObject> CRendererComponent::m_RendererObjectMap = {};

CRendererComponent::~CRendererComponent()
{

}

void CRendererComponent::SetRendererParam(const RendererParam inParam)
{
	m_tParam = inParam;
}

void CRendererComponent::SetPos(const DirectX::XMFLOAT3 inPos)
{
	m_tParam.m_f3Pos = inPos;
}

void CRendererComponent::SetPos(DirectX::XMFLOAT2 inPos)
{
	m_tParam.m_f3Pos.x = inPos.x;
	m_tParam.m_f3Pos.y = inPos.y;
	m_tParam.m_f3Pos.z = 0.0f;
}

void CRendererComponent::SetSize(DirectX::XMFLOAT3 inSize)
{
	m_tParam.m_f3Size = inSize;
}

void CRendererComponent::SetSize(DirectX::XMFLOAT2 inSize)
{
	m_tParam.m_f3Size.x = inSize.x;
	m_tParam.m_f3Size.y = inSize.y;
	m_tParam.m_f3Size.z = 1.0f;
}

void CRendererComponent::SetRotation(DirectX::XMFLOAT3 inRotation)
{
	m_tParam.m_f3Rotate = inRotation;
}

void CRendererComponent::SetRotation(float inRotation)
{
	m_tParam.m_f3Rotate.x = 0.0f;
	m_tParam.m_f3Rotate.y = 0.0f;
	m_tParam.m_f3Rotate.z = inRotation;
}

void CRendererComponent::SetColor(DirectX::XMFLOAT4 inColor)
{
	m_tParam.m_f4Color = inColor;
}

void CRendererComponent::SetUVPos(DirectX::XMFLOAT2 inUVPos)
{
	m_tParam.m_f2UVPos = inUVPos;
}

void CRendererComponent::SetUVSize(DirectX::XMFLOAT2 inUVSize)
{
	m_tParam.m_f2UVSize = inUVSize;
}

void CRendererComponent::SetCullingMode(D3D11_CULL_MODE inCulling)
{
	m_tParam.m_eCulling = inCulling;
}

RendererParam CRendererComponent::GetRendererParam()
{
	return m_tParam;
}

void CRendererComponent::SetKey(std::string inKey)
{
	// Map内から引数のキーが存在しているかチェック
	if (m_RendererObjectMap.find(inKey.c_str()) != m_RendererObjectMap.end())
	{
		// 存在していたらそのキーを設定する
		m_sKey = inKey;
	}
	else
	{
		// 存在していなかったらエラーメッセージを送信する
		inKey = "NotFind:" + inKey;
		MessageBox(NULL, inKey.c_str(), "Error", MB_OK);
	}
}

void CRendererComponent::Load(RendererKind inKind, const char* inPath, std::string inKey, float scale, Model::Flip flip)
{
	// そのキー位置に既にオブジェクトがロード済みかをチェックする
	auto itr = m_RendererObjectMap.find(inKey.c_str());
	if (itr != m_RendererObjectMap.end())
	{
		// ロード済みなら処理を飛ばす
		return;
	}

	RendererObject tObject{};   // マップに登録するオブジェクトのデータ
	tObject.m_eKind = inKind;   // オブジェクトの種類をセット

	Texture* pTexture = nullptr;    // 読み込み用テクスチャクラスポインタ
	Model* pModel = nullptr;        // 読み込み用モデルクラスポインタ

	switch (tObject.m_eKind)
	{
	case RendererKind::Texture:
        // テクスチャの読み込み
		pTexture = new Texture();
		pTexture->Create(inPath);

        // 読み込んだらデータをセットする
		tObject.m_Data = pTexture;
		break;
	case RendererKind::Model:
        // モデルの読み込み
		pModel = new Model();
		if (!pModel->Load(inPath, scale, flip)) MessageBox(NULL, inPath, "Error", MB_OK);

        // Mesh情報の取得
		std::vector<Model::Mesh> meshVec;
		for (unsigned int i = 0; i < pModel->GetMeshNum(); i++)
		{
			Model::Mesh Mesh = *pModel->GetMesh(i);
			meshVec.push_back(Mesh);
		}

        // モデル用パラメータに一旦移す
		ModelParam tModel;
		tModel.m_pModel = pModel;
		tModel.m_tMeshVec = meshVec;

        // 移したらそのデータをセットする
		tObject.m_Data = tModel;
		break;
	}

    // セットされたデータをキーと共に登録する
	m_RendererObjectMap.emplace(inKey, tObject);
}

void CRendererComponent::UnLoad()
{
    // マップから全てのオブジェクト情報を取得
	for (auto& itr : m_RendererObjectMap)
	{
		switch (itr.second.m_eKind)
		{
		case RendererKind::Texture:
            // テクスチャならばテクスチャのdeleteをする
			SAFE_DELETE(std::get<Texture*>(itr.second.m_Data));
			break;
		case RendererKind::Model:
            // モデルならばモデルのdeleteをする
			SAFE_DELETE(std::get<ModelParam>(itr.second.m_Data).m_pModel);
			break;
		}
	}
}
