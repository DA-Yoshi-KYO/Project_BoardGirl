#include "Slime.h"
#include "BillboardRenderer.h"
#include "Oparation.h"
#include "Player.h"

CSlime::CSlime()
    : CEnemyBase()
{
    m_tEnemyStatus.m_nHP = 10;
    m_tEnemyStatus.m_nAttack = 10;
    m_tEnemyStatus.m_nDefense = 1;
}

CSlime::~CSlime()
{

}

void CSlime::Init()
{
    CEnemyBase::Init();
    AddComponent<CBillboardRenderer>()->SetKey("Slime");

    m_pCollision[(int)eEnemyCollision::Body]->AccessorHalfSize(m_tParam.m_f3Size / 2.0f);
    m_pCollision[(int)eEnemyCollision::Search]->AccessorHalfSize(DirectX::XMFLOAT3(5.0f, 5.0f, 5.0f));
    m_pCollision[(int)eEnemyCollision::Attack]->AccessorHalfSize(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
}

void CSlime::Attack()
{
    DirectX::XMFLOAT3 f3PlayerPos = m_pPlayer->AccessorPos();
    DirectX::XMVECTOR vecPlayerPos = DirectX::XMLoadFloat3(&f3PlayerPos);
    DirectX::XMVECTOR vecEnemyPos = DirectX::XMLoadFloat3(&m_tParam.m_f3Pos);
    DirectX::XMVECTOR vecDirection = DirectX::XMVector3Normalize(vecPlayerPos - vecEnemyPos);
    DirectX::XMFLOAT3 f3AttackPos;
    DirectX::XMStoreFloat3(&f3AttackPos, vecDirection);
    f3AttackPos += m_tParam.m_f3Pos;

    AttackState tState;
    tState.m_f3Center = f3AttackPos;
    tState.m_f3Size = DirectX::XMFLOAT3(1.0f,1.0f,1.0f);
    tState.m_f3Direction = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    tState.m_fAttackDuration = 1.0f;
    tState.m_nDamage = m_tEnemyStatus.m_nAttack;
    tState.m_sTexKey = "SlimeAttack";
    tState.m_n2Split = DirectX::XMINT2(5, 2);

    CEnemyBase::Attack(tState);
}
