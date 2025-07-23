#pragma once

// インクルード部
#include "GameObject.h"

class CPlayer: public CGameObject
{
public: 
	void Init() override;
	void Update() override;

    // プレイヤーの前方向を取得
	DirectX::XMFLOAT3 GetForward();

private:
    bool m_bJump;   // ジャンプ中かどうか
	DirectX::XMFLOAT3 m_f3Velocity; // 移動量

private:
    DirectX::XMFLOAT3 GetRight();
    void PlayerMove();  // プレイヤーの移動処理

private:

};
