#include "GameObject.h"
#include "RendererComponent.h"

CGameObject::CGameObject()
    : m_bDestroy(false)
    , m_eTag(Tag::None)
{
    m_tParam.m_f3Pos = { 0.0f, 0.0f, 0.0f };
    m_tParam.m_f3Size = { 1.0f, 1.0f, 1.0f };
    m_tParam.m_f3Rotate = { 0.0f, 0.0f, 0.0f };
    m_tParam.m_f4Color = { 1.0f, 1.0f, 1.0f, 1.0f };
    m_tParam.m_f2UVPos = { 0.0f, 0.0f };
    m_tParam.m_f2UVSize = { 1.0f, 1.0f };
}

CGameObject::~CGameObject()
{
}

void CGameObject::Init()
{

}

void CGameObject::Uninit()
{
    // コンポーネントの解放
	for (auto comp : m_pComponent_List)
	{
		comp->Uninit();
		delete comp;
	}
	m_pComponent_List.clear();
}

void CGameObject::Update()
{
    // コンポーネントの更新
	for (auto comp : m_pComponent_List)
	{
		comp->Update();
	}
}

void CGameObject::Draw()
{
    // コンポーネントの描画
    for (auto comp : m_pComponent_List)
	{
        // 描画用コンポーネントを使用する場合、汎用パラメータをコンポーネントに渡す
		if (dynamic_cast<CRendererComponent*>(comp))dynamic_cast<CRendererComponent*>(comp)->SetRendererParam(m_tParam);
        // 当たり判定描画はSceneで行う
        if (dynamic_cast<CCollisionBase*>(comp)) continue;
		comp->Draw();
	}	
}

void CGameObject::OnColliderHit(CCollisionBase* other)
{

}

void CGameObject::OnDestroy()
{

}

void CGameObject::Destroy()
{
	m_bDestroy = true;
}

bool CGameObject::IsDestroy()
{
	return m_bDestroy;
}
