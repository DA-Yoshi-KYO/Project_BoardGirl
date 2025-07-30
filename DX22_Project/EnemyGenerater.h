#pragma once

#include "Defines.h"

class CEnemyGenerater
{
private:
    CEnemyGenerater();

public:
    CEnemyGenerater(const CEnemyGenerater&) = delete;
    CEnemyGenerater& operator=(const CEnemyGenerater&) = delete;
    static CEnemyGenerater* GetInstance();
    void ReleaseInstance();
    void GenerateEnemy(std::string enemyID, const DirectX::XMFLOAT3& position);

private:
    static CEnemyGenerater* m_pInstance;

};
