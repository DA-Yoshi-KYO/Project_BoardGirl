#pragma once

// インクルード部
#include "Defines.h"
#include "Component.h"

// 使用する当たり判定
enum class Collision
{
	None,
	Box,
	Sphere,

	Max
};

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
	virtual void OnColliderHit();
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
    void AccessorTag(Tag inTag) { m_eTag = inTag; }
    Tag AccessorTag() { return m_eTag; }
    void AccessorCollisionType(Collision inCollisionType) { m_eCollisionType = inCollisionType; }
    Collision AccessorCollisionType() { return m_eCollisionType; }

public:
    // コンポーネントのリスト
    std::list<CComponent*> m_pComponent_List;

protected:
    RendererParam m_tParam;     // 描画パラメータ
    bool m_bDestroy;            // オブジェクトが破棄されているかのフラグ
    Collision m_eCollisionType; // 使用する当たり判定
    Tag m_eTag;                 // オブジェクトのタグ

};

