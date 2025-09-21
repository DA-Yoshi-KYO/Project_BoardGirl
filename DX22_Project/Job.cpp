#include "Job.h"
#include "Main.h"
#include "Player.h"
#include "SceneResult.h"
#include "PlayerAttack.h"
#include "Alphabet.h"
#include "MouseUI.h"

CJob::CJob()
    : m_tStatus{}, m_pTargetEnemy(nullptr), isEnd(false), m_pSkillUI{}
{
    CScene* pScene = GetScene();
    CPlayer* pPlayer = pScene->GetGameObject<CPlayer>();
}

CJob::~CJob()
{
}

void CJob::Init()
{
    CScene* pScene = GetScene();
    for (int i = (int)eSkill::QSkill; i < (int)eSkill::Max; i++)
    {
        std::string skillName = "";
        switch (i)
        {
        case (int)eSkill::QSkill: skillName = "QSkillUI"; break;
        case (int)eSkill::ESkill: skillName = "ESkillUI"; break;
        case (int)eSkill::RSkill: skillName = "RSkillUI"; break;
        }
        m_pSkillUI[i - 1] = pScene->AddGameObject<CSkillUI>(skillName,Tag::UI);
        m_pSkillUI[i - 1]->SetCurrentValue(m_tStatus.m_fSkillTime[i]);
        m_pSkillUI[i - 1]->SetMaxValue(m_tStatus.m_fSkillCooltime[i]);
    }             
    m_pSkillUI[0]->SetTransform(DirectX::XMFLOAT3(450.0f,180.0f,0.0f),DirectX::XMFLOAT3(100.0f,100.0f,0.0f));
    m_pSkillUI[1]->SetTransform(DirectX::XMFLOAT3(550.0f,280.0f,0.0f),DirectX::XMFLOAT3(100.0f,100.0f,0.0f));
    m_pSkillUI[2]->SetTransform(DirectX::XMFLOAT3(-520.0f,240.0f,0.0f),DirectX::XMFLOAT3(150.0f,150.0f,0.0f));

    CAlphabet* AlphaQ = pScene->AddGameObject<CAlphabet>("Q",Tag::UI);
    AlphaQ->AccessorPos(DirectX::XMFLOAT3(450.0f, 180.0f, -50.0f));
    AlphaQ->AccessorSize(DirectX::XMFLOAT3(100.0f, 100.0f, 0.0f));
    AlphaQ->SetAlphabet(ALPHA_Q);
    AlphaQ->AccessorColor(DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

    CAlphabet* AlphaE = pScene->AddGameObject<CAlphabet>("E",Tag::UI);
    AlphaE->AccessorPos(DirectX::XMFLOAT3(550.0f, 280.0f, -50.0f));
    AlphaE->AccessorSize(DirectX::XMFLOAT3(100.0f, 100.0f, 0.0f));
    AlphaE->SetAlphabet(ALPHA_E);
    AlphaE->AccessorColor(DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

    CMouseUI* MouseMiddle = pScene->AddGameObject<CMouseUI>("Middle", Tag::UI);
    MouseMiddle->AccessorPos(DirectX::XMFLOAT3(-520.0f, 240.0f, 0.0f));
    MouseMiddle->AccessorSize(DirectX::XMFLOAT3(100.0f, 100.0f, 0.0f));
    MouseMiddle->SetKind(MouseKind::Middle);
    MouseMiddle->AccessorColor(DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f));
}

void CJob::Update()
{
    for (int i = 0; i < (int)eSkill::Max; i++)
    {
            ObjectID id;
            id.m_nSameCount = 0;
        if (m_tStatus.m_fSkillTime[i] != m_tStatus.m_fSkillCooltime[i])
        {
            m_tStatus.m_fSkillTime[i] += fDeltaTime;
            m_tStatus.m_fSkillTime[i] = std::min(m_tStatus.m_fSkillTime[i], m_tStatus.m_fSkillCooltime[i]);

            if (i == (int)eSkill::NormalAttack) continue;
            switch (i)
            {
            case (int)eSkill::QSkill: id.m_sName = "Q"; break;
            case (int)eSkill::ESkill: id.m_sName = "E"; break;
            case (int)eSkill::RSkill: id.m_sName = "Middle"; break;
            }
            GetScene()->GetGameObject(id)->AccessorColor(DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f));
        }
        else
        {
            if (i == (int)eSkill::NormalAttack) continue;
            switch (i)
            {
            case (int)eSkill::QSkill: id.m_sName = "Q"; break;
            case (int)eSkill::ESkill: id.m_sName = "E"; break;
            case (int)eSkill::RSkill: id.m_sName = "Middle"; break;
            }
            GetScene()->GetGameObject(id)->AccessorColor(DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
        }

        m_tStatus.m_fDurationTime[i] += fDeltaTime;
        if (m_tStatus.m_fDurationTime[i] >= m_tStatus.m_fAttackDuration[i])
        {
            m_tStatus.m_fDurationTime[i] = 0.0f;
        }
        if (i != 0)
        {
            m_pSkillUI[i - 1]->SetCurrentValue(m_tStatus.m_fSkillTime[i]);
        }
    }
}

bool CJob::Skill(eSkill inKind)
{
    if (inKind >= eSkill::Max || inKind < eSkill::NormalAttack) return false;
    if (m_tStatus.m_fSkillTime[(int)inKind] < m_tStatus.m_fSkillCooltime[(int)inKind]) return false;

    switch (inKind)
    {
    case eSkill::NormalAttack: NormalAttack(); break;
    case eSkill::QSkill: QSkill(); break;
    case eSkill::ESkill: ESkill(); break;
    case eSkill::RSkill: RSkill();  break;
    default: break;
    }

    m_tStatus.m_fSkillTime[(int)inKind] = 0.0f;
    return true;
}

void CJob::Damage(int inDamage)
{
    if (isEnd) return;
    m_tStatus.m_nHP -= inDamage;
    if (m_tStatus.m_nHP <= 0 && !isEnd)
    {
        isEnd = true;
        FadeOut([]()
            {
                ChangeScene(new CSceneResult());
                FadeIn(nullptr);
            });
    }
}

void CJob::Attack(AttackState inState)
{
    CPlayerAttack* pAttack = GetScene()->AddGameObject<CPlayerAttack>("PlayerAttack", Tag::GameObject);
    pAttack->Init();
    pAttack->SetAttackState(inState);
    pAttack->AccessorRotate(GetScene()->GetGameObject<CPlayer>()->AccessorRotate());
}
