#pragma once

#include "Defines.h"
#include "Component.h"

enum class Collision
{
	None,
	Box,
	Sphere,

	Max
};

enum class Tag
{
	None,
	UI,
	Player,
	Enemy,

	Max
};

class CGameObject
{
public:
    CGameObject();
    virtual ~CGameObject();
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	virtual void OnColliderHit();
	virtual void OnDestroy();

	void Destroy();
	bool IsDestroy();

public:
	template<typename T = CComponent>
	T* AddComponent()
	{
		T* pComponent = new T(this);
		m_pComponent_List.push_back(pComponent);
		((CComponent*)pComponent)->Init();
		return pComponent;
	}

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
	void AccessorPos(DirectX::XMFLOAT3 inPos) { m_tParam.m_f3Pos = inPos; }
    DirectX::XMFLOAT3 AccessorPos() { return m_tParam.m_f3Pos; }
    void AccessorTag(Tag inTag) { m_eTag = inTag; }
    Tag AccessorTag() { return m_eTag; }
    void AccessorCollisionType(Collision inCollisionType) { m_eCollisionType = inCollisionType; }
    Collision AccessorCollisionType() { return m_eCollisionType; }

	std::list<CComponent*> m_pComponent_List;

protected:
	RendererParam m_tParam;
	bool m_bDestroy;
	Collision m_eCollisionType;
	Tag m_eTag;

};

