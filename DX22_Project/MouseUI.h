#pragma once

#include "GameObject.h"
#include "SpriteRenderer.h"

enum class MouseKind
{
    None,
    Middle,
    Left,
    Right,

    Max
};

class CMouseUI : public CGameObject
{
public:
    void Init() override;
    void SetKind(MouseKind inKind);

private:

};
