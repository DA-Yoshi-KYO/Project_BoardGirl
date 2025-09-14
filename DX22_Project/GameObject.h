#pragma once

// インクルード部
#include "Defines.h"
#include "Component.h"
#include "CollisionBase.h"
#include "Audio.h"
#include "imgui.h"

// オブジェクトタグ
enum class Tag
{
	None,
    SkyBox,
    Sound,
    Field,
	GameObject,
	
	UI,
	Max
};

struct ObjectID
{
    std::string m_sName;    // オブジェクトの名前
    int m_nSameCount;       // 同オブジェクトの数
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
	virtual void OnColliderHit(CCollisionBase* other, std::string thisTag = "None");
    // オブジェクトの破棄時の処理
	virtual void OnDestroy();
    // オブジェクトの破棄
	virtual void Destroy();
    // オブジェクトが破棄されているかの確認
	bool IsDestroy();

    virtual int Inspecter(bool isEnd = true);
    
    DirectX::XMFLOAT3 GetForward();
    DirectX::XMFLOAT3 GetRight();
    DirectX::XMFLOAT3 GetUp();

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

    template<typename T = CComponent>
    std::list<T*> GetSameComponents()
    {
        std::list<T*> componentList;
        componentList.clear();

        for (CComponent* pComponent : m_pComponent_List)
        {
            T* pRet = dynamic_cast<T*>(pComponent);
            if (pRet != nullptr) componentList.push_back(pRet);
        }
        return componentList;
    }

    template<typename T = CComponent>
    void DestroyComponent()
    {
        for (auto itr = m_pComponent_List.begin(); itr != m_pComponent_List.end();)
        {
            if (dynamic_cast<T*>(*itr))
            {
                delete (*itr);
                (*itr) = nullptr;
                itr = m_pComponent_List.erase(itr);
            }
            else itr++;
        }
    }

public:
    // アクセサ

    void AccessorPos(DirectX::XMFLOAT3 inPos) { m_tParam.m_f3Pos = inPos; }
    DirectX::XMFLOAT3 AccessorPos() { return m_tParam.m_f3Pos; }
    void AccessorRotate(DirectX::XMFLOAT3 inRotate) { m_tParam.m_f3Rotate = inRotate; }
    DirectX::XMFLOAT3 AccessorRotate() { return m_tParam.m_f3Rotate; }
    void AccessorSize(DirectX::XMFLOAT3 inSize) { m_tParam.m_f3Size = inSize; }
    DirectX::XMFLOAT3 AccessorSize() { return m_tParam.m_f3Size; }
    void AccessorColor(DirectX::XMFLOAT4 inColor) { m_tParam.m_f4Color = inColor; }
    DirectX::XMFLOAT4 AccessorColor() { return m_tParam.m_f4Color; }
    void AccessorTag(Tag inTag) { m_eTag = inTag; }
    Tag AccessorTag() { return m_eTag; }
    void AccessorID(ObjectID inTag) { m_tID = inTag; }
    ObjectID AccessorID() { return m_tID; }

    DirectX::XMFLOAT4X4* GetWorld()
    {
        DirectX::XMFLOAT4X4 world;

        DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixScaling(m_tParam.m_f3Size.x, m_tParam.m_f3Size.y, m_tParam.m_f3Size.z) *
            DirectX::XMMatrixRotationRollPitchYaw(m_tParam.m_f3Rotate.x, m_tParam.m_f3Rotate.y, m_tParam.m_f3Rotate.z) *
            DirectX::XMMatrixTranslation(m_tParam.m_f3Pos.x, m_tParam.m_f3Pos.y, m_tParam.m_f3Pos.z));
        return &world;
    }

public:
    // コンポーネントのリスト
    std::list<CComponent*> m_pComponent_List;

protected:
    RendererParam m_tParam;     // 描画パラメータ
    DirectX::XMFLOAT3 m_f3OldPos; // 前フレームの位置
    bool m_bDestroy;            // オブジェクトが破棄されているかのフラグ
    Tag m_eTag;                 // オブジェクトのタグ
    ObjectID m_tID;
    std::vector<CAudio*> m_pSE;
    
};

