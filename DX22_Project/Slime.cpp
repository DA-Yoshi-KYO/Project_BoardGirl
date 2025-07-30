#include "Slime.h"
#include "BillboardRenderer.h"

CSlime::CSlime()
    : CEnemyBase()
{
    m_tEnemyStatus.m_nHP = 10;
    m_tEnemyStatus.m_nAttack = 2;
    m_tEnemyStatus.m_nDefense = 1;
}

CSlime::~CSlime()
{
}

void CSlime::Init()
{
    AddComponent<CBillboardRenderer>()->SetKey("Slime");
}
