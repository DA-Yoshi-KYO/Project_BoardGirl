#include "Timer.h"
#include "SpriteRenderer.h"

constexpr DirectX::XMINT2 ce_nSplit = { 5,5 };

int CTimer::m_nTimeCount = 0;

CTimer::~CTimer()
{

}

void CTimer::Init()
{
    CSpriteRenderer* pRenderer = AddComponent<CSpriteRenderer>();
    pRenderer->SetKey("Number");

    for (int i = 0; i < 5; i++)
    {
        m_tRenderParam[i].m_f3Size = { 100.0f,100.0f,100.0f };
        m_tRenderParam[i].m_f3Pos = { 320.0f + i * 60.0f,-300.0f,0.0f };
        m_tRenderParam[i].m_f3Rotate = { 0.0f,0.0f,0.0f };
        m_tRenderParam[i].m_f2UVPos = { 0.0f,0.0f };
        m_tRenderParam[i].m_f2UVSize = { 1.0f / (float)ce_nSplit.x,1.0f / (float)ce_nSplit.y };
        m_tRenderParam[i].m_f4Color = { 0.0f,0.0f,0.0f,1.0f };
    }
}

void CTimer::Update()
{
    int nMinitue = m_nTimeCount / 60;
    int nMinitueTen = nMinitue / 10;
    int nMinitueOne = nMinitue % 10;

    int nSecond = m_nTimeCount % 60;
    int nSecondTen = nSecond / 10;
    int nSecondOne = nSecond % 10;

    int CalcValue[] =
    {
        nMinitueTen,
        nMinitueOne,
        10, // ：は10番目に充てられている
        nSecondTen,
        nSecondOne
    };

    for (int i = 0; i < 5; i++)
    {
        m_tRenderParam[i].m_f2UVPos.x = float(CalcValue[i] % ce_nSplit.x) / (float)ce_nSplit.x;
        m_tRenderParam[i].m_f2UVPos.y = float(CalcValue[i] / ce_nSplit.x) / (float)ce_nSplit.y;
    }

    m_fTime += fDeltaTime;
    m_nTimeCount = m_fTime;
    CGameObject::Update();
}

void CTimer::Draw()
{
    for (int i = 0; i < 5; i++)
    {
        m_tParam = m_tRenderParam[i];
        CGameObject::Draw();
    }
}
