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
	T* AddGameObject(Collision inCollisionType = Collision::None, Tag inTag = Tag::None)
	{
		T* gameObject;
		gameObject = new T();
		gameObject->Init();
        gameObject->AccessorCollisionType(inCollisionType);
        gameObject->AccessorTag(inTag);
		m_pGameObject_List.push_back(gameObject);

		return gameObject;
	}

	template<typename T = CGameObject>
	T* GetGameObject()
	{
        for (auto list : m_pGameObject_List)
        {
            T* ret = dynamic_cast<T*>(list);
            if (ret != nullptr) return ret;
        }
		return nullptr;
	}

protected:
    std::list<CGameObject*> m_pGameObject_List;

};
