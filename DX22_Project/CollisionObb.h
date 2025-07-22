// CollisionObbコンポーネント定義 [obbColider.h]
#pragma once

#include "CollisionBase.h"
#include <list>

class CCollisionObb : public CCollisionBase
{
public:

	using CCollisionBase::CCollisionBase;

	void Update() override;
	void Draw() override;

    DirectX::XMFLOAT3 AccessorCenter() const { return m_Center; }
    void AccessorCenter(const DirectX::XMFLOAT3& center) { m_Center = center; }
    DirectX::XMFLOAT3 AccessorHalfSize() const { return m_HalfSize; }
    void AccessorHalfSize(const DirectX::XMFLOAT3& halfSize) { m_HalfSize = halfSize; }
private:
	DirectX::XMFLOAT3		m_Center;
	DirectX::XMFLOAT3		m_HalfSize;
	bool IsHit(CCollisionBase* other) override;

};
