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
	T* AddGameObject(std::string inName, Tag inTag = Tag::None)
	{
		T* gameObject;
		gameObject = new T();
		m_pGameObject_List[(int)inTag].push_back(gameObject);
		gameObject->Init();
        gameObject->AccessorTag(inTag);

        std::string name = inName;
        int nSameCount = 0;
        for (auto itr : m_sNameList)
        {
            if (itr == name)
            {
                nSameCount++;
                name = inName + std::to_string(nSameCount);
            }
        }
        m_sNameList.push_back(name);

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

    void AddCollision(CCollisionBase* inCollision)
    {
        if (inCollision)
        {
            m_pCollisionVec.push_back(inCollision);
        }
    }

    void DequeCollision(CGameObject* inThis);
    std::array<std::list<CGameObject*>, (int)Tag::Max> GetGameObjectList();
    std::vector<std::string> GetNameList() { return m_sNameList; };

protected:
    std::array<std::list<CGameObject*>,(int)Tag::Max> m_pGameObject_List; // シーン内のゲームオブジェクトリスト
    std::vector<CCollisionBase*> m_pCollisionVec; // 衝突判定用のコンポーネントリスト
    std::vector<std::string> m_sNameList;        // IMGUI識別用名称
};
