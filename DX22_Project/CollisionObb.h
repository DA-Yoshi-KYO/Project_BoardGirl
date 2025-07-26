// CollisionObbコンポーネント定義 [obbColider.h]
#pragma once

#include "CollisionBase.h"
#include <list>

struct ObbInfo
{
    DirectX::XMFLOAT3 m_Center;
    DirectX::XMFLOAT3 m_HalfSize;
};

class CCollisionObb : public CCollisionBase
{
public:
	using CCollisionBase::CCollisionBase;

	void Draw() override;
	bool IsHit(CCollisionBase* other) override;

private:
    ObbInfo m_tCollisionInfo;

public:
    DirectX::XMFLOAT3 AccessorCenter() const { return m_tCollisionInfo.m_Center; }
    void AccessorCenter(const DirectX::XMFLOAT3& center) { m_tCollisionInfo.m_Center = center; }
    DirectX::XMFLOAT3 AccessorHalfSize() const { return m_tCollisionInfo.m_HalfSize; }
    void AccessorHalfSize(const DirectX::XMFLOAT3& halfSize) { m_tCollisionInfo.m_HalfSize = halfSize; }
    ObbInfo AcessorCollisionInfo() const { return m_tCollisionInfo; }
    void AccessorCollisionInfo(const ObbInfo& info)
    {
        m_tCollisionInfo.m_Center = info.m_Center;
        m_tCollisionInfo.m_HalfSize = info.m_HalfSize;
    }

};
