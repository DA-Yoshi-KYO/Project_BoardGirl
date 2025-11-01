#include "Alphabet.h"
#include "SpriteRenderer.h"

CAlphabet::~CAlphabet()
{
}

void CAlphabet::Init()
{
    AddComponent<CSpriteRenderer>()->SetKey("Alphabet");
    m_tParam.m_f2UVSize.x = 0.125f;
    m_tParam.m_f2UVSize.y = 0.25f;
}
