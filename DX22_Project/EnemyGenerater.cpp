// インクルード部
#include "EnemyGenerater.h"
#include "Main.h"
#include "Slime.h"
#include "Ghost.h"
#include "Dragon.h"

// 静的変数初期化
CEnemyGenerater* CEnemyGenerater::m_pInstance = nullptr;

CEnemyGenerater::CEnemyGenerater()
{

}

CEnemyGenerater* CEnemyGenerater::GetInstance()
{
    // インスタンスを1つだけ生成
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

void CEnemyGenerater::GenerateEnemy(EnemyID inEnemyID, const DirectX::XMFLOAT3& position)
{
    CScene* pScene = GetScene();
    CEnemyBase* pEnemy = nullptr;

    // IDによって生成する敵を決める
    switch (inEnemyID)
    {
    case EnemyID::Slime:
        pEnemy = pScene->AddGameObject<CSlime>("Slime", Tag::GameObject);
        break;
    case EnemyID::Ghost:
        pEnemy = pScene->AddGameObject<CGhost>("Ghost", Tag::GameObject);
        break;
    case EnemyID::Dragon:
        pScene->AddGameObject<CDragon>("Dragon", Tag::GameObject);
        break;
    default:
        MessageBox(NULL, "NotFindEnemy", "Error", MB_OK);
        break;
    }

    // 位置を決定
    pEnemy->AccessorPos(position);
}
