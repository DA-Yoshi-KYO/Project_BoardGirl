#include "Ghost.h"
#include "Oparation.h"
#include "Player.h"
#include "EnemyAttack.h"
#include "Main.h"
#include "BillboardRenderer.h"

constexpr float ce_fShotSpeed = 0.2f;

CGhost::CGhost()
{
    m_tEnemyStatus.m_nHP = 10;
    m_tEnemyStatus.m_nAttack = 5;
}

CGhost::~CGhost()
{
}

void CGhost::Init()
{
    CEnemyBase::Init();

    AddComponent<CBillboardRenderer>()->SetKey("Ghost");

    m_pCollision[(int)eEnemyCollision::Body]->AccessorHalfSize(m_tParam.m_f3Size / 2.0f);
    m_pCollision[(int)eEnemyCollision::Search]->AccessorHalfSize(DirectX::XMFLOAT3( 10.0f, 10.0f, 10.0f));
    m_pCollision[(int)eEnemyCollision::Attack]->AccessorHalfSize(DirectX::XMFLOAT3( 10.0f, 10.0f, 10.0f));
}

void CGhost::Attack()
{
    DirectX::XMFLOAT3 f3PlayerPos = m_pPlayer->AccessorPos();
    DirectX::XMVECTOR vecPlayerPos = DirectX::XMLoadFloat3(&f3PlayerPos);
    DirectX::XMVECTOR vecEnemyPos = DirectX::XMLoadFloat3(&m_tParam.m_f3Pos);
    DirectX::XMVECTOR vecDirection = DirectX::XMVector3Normalize(vecPlayerPos - vecEnemyPos);
    vecDirection *= ce_fShotSpeed;
    DirectX::XMFLOAT3 f3ShotDir;
    DirectX::XMStoreFloat3(&f3ShotDir, vecDirection);

    AttackState tState;
    tState.m_f3Center = m_tParam.m_f3Pos;
    tState.m_f3Size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
    tState.m_fAttackDuration = 1.0f;
    tState.m_nDamage = m_tEnemyStatus.m_nAttack;
    tState.m_sTexKey = "GhostAttack";
    tState.m_n2Split = DirectX::XMINT2(10, 1);
    tState.m_tDirectionState.m_eKind = DirectionKind::Toward;
    tState.m_tDirectionState.m_tToward.m_f3Direction = f3ShotDir;

    CEnemyBase::Attack(tState);
}
