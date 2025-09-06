#pragma once
#include "Defines.h"

class CGameObject;

class CComponent
{
public:
	CComponent() = delete;
	CComponent(CGameObject* inGameObject)
		: m_pGameObject(nullptr)
	{
		m_pGameObject = inGameObject;
	}
	virtual ~CComponent();
	virtual void Init();
	virtual void Uninit();	
	virtual void Update();
	virtual void Draw();
    CGameObject* GetGameObject() { return m_pGameObject; }
	
protected:
	CGameObject* m_pGameObject;

};

