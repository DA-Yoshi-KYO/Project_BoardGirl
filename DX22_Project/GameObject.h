#pragma once

#include "Defines.h"
#include "Component.h"

class CGameObject
{
public:
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	virtual void OnColliderHit();
	virtual void OnDestroy();

	void Destroy();
	bool IsDestroy();

	std::list<CComponent*> m_pComponent_List;

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

	DirectX::XMFLOAT3 GetPos() { return m_tParam.m_f3Pos; }

protected:
	RendererParam m_tParam;
	bool m_bDestroy;

};

