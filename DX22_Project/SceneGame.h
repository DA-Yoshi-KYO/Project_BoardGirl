#pragma once

// インクルード部
#include "Scene.h"

class CSceneGame : public CScene
{
public:
	void Init() override;
    void Update() override;
    void Draw() override;

private:
    void GenerateSystem();
    float m_fTime;
    int m_nLastSpawnTime;

};
