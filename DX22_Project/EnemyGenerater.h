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
    void GenerateEnemy(const char* enemyID, const DirectX::XMFLOAT3& position);

    void MasterInit();

private:
    static CEnemyGenerater* m_pInstance;

};
