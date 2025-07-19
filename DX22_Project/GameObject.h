#pragma once

#include "Defines.h"
#include "Component.h"

enum class Layer
{
	None,
	Back,
	Mid,
	Front,
	Canvas,

	Max
};

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
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	virtual void OnColliderHit();
	virtual void OnDestroy();
	virtual void SetCollisionType(Collision inCollisionType);
	virtual void SetTag(Tag inTag);

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
	DirectX::XMFLOAT3 PosAccessor();
	void PosAccessor(DirectX::XMFLOAT3 inPos) { m_tParam.m_f3Pos = inPos; }

	std::list<CComponent*> m_pComponent_List;

protected:
	RendererParam m_tParam;
	bool m_bDestroy;
	Collision m_eCollisionType;
	Tag m_eTag;
};

