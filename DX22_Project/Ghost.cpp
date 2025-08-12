#include "Ghost.h"
#include "Oparation.h"
#include "Player.h"
#include "EnemyAttack.h"
#include "Main.h"

CGhost::CGhost()
{
}

CGhost::~CGhost()
{
}

void CGhost::Init()
{
    CEnemyBase::Init();

    AddComponent<CBillboardRenderer>()->SetKey("Ghost");

    m_pCollision[(int)EnemyCollision::Body]->AccessorHalfSize(m_tParam.m_f3Size / 2.0f);
    m_pCollision[(int)EnemyCollision::Search]->AccessorHalfSize({ 7.0f, 7.0f, 7.0f });
    m_pCollision[(int)EnemyCollision::Attack]->AccessorHalfSize({ 5.0f, 5.0f, 5.0f });
}

void CGhost::Attack()
{
    DirectX::XMFLOAT3 f3PlayerPos = m_pPlayer->AccessorPos();
    DirectX::XMVECTOR vecPlayerPos = DirectX::XMLoadFloat3(&f3PlayerPos);
    DirectX::XMVECTOR vecEnemyPos = DirectX::XMLoadFloat3(&m_tParam.m_f3Pos);
    DirectX::XMVECTOR vecDirection = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(vecPlayerPos, vecEnemyPos));
    DirectX::XMVECTOR vecVelocity = vecDirection * m_tEnemyStatus.m_fSpeed;
    DirectX::XMFLOAT3 f3ShotDir = m_pPlayer->AccessorPos();
    DirectX::XMStoreFloat3(&f3ShotDir, vecDirection);

    AttackState tState;
    tState.m_f3Center = m_tParam.m_f3Pos;
    tState.m_f3Size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
    tState.m_f3Direction = f3ShotDir;
    tState.m_fAttackDuration = 1.0f;
    tState.m_nDamage = m_tEnemyStatus.m_nAttack;

    CEnemyBase::Attack(tState);
}
