// インクルード部
#include "Player.h"
#include "Input.h"
#include "BillboardRenderer.h"
#include "SelectJobs.h"
#include "Soldier.h"
#include "Wizard.h"
#include "Fighter.h"
#include "Main.h"
#include "Effect.h"
#include "Oparation.h"
#include "DebugSystem.h"
#include "Field.h"

// 定数定義
constexpr float ce_fRotatePow = 0.01f;   // 回転速度
constexpr float ce_fMovePow = 0.15f;    // 移動速度
constexpr DirectX::XMINT2 ce_n2Split = { 6, 6 };

enum class SEKind
{
    Walk,
    Jump,
    NormalSkill,
    QSkill,
    ESkill,
    RSkill,

    Max
};

void CPlayer::Init()
{
    // コンポーネントの追加
	AddComponent<CBillboardRenderer>()->SetKey("Player");
    m_pCollision = AddComponent<CCollisionObb>();

    // 汎用パラメータの初期化
	m_tParam.m_f3Pos = { 0.0f,2.0f,0.0f };
    m_f3OldPos = m_tParam.m_f3Pos;
	m_tParam.m_f3Size = { 1.0f,1.0f,1.0f };
    m_pCollision->AccessorCenter(m_tParam.m_f3Pos);
    m_pCollision->AccessorHalfSize(m_tParam.m_f3Size / 2.0f);
    m_pCollision->AccessorTag("PlayerBody");

    // 特有パラメータの初期化
	m_f3Velocity = {};
	m_bJump = false;

    for (int i = 0; i < (int)SEKind::Max; i++)
    {
        m_pSE.push_back(AddComponent<CAudio>());
    }
    m_pSE[(int)SEKind::Jump]->Load(AUDIO_PATH("SE/Jump.wav"));
    m_pSE[(int)SEKind::Walk]->Load(AUDIO_PATH("SE/Walk.wav"));


    m_eJobKind = CSelectJobs::GetSelectedJob();
    switch (m_eJobKind)
    {
    case JobKind::Soldier:
        m_pJob = std::make_unique<CSoldier>();
        m_tParam.m_f2UVPos = { 0.0f / (float)ce_n2Split.x , 1.0f / (float)ce_n2Split.y };
        m_pSE[(int)SEKind::NormalSkill]->Load(AUDIO_PATH("SE/SoldierNomalSkill.wav"));
        m_pSE[(int)SEKind::QSkill]->Load(AUDIO_PATH("SE/SoldierQSkill.wav"));
        m_pSE[(int)SEKind::ESkill]->Load(AUDIO_PATH("SE/SoldierESkill.wav"));
        m_pSE[(int)SEKind::RSkill]->Load(AUDIO_PATH("SE/SoldierRSkill.wav"));
        break;
    case JobKind::Wizard:
        m_pJob = std::make_unique<CWizard>();
        m_tParam.m_f2UVPos = { 3.0f / (float)ce_n2Split.x , 1.0f / (float)ce_n2Split.y };
        m_pSE[(int)SEKind::NormalSkill]->Load(AUDIO_PATH("SE/WizardNomalSkill.wav"));
        m_pSE[(int)SEKind::QSkill]->Load(AUDIO_PATH("SE/WizardQSkill.wav"));
        m_pSE[(int)SEKind::ESkill]->Load(AUDIO_PATH("SE/WizardESkill.wav"));
        m_pSE[(int)SEKind::RSkill]->Load(AUDIO_PATH("SE/WizardRSkill.wav"));
        break;
    case JobKind::Fighter:
        m_pJob = std::make_unique<CFighter>();
        m_tParam.m_f2UVPos = { 1.0f / (float)ce_n2Split.x , 1.0f / (float)ce_n2Split.y };
        m_pSE[(int)SEKind::NormalSkill]->Load(AUDIO_PATH("SE/SoldierNomalSkill.wav"));
        m_pSE[(int)SEKind::QSkill]->Load(AUDIO_PATH("SE/SoldierQSkill.wav"));
        m_pSE[(int)SEKind::ESkill]->Load(AUDIO_PATH("SE/SoldierESkill.wav"));
        m_pSE[(int)SEKind::RSkill]->Load(AUDIO_PATH("SE/SoldierRSkill.wav"));
        break;
    case JobKind::Max:
        break;
    default:
        break;
    }

    m_pJob->Init();

    for (int i = 0; i < (int)SEKind::Max; i++)
    {
        m_pSE[i]->SetVolume(0.1f);
    }

    m_tParam.m_f2UVSize = { 1.0f / (float)ce_n2Split.x, 1.0f / (float)ce_n2Split.y };

    m_pHPBar = GetScene()->AddGameObject<CHPBar>("HPBar", Tag::GameObject);
    m_pHPBar->SetRenderState(DirectX::XMFLOAT3(2.0f, 0.25f, 1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
    m_pHPBar->SetMaxHP(m_pJob->GetHP());
    m_pHPBar->SetCurrentHP(m_pJob->GetHP());

    m_pHPBar->SetParentID(m_tID);
    m_bDamage = false;

}

void CPlayer::Update()
{
    m_f3OldPos = m_tParam.m_f3Pos;

    // 移動処理
	PlayerMove();
    PlayerSkill();

    m_pCollision->AccessorCenter(m_tParam.m_f3Pos);
    m_pCollision->AccessorHalfSize(m_tParam.m_f3Size / 2.0f);

    m_pHPBar->SetCurrentHP(m_pJob->GetHP());



    CGameObject::Update();
}

void CPlayer::OnColliderHit(CCollisionBase* other, std::string thisTag)
{
    if (other->AccessorTag() == "EnemyBody")
    {
        CEnemyBase* pEnemy = dynamic_cast<CEnemyBase*>(other->GetGameObject());

        if (thisTag == "PlayerBody")
        {
            m_tParam.m_f3Pos = m_f3OldPos;
        }
    }
}

void CPlayer::Damage(int inDamage)
{
    m_pJob->Damage(inDamage);
}

int CPlayer::Inspecter(bool isEnd)
{
    int nChildCnt = CGameObject::Inspecter(false);

    if (ImGui::CollapsingHeader(std::string("[Status]").c_str()))
    {
        ImGui::BeginChild(ImGui::GetID((void*)nChildCnt), ImVec2(ce_f2InspecterSize.x,ce_f2InspecterSize.y * 4));

        PlayerStatus tStatus = m_pJob->GetStatus();
        ImGui::Text(std::string("HP:" + std::to_string(tStatus.m_nHP)).c_str());
        ImGui::Text(std::string("ATK:" + std::to_string(tStatus.m_nAttack)).c_str());
        ImGui::Text(std::string("DEF:" + std::to_string(tStatus.m_nDefense)).c_str());
        ImGui::Text(std::string("CRT:" + std::to_string(tStatus.m_fCriticalPercentage) + "%%").c_str());
        
        ImGui::EndChild();
        nChildCnt++;
    }

    ImGui::End();

    return nChildCnt;
}

void CPlayer::PlayerMove()
{
    // プレイヤーの前方向と右方向を取得
	DirectX::XMFLOAT3 f3ForWard = GetForward();
	DirectX::XMFLOAT3 f3Right = GetRight();

    // 移動量は初期化してから計算する
	m_f3Velocity.x = 0.0f;
	m_f3Velocity.z = 0.0f;

    if (!IsDebugMode())
    {
        if (ShowCursor(false) < -1)
        {
            ShowCursor(true);
        }
        POINT mousePos = *GetMousePosition();
	    m_tParam.m_f3Rotate.y += DirectX::XMConvertToRadians(mousePos.x * ce_fRotatePow);
	    m_tParam.m_f3Rotate.x += DirectX::XMConvertToRadians(mousePos.y * ce_fRotatePow);
        POINT center;
        center.x = 0;
        center.y = 0;
        SetMousePosition(center);
    }
    else
    {
        if (ShowCursor(true) > 0)
        {
            ShowCursor(false);
        }
    }
    // 回転の速度は-45度から45度の範囲に制限する
	constexpr float ce_fMinRotateX = DirectX::XMConvertToRadians(-45.0f);
	constexpr float ce_fMaxRotateX = DirectX::XMConvertToRadians(45.0f);
	m_tParam.m_f3Rotate.x = std::clamp(m_tParam.m_f3Rotate.x, ce_fMinRotateX, ce_fMaxRotateX);

    // キー入力による移動処理
	if (IsKeyPress('W'))
	{
		m_f3Velocity.x += f3ForWard.x * ce_fMovePow;
		m_f3Velocity.z += f3ForWard.z * ce_fMovePow;
	}
	else if (IsKeyPress('S'))
	{
		m_f3Velocity.x -= f3ForWard.x * ce_fMovePow;
		m_f3Velocity.z -= f3ForWard.z * ce_fMovePow;
	}
	if (IsKeyPress('A'))
	{
		m_f3Velocity.x -= f3Right.x * ce_fMovePow;
		m_f3Velocity.z -= f3Right.z * ce_fMovePow;
	}
	else if (IsKeyPress('D'))
	{
		m_f3Velocity.x += f3Right.x * ce_fMovePow;
		m_f3Velocity.z += f3Right.z * ce_fMovePow;
	}

    if ((m_f3Velocity.x != 0.0f || m_f3Velocity.z != 0.0f) && !m_pSE[(int)SEKind::Walk]->IsPlay())
    {
        m_pSE[(int)SEKind::Walk]->Play();
    }

	if (IsKeyTrigger(VK_SPACE) && !m_bJump)
	{
        m_pSE[(int)SEKind::Jump]->Play();
		m_f3Velocity.y += 0.35f;
		m_bJump = true;
	}

    // 移動量を使用してプレイヤーの位置を更新
    m_tParam.m_f3Pos.x += m_f3Velocity.x;
	m_tParam.m_f3Pos.y += m_f3Velocity.y;
	m_tParam.m_f3Pos.z += m_f3Velocity.z;

    DirectX::XMFLOAT3 origin = DirectX::XMFLOAT3(m_tParam.m_f3Pos.x, m_tParam.m_f3Pos.y - m_tParam.m_f3Size.y * 0.5f, m_tParam.m_f3Pos.z);
    HitResult result = CField::RayIntersectsTriangle(m_tParam.m_f3Pos, DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f));

    if (result.Distance <= m_tParam.m_f3Size.y * 0.5f)
    {
        m_tParam.m_f3Pos.y = result.Position.y + m_tParam.m_f3Size.y * 0.5f;
        m_f3Velocity.y = 0.0f;
        m_bJump = false;
    }
    else
    {
        // 重力
        m_f3Velocity.y -= 0.015f;
    } 
}

void CPlayer::PlayerSkill()
{
    if (IsMouseButtonTrigger(MOUSEBUTTON_L))
    {
        if(m_pJob->Skill(eSkill::NormalAttack)) m_pSE[(int)SEKind::NormalSkill]->Play();
    }
    if (IsKeyTrigger('Q'))
    {
        if (m_pJob->Skill(eSkill::QSkill)) m_pSE[(int)SEKind::QSkill]->Play();
    }
    if (IsKeyTrigger('E'))
    {
        if (m_pJob->Skill(eSkill::ESkill)) m_pSE[(int)SEKind::ESkill]->Play();
    }
    if (IsMouseButtonTrigger(MOUSEBUTTON_M))
    {
        if (m_pJob->Skill(eSkill::RSkill)) m_pSE[(int)SEKind::RSkill]->Play();
    }

    m_pJob->Update();
}
