#pragma once

#include "Defines.h"
#include "GameObject.h"
#include "CollisionBase.h"

class CScene
{
public:
	virtual ~CScene();
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

    // ゲームオブジェクトを追加する
	template<typename T = CGameObject>
	T* AddGameObject(Tag inTag = Tag::None)
	{
		T* gameObject;
		gameObject = new T();
		gameObject->Init();
        gameObject->AccessorTag(inTag);

		m_pGameObject_List.push_back(gameObject);

        CCollisionBase* pCollision = gameObject->GetComponent<CCollisionBase>();
        if (pCollision)
        {
            m_pCollisionVec.push_back(pCollision);
        }

		return gameObject;
	}

    // ゲームオブジェクトを取得する
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

    void AddCollision(CCollisionBase* inCollision)
    {
        if (inCollision)
        {
            m_pCollisionVec.push_back(inCollision);
        }
    }

protected:
    std::list<CGameObject*> m_pGameObject_List; // シーン内のゲームオブジェクトリスト
    std::vector<CCollisionBase*> m_pCollisionVec; // 衝突判定用のコンポーネントリスト
};
