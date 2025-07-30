#include "EnemyGenerater.h"

CEnemyGenerater* CEnemyGenerater::m_pInstance = nullptr;

CEnemyGenerater::CEnemyGenerater()
{

}

CEnemyGenerater* CEnemyGenerater::GetInstance()
{
    if (m_pInstance == nullptr)
    {
        m_pInstance = new CEnemyGenerater();
    }
    return nullptr;
}

void CEnemyGenerater::ReleaseInstance()
{
    if (m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }
}

void CEnemyGenerater::GenerateEnemy(std::string inEnemyID, const DirectX::XMFLOAT3& position)
{

}
