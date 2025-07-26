#pragma once

// インクルード部
#include "Defines.h"
#include "Component.h"
#include "CollisionBase.h"

// オブジェクトタグ
enum class Tag
{
	None,
	Player,
	Enemy,

    Field,
	UI,
	Max
};

class CGameObject
{
public:
    // 初期化処理時に値を参照したい時は、その値をコンストラクタで初期化する
    // ※ここでのコンストラクタが各種Initより先に呼ばれる為
    CGameObject();
    virtual ~CGameObject();
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

    // 衝突時の処理
	virtual void OnColliderHit(CCollisionBase* other);
    // オブジェクトの破棄時の処理
	virtual void OnDestroy();
    // オブジェクトの破棄
	void Destroy();
    // オブジェクトが破棄されているかの確認
	bool IsDestroy();

public:
    // コンポーネントの追加
	template<typename T = CComponent>
	T* AddComponent()
	{
		T* pComponent = new T(this);
		m_pComponent_List.push_back(pComponent);
		((CComponent*)pComponent)->Init();
		return pComponent;
	}

    // コンポーネントの取得
	template<typename T = CComponent>
	T* GetComponent()
	{
		for (CComponent* pComponent : m_pComponent_List)
		{
			T* pRet = dynamic_cast<T*>(pComponent);
			if (pRet != nullptr) return pRet;
		}
		return nullptr;
	}

public:
    // アクセサ

    void AccessorPos(DirectX::XMFLOAT3 inPos) { m_tParam.m_f3Pos = inPos; }
    DirectX::XMFLOAT3 AccessorPos() { return m_tParam.m_f3Pos; }
    void AccessorRotate(DirectX::XMFLOAT3 inRotate) { m_tParam.m_f3Rotate = inRotate; }
    DirectX::XMFLOAT3 AccessorRotate() { return m_tParam.m_f3Rotate; }
    void AccessorSize(DirectX::XMFLOAT3 inSize) { m_tParam.m_f3Size = inSize; }
    DirectX::XMFLOAT3 AccessorSize() { return m_tParam.m_f3Size; }
    void AccessorTag(Tag inTag) { m_eTag = inTag; }
    Tag AccessorTag() { return m_eTag; }

    DirectX::XMFLOAT4X4* GetWorld()
    {
        DirectX::XMFLOAT4X4 world;

        DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranslation(m_tParam.m_f3Pos.x, m_tParam.m_f3Pos.y, m_tParam.m_f3Pos.z) *
            DirectX::XMMatrixRotationRollPitchYaw(m_tParam.m_f3Rotate.x, m_tParam.m_f3Rotate.y, m_tParam.m_f3Rotate.z) *
            DirectX::XMMatrixScaling(m_tParam.m_f3Size.x, m_tParam.m_f3Size.y, m_tParam.m_f3Size.z));
        return &world;
    }
    
public:
    // コンポーネントのリスト
    std::list<CComponent*> m_pComponent_List;

protected:
    RendererParam m_tParam;     // 描画パラメータ
    bool m_bDestroy;            // オブジェクトが破棄されているかのフラグ
    Tag m_eTag;                 // オブジェクトのタグ

};

