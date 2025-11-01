#include "MouseUI.h"

void CMouseUI::Init()
{
    AddComponent<CSpriteRenderer>()->SetKey("MouseUI");
    m_tParam.m_f2UVSize.x = 1.0f / (float)MouseKind::Max;
}

void CMouseUI::SetKind(MouseKind inKind)
{
    m_tParam.m_f2UVPos.x = (float)inKind / (float)MouseKind::Max;
}
