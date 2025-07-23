#include "SelectJobs.h"

constexpr DirectX::XMINT2 ce_n2Split = { 6, 6 };
constexpr float ce_fRadius = 5.0f;

void CSelectJobs::Init()
{
    m_pSpriteRenderer[(int)JobKind::Soldier] = AddComponent<CSprite3DRenderer>();
    m_pSpriteRenderer[(int)JobKind::Soldier]->Load(TEXTURE_PATH("Jobs.png"));
    m_pSpriteRenderer[(int)JobKind::Wizard] = AddComponent<CSprite3DRenderer>();
    m_pSpriteRenderer[(int)JobKind::Wizard]->Load(TEXTURE_PATH("Jobs.png"));
    m_pSpriteRenderer[(int)JobKind::Fighter] = AddComponent<CSprite3DRenderer>();
    m_pSpriteRenderer[(int)JobKind::Fighter]->Load(TEXTURE_PATH("Jobs.png"));
    m_tJobsParam[(int)JobKind::Soldier].m_f2UVPos = { 0.0f / (float)ce_n2Split.x , 1.0f / (float)ce_n2Split.y };
    m_tJobsParam[(int)JobKind::Wizard].m_f2UVPos = { 3.0f / (float)ce_n2Split.x , 1.0f / (float)ce_n2Split.y };
    m_tJobsParam[(int)JobKind::Fighter].m_f2UVPos = { 1.0f / (float)ce_n2Split.x , 1.0f / (float)ce_n2Split.y };
    // 戦士の位置を初期値(手前)として、円状にキャラを配置する
    // 円の中心をXZ(0,0)とした時、各キャラの位置は
    // XZ = (0 + r * cos(θ) , 0 + r * sin(θ))となる

    for (int i = 0; i < (int)JobKind::Max; i++)
    {
        m_tJobsParam[i].m_f2UVSize = { 1.0f / (float)ce_n2Split.x, 1.0f / (float)ce_n2Split.y };
        m_tJobsParam[i].m_f3Pos.x = 0.0f + ce_fRadius * cosf(DirectX::XMConvertToRadians((360.0f / (int)JobKind::Max) * i));
        m_tJobsParam[i].m_f3Pos.z = 0.0f + ce_fRadius * sinf(DirectX::XMConvertToRadians((360.0f / (int)JobKind::Max) * i));
    }
}

void CSelectJobs::Draw()
{

    for (int i = 0; i < (int)JobKind::Max; ++i)
    {
        m_tJobsParam[i].m_f3Size = { 1.0f, 1.0f, 1.0f };
        m_pSpriteRenderer[i]->SetDepth(false);
        m_pSpriteRenderer[i]->SetRendererParam(m_tJobsParam[i]);
        m_pSpriteRenderer[i]->Draw();
    }
}
