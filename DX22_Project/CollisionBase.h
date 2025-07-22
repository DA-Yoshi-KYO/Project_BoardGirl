#pragma once

#include "Component.h" 

enum class CollisionKind
{
    Box,
    Sphere,

    Max
};

class CCollisionBase : public CComponent
{
public:
    using CComponent::CComponent;
    virtual ~CCollisionBase();
    virtual bool IsHit(CCollisionBase* other);
    CollisionKind GetCollisionKind() const { return m_eCollisionKind; }

private:
    CollisionKind m_eCollisionKind;

};
