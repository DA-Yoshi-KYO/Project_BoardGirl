#include "Score.h"
#include "SpriteRenderer.h"

constexpr DirectX::XMINT2 ce_nSplit = { 5,5 };

int CScore::m_nScore = 0;

CScore::~CScore()
{

}

void CScore::Init()
{
    CSpriteRenderer* pRenderer = AddComponent<CSpriteRenderer>();
    pRenderer->SetKey("Number");

    for (int i = 0; i < 4; i++)
    {
        m_tRenderParam[i].m_f3Size = { 100.0f,100.0f,100.0f };
        m_tRenderParam[i].m_f3Pos = { -360.0f + i * 60.0f,-300.0f,0.0f };
        m_tRenderParam[i].m_f3Rotate = { 0.0f,0.0f,0.0f };
        m_tRenderParam[i].m_f2UVPos = { 0.0f,0.0f };
        m_tRenderParam[i].m_f2UVSize = { 1.0f / (float)ce_nSplit.x,1.0f / (float)ce_nSplit.y };
        m_tRenderParam[i].m_f4Color = { 0.0f,0.0f,0.0f,1.0f };
    }
}

void CScore::Update()
{
    int nOne = m_nScore % 10;
    int nTen = (m_nScore % 100) / 10;
    int nHundred = (m_nScore % 1000) / 100;
    int nThowthant = (m_nScore % 10000) / 1000;

    int CalcValue[] =
    {
        nOne,
        nTen,
        nHundred,
        nThowthant
    };

    for (int i = 0; i < 4; i++)
    {
        m_tRenderParam[i].m_f2UVPos.x = float(CalcValue[i] % ce_nSplit.x) / (float)ce_nSplit.x;
        m_tRenderParam[i].m_f2UVPos.y = float(CalcValue[i] / ce_nSplit.x) / (float)ce_nSplit.y;
    }

    CGameObject::Update();
}

void CScore::Draw()
{
    int a = 0;
    for (int i = 3; i >= 0; i--)
    {
        if (m_nScore < powf(10, i) && i != 0)
        {
            a++;
            continue;
        }
        m_tRenderParam[i].m_f3Pos = { -320.0f - (i + a) * 60.0f,-300.0f,0.0f };
        m_tParam = m_tRenderParam[i];
        CGameObject::Draw();
    }
}
