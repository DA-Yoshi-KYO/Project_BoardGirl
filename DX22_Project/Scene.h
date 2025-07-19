#pragma once

#include "Defines.h"
#include "GameObject.h"

class CScene
{
public:
	virtual ~CScene();
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	template<typename T = CGameObject>
	T* AddGameObject(Layer inLayer = Layer::None, Collision inCollisionType = Collision::None, Tag inTag = Tag::None)
	{
		T* gameObject;
		gameObject = new T();
		gameObject->Init();
		m_pGameObject_List[(int)inLayer].push_back(gameObject);

		return gameObject;
	}

	template<typename T = CGameObject>
	T* GetGameObject()
	{
		for (auto list : m_pGameObject_List)
		{
			for (CGameObject* obj : list)
			{
				T* ret = dynamic_cast<T*>(obj);
				if (ret != nullptr) return ret;
			}
		}
		return nullptr;
	}

protected:
	std::array<std::list<CGameObject*>, (int)Layer::Max> m_pGameObject_List;

};

