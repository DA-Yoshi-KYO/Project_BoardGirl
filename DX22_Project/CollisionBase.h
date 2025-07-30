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
    void AccessorTag(const std::string& inTag) { m_sTag = inTag; }
    const std::string& AccessorTag() const { return m_sTag; }
    void AccessorActive(const bool inActive) { m_bActive = inActive; }
    const bool AccessorActive() const { return m_bActive; }

private:
    CollisionKind m_eCollisionKind;

protected:
    bool m_bActive = true;
    std::string m_sTag = "None";

};
