#pragma once

// インクルード部
#include "GameObject.h"
#include "Job.h"
#include "CollisionObb.h"

class CPlayer: public CGameObject
{
public: 
	void Init() override;
	void Update() override;
    void OnColliderHit(CCollisionBase* other, std::string thisTag = "None") override;

    void Damage(int inDamage);
    // プレイヤーの前方向を取得
	DirectX::XMFLOAT3 GetForward();

private:
    bool m_bJump;   // ジャンプ中かどうか
	DirectX::XMFLOAT3 m_f3Velocity; // 移動量

private:
    DirectX::XMFLOAT3 GetRight();
    void PlayerMove();
    void PlayerSkill();
    bool m_bDamage;
private:
    std::unique_ptr<CJob> m_pJob;
    CCollisionObb* m_pCollision;
    CHPBar* m_pHPBar;
    JobKind m_eJobKind;

};
