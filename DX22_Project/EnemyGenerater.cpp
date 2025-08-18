#include <variant>
#include "EnemyGenerater.h"
#include "Main.h"
#include "EnemyBase.h"
#include "Slime.h"
#include "Ghost.h"
#include "Dragon.h"

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
    return m_pInstance;
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
    CScene* pScene = GetScene();
    CEnemyBase* pEnemy = nullptr;
    
    if (inEnemyID == "Slime") pEnemy = pScene->AddGameObject<CSlime>("Slime");
    else if (inEnemyID == "Ghost") pEnemy = pScene->AddGameObject<CGhost>("Ghost");
    else if (inEnemyID == "Dragon") pEnemy = pScene->AddGameObject<CDragon>("Dragon");
    else MessageBox(NULL, "NotFindEnemy", "Error", MB_OK);

    pEnemy->AccessorPos(position);
}
