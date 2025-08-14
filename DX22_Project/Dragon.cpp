#include "Dragon.h"
#include "Oparation.h"
#include "Player.h"

CDragon::CDragon()
{
    m_tEnemyStatus.m_nHP = 30;
    m_tEnemyStatus.m_nAttack = 20;
    m_tEnemyStatus.m_nDefense = 1;

    m_tParam.m_f3Size = DirectX::XMFLOAT3(3.0f,3.0f,3.0f);
}

CDragon::~CDragon()
{

}

void CDragon::Init()
{
    CEnemyBase::Init();
    AddComponent<CBillboardRenderer>()->SetKey("Dragon");

    m_pCollision[(int)eEnemyCollision::Body]->AccessorHalfSize(m_tParam.m_f3Size / 2.0f);
    m_pCollision[(int)eEnemyCollision::Search]->AccessorHalfSize(DirectX::XMFLOAT3(5.0f, 5.0f, 5.0f));
    m_pCollision[(int)eEnemyCollision::Attack]->AccessorHalfSize(DirectX::XMFLOAT3(3.0f, 3.0f, 3.0f));
}

void CDragon::Attack()
{
    int nPercent = rand() % 100;

    switch (CEnemyBase::GetPattern(m_pCollision[(int)eEnemyCollision::Attack]->AccessorHalfSize()))
    {
    case eEnemyStatePattern::Near:
        if (nPercent <= 20) AttackBreath();
        else AttackNormal();
        break;
    case eEnemyStatePattern::Middle:
        if (nPercent <= 50) AttackBreath();
        else AttackNormal();
        break;
    case eEnemyStatePattern::Far:
        if (nPercent <= 80) AttackBreath();
        else AttackNormal();
        break;
    default:
        break;
    }
}

void CDragon::AttackNormal()
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
    tState.m_f3Size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
    tState.m_f3Direction = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    tState.m_fAttackDuration = 1.0f;
    tState.m_nDamage = m_tEnemyStatus.m_nAttack;

    CEnemyBase::Attack(tState);
}

void CDragon::AttackBreath()
{
}
