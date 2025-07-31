#pragma once

#include "Defines.h"
#include "GameObject.h"
#include "CollisionBase.h"
#include "BillboardRenderer.h"
#include "SpriteRenderer.h"
#include "Sprite3DRenderer.h"
#include "ModelRenderer.h"

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
		m_pGameObject_List.push_back(gameObject);
		gameObject->Init();
        gameObject->AccessorTag(inTag);


        std::list<CCollisionBase*> pCollisionList = gameObject->GetSameComponents<CCollisionBase>();
        for (auto itr : pCollisionList)
        {
            m_pCollisionVec.push_back(itr);
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
