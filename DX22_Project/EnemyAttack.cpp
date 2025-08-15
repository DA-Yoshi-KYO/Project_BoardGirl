#include "EnemyAttack.h"
#include "Oparation.h"
#include "Player.h"
#include "CollisionObb.h"
#include "BillboardRenderer.h"
#include "Main.h"

CEnemyAttack::CEnemyAttack()
    : CGameObject()
    , m_tAttackState{},m_fTime(0.0f), m_nStep(0)
{

}

CEnemyAttack::~CEnemyAttack()
{
}

void CEnemyAttack::Init()
{
    CCollisionObb* pCollision = AddComponent<CCollisionObb>();
    pCollision->AccessorCenter(m_tAttackState.m_f3Center);
    pCollision->AccessorHalfSize(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
    pCollision->AccessorTag("EnemyDamage");
    pCollision->AccessorActive(true);

    AddComponent<CBillboardRenderer>();
}

void CEnemyAttack::Update()
{
    m_tAttackState.m_f3Center += m_tAttackState.m_f3Direction;
    m_tParam.m_f3Pos = m_tAttackState.m_f3Center;
    m_tParam.m_f3Size = m_tAttackState.m_f3Size * 2.0f;

    if (m_tAttackState.m_n2Split.x != 0 && m_tAttackState.m_n2Split.y != 0)
    {
        m_tParam.m_f2UVSize.x = 1.0f / (float)m_tAttackState.m_n2Split.x;
        m_tParam.m_f2UVSize.y = 1.0f / (float)m_tAttackState.m_n2Split.y;
        float fStep = m_tAttackState.m_fAttackDuration / float(m_tAttackState.m_n2Split.x * m_tAttackState.m_n2Split.y);
        if (m_fTime >= fStep * (m_nStep + 1)) m_nStep++;
        m_tParam.m_f2UVPos.x = (1.0f / (float)m_tAttackState.m_n2Split.x) * (m_nStep % m_tAttackState.m_n2Split.x);
        m_tParam.m_f2UVPos.y = (1.0f / (float)m_tAttackState.m_n2Split.y) * (m_nStep / m_tAttackState.m_n2Split.x);
    }

    CCollisionObb* pCollision = GetComponent<CCollisionObb>();
    if (pCollision)
    {
        pCollision->AccessorCenter(m_tAttackState.m_f3Center);
        pCollision->AccessorHalfSize(m_tAttackState.m_f3Size * 0.5f);
    }

    if (m_fTime >= m_tAttackState.m_fAttackDuration)
        Destroy();

    m_fTime += fDeltaTime;
    CGameObject::Update();
}

void CEnemyAttack::Draw()
{
    if (m_tAttackState.m_sTexKey != "")GetComponent<CBillboardRenderer>()->SetKey(m_tAttackState.m_sTexKey);
    CGameObject::Draw();
}

void CEnemyAttack::OnColliderHit(CCollisionBase* other, std::string thisTag)
{
    CGameObject* pOtherObject = other->GetGameObject();
    if (other->AccessorTag() == "PlayerBody")
    {
        dynamic_cast<CPlayer*>(pOtherObject)->Damage(m_tAttackState.m_nDamage);
        GetComponent<CCollisionObb>()->AccessorActive(false);
    }
}
