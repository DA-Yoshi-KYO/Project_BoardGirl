#pragma once

#include "Defines.h"
#include "CollisionBase.h"
#include "BillboardRenderer.h"
#include "SpriteRenderer.h"
#include "Sprite3DRenderer.h"
#include "ModelRenderer.h"
#include "GameObject.h"

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
	T* AddGameObject(std::string inName, Tag inTag = Tag::None)
	{
		T* gameObject;
		gameObject = new T();
		m_pGameObject_List[(int)inTag].push_back(gameObject);
		gameObject->Init();
        gameObject->AccessorTag(inTag);

        ObjectID id{};
        for (auto itr : m_tIDVec)
        {
            if (itr.m_sName == inName)
            {
                id.m_nSameCount++;
            }
        }
        id.m_sName = inName;
        m_tIDVec.push_back(id);
        gameObject->AccessorID(id);

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
            for (auto obj : list)
            {
                T* ret = dynamic_cast<T*>(obj);
                if (ret != nullptr) return ret;
            }
        }
		return nullptr;
	}

	CGameObject* GetGameObject(ObjectID inID)
	{
        for (auto list : m_pGameObject_List)
        {
            for (auto obj : list)
            {
                ObjectID id = obj->AccessorID();
                if (id.m_sName == inID.m_sName &&
                    id.m_nSameCount == inID.m_nSameCount)
                {
                    return obj;
                }
            }
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

    void DequeCollision(CGameObject* inThis);
    std::array<std::list<CGameObject*>, (int)Tag::Max> GetGameObjectList();

protected:
    std::array<std::list<CGameObject*>,(int)Tag::Max> m_pGameObject_List; // シーン内のゲームオブジェクトリスト
    std::vector<CCollisionBase*> m_pCollisionVec; // 衝突判定用のコンポーネントリスト
private:
    std::vector<ObjectID> m_tIDVec;
};
