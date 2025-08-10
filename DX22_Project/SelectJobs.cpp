#include "SelectJobs.h"
#include "Easing.h"
#include "Input.h"
#include "Main.h"
#include "SceneGame.h"
#include "Oparation.h"

constexpr DirectX::XMINT2 ce_n2Split = { 6, 6 };
constexpr float ce_fRadius = 5.0f;
JobKind CSelectJobs::m_eSelectedJob = JobKind::Soldier;

enum class SEKind
{
    Decision,
    Select
};

void CSelectJobs::Init()
{
    m_eSelectedJob = JobKind::Soldier;

    m_pSpriteRenderer[(int)JobKind::Soldier] = AddComponent<CBillboardRenderer>();
    m_pSpriteRenderer[(int)JobKind::Soldier]->SetKey("Player");
    m_tJobsParam[(int)JobKind::Soldier].m_f2UVPos = { 0.0f / (float)ce_n2Split.x , 1.0f / (float)ce_n2Split.y };
    m_pSpriteRenderer[(int)JobKind::Wizard] = AddComponent<CBillboardRenderer>();
    m_pSpriteRenderer[(int)JobKind::Wizard]->SetKey("Player");
    m_tJobsParam[(int)JobKind::Wizard].m_f2UVPos = { 3.0f / (float)ce_n2Split.x , 1.0f / (float)ce_n2Split.y };
    m_pSpriteRenderer[(int)JobKind::Fighter] = AddComponent<CBillboardRenderer>();
    m_pSpriteRenderer[(int)JobKind::Fighter]->SetKey("Player");
    m_tJobsParam[(int)JobKind::Fighter].m_f2UVPos = { 1.0f / (float)ce_n2Split.x , 1.0f / (float)ce_n2Split.y };

    // 戦士の位置を初期値(手前)として、円状にキャラを配置する
    // 円の中心をXZ(0,0)とした時、各キャラの位置は
    // XZ = (0 + r * cos(θ) , 0 + r * sin(θ))となる

    for (int i = 0; i < (int)JobKind::Max; i++)
    {
        m_tJobsParam[i].m_f2UVSize = { 1.0f / (float)ce_n2Split.x, 1.0f / (float)ce_n2Split.y };
        m_tJobsParam[i].m_f3Pos.z = -(0.0f + ce_fRadius * cosf(DirectX::XMConvertToRadians((360.0f / (int)JobKind::Max) * i)));
        m_tJobsParam[i].m_f3Pos.x = 0.0f + ce_fRadius * sinf(DirectX::XMConvertToRadians((360.0f / (int)JobKind::Max) * i));
    }

    m_pSE.push_back(AddComponent<CAudio>());
    m_pSE[(int)SEKind::Decision]->Load(AUDIO_PATH("SE/Decision.wav"));
    m_pSE[(int)SEKind::Decision]->SetVolume(0.1f);

    m_pSE.push_back(AddComponent<CAudio>());
    m_pSE[(int)SEKind::Select]->Load(AUDIO_PATH("SE/Select.wav"));
    m_pSE[(int)SEKind::Select]->SetVolume(0.1f);

    m_bEnd = false;
    m_bTransition = false;
}

void CSelectJobs::Update()
{
    static float fTime = 0.0f;

    if (!m_bEnd)
    {
        if (!isMove)
        {
            fTime = 0.0f;
            m_tJobsParam[(int)m_eSelectedJob].m_f3Size = { 3.0f, 3.0f, 1.0f };
            for (int i = 0; i < (int)JobKind::Max; i++)
            {
                m_tTempParam[i] = m_tJobsParam[i];
            }

            int nSelect = (int)m_eSelectedJob;
            if (!isMove)
            {
                if (IsKeyTrigger(VK_RIGHT))
                {
                    m_pSE[(int)SEKind::Select]->Play();
                    nSelect++;
                    if (nSelect == (int)JobKind::Max)
                    {
                        nSelect = 0;
                    }
                    isNext = true;
                    isMove = true;
                }
                else if (IsKeyTrigger(VK_LEFT))
                {
                    m_pSE[(int)SEKind::Select]->Play();
                    nSelect--;
                    if (nSelect < 0)
                    {
                        nSelect = (int)JobKind::Max - 1;
                    }
                    isNext = false;
                    isMove = true;
                }
                else if (IsKeyTrigger(VK_SPACE))
                {
                    m_pSE[(int)SEKind::Decision]->Play();
                    m_bEnd = true;
                }
            }
            m_eSelectedJob = (JobKind)nSelect;
        }
        else
        {
            for (int i = 0; i < (int)JobKind::Max; ++i)
            {
                m_tJobsParam[i].m_f3Size = { 1.0f, 1.0f, 1.0f };
            }
            if (isNext)
            {
                for (int i = 0; i < (int)JobKind::Max; i++)
                {
                    int backIndex = (i - 1 + (int)JobKind::Max) % (int)JobKind::Max;
                    DirectX::XMFLOAT3 f3Disance = m_tTempParam[backIndex].m_f3Pos - m_tTempParam[i].m_f3Pos;
                    m_tJobsParam[i].m_f3Pos = (CEasing::EaseOutBack(fTime, 1.0f) * f3Disance) + m_tTempParam[i].m_f3Pos;
                }
            }
            else
            {
                for (int i = 0; i < (int)JobKind::Max; i++)
                {
                    int nextIndex = (i + 1) % (int)JobKind::Max;
                    DirectX::XMFLOAT3 f3Disance = m_tTempParam[nextIndex].m_f3Pos - m_tTempParam[i].m_f3Pos;
                    m_tJobsParam[i].m_f3Pos = (CEasing::EaseOutBack(fTime, 1.0f) * f3Disance) + m_tTempParam[i].m_f3Pos;
                }
            }

            if (fTime >= 1.0f)
            {
                isMove = false;
            }

            fTime += fDeltaTime;
        }
    }
    else
    {
        if (!m_pSE[(int)SEKind::Decision]->IsPlay() && !m_bTransition && m_bEnd)
        {
            m_bTransition = true;
            ChangeScene(new CSceneGame());
        }
    }
 
    CGameObject::Update();
}

void CSelectJobs::Draw()
{
    for (int i = 0; i < (int)JobKind::Max; ++i)
    {
        m_pSpriteRenderer[i]->SetRendererParam(m_tJobsParam[i]);
        m_pSpriteRenderer[i]->Draw();
    }
}
