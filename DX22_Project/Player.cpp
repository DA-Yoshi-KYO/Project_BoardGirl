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
#include "HPBar.h"
#include "Job.h"
#include "CollisionObb.h"

// 定数・マクロ定義
constexpr float ce_fRotatePow = 0.01f;   // 回転速度
constexpr float ce_fMovePow = 0.15f;    // 移動速度
constexpr DirectX::XMINT2 ce_n2Split = { 6, 6 };    // プレイヤーのスプライトシート分割数

// SEの種類
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

CPlayer::CPlayer()
    : CGameObject()
    , m_f3Velocity{}, m_eJobKind(CSelectJobs::GetSelectedJob())
    , m_pCollision(nullptr), m_pHPBar(nullptr), m_pJob(nullptr)
    , m_bDamage(false), m_bJump(false)
{
    // 汎用パラメータの初期化
    m_tParam.m_f3Pos = DirectX::XMFLOAT3(0.0f, 2.0f, -10.0f);
    m_tParam.m_f3Size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
    m_tParam.m_f2UVSize = DirectX::XMFLOAT2(1.0f / (float)ce_n2Split.x, 1.0f / (float)ce_n2Split.y);
    m_f3OldPos = m_tParam.m_f3Pos;
}

void CPlayer::Init()
{
    // コンポーネントの追加
    m_pCollision = AddComponent<CCollisionObb>();
    CBillboardRenderer* pRenderer = AddComponent<CBillboardRenderer>();
    for (int i = 0; i < (int)SEKind::Max; i++)
    {
        m_pSE.push_back(AddComponent<CAudio>());
    }

    // 描画に使うテクスチャのキーをセット
    pRenderer->SetKey("Player");

    // コリジョン情報のセット
    m_pCollision->AccessorCenter(m_tParam.m_f3Pos);
    m_pCollision->AccessorHalfSize(m_tParam.m_f3Size / 2.0f);
    m_pCollision->AccessorTag("PlayerBody");

    // SEのロード
    m_pSE[(int)SEKind::Jump]->Load(AUDIO_PATH("SE/Jump.wav"));  // ジャンプ音
    m_pSE[(int)SEKind::Walk]->Load(AUDIO_PATH("SE/Walk.wav"));  // 歩行音

    // ジョブ情報の作成
    // ジョブによってUV座標、ロードするSEを変える
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

    // ボリュームの調整
    for (int i = 0; i < (int)SEKind::Max; i++)
    {
        m_pSE[i]->SetVolume(0.1f);
    }

    // HPバーを作成し、パラメータをセットする
    m_pHPBar = GetScene()->AddGameObject<CHPBar>("HPBar", Tag::GameObject);
    m_pHPBar->SetRenderState(DirectX::XMFLOAT3(2.0f, 0.25f, 1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
    m_pHPBar->SetMaxHP(m_pJob->GetHP());
    m_pHPBar->SetCurrentHP(m_pJob->GetHP());

    // 親としてプレイヤーを紐付ける
    m_pHPBar->SetParentID(m_tID);
}

void CPlayer::Update()
{
    // 座標の保存
    m_f3OldPos = m_tParam.m_f3Pos;

	PlayerMove();   // 移動処理
    PlayerSkill();  // スキル発動処理

    // コリジョン情報の更新
    m_pCollision->AccessorCenter(m_tParam.m_f3Pos);
    m_pCollision->AccessorHalfSize(m_tParam.m_f3Size / 2.0f);

    // 現在HPをHPバーに渡す
    m_pHPBar->SetCurrentHP(m_pJob->GetHP());

    CGameObject::Update();
}

void CPlayer::OnColliderHit(CCollisionBase* other, std::string thisTag)
{
    // 自身の身体に当たった際の処理
    if (thisTag == "PlayerBody")
    {
        // 当たった相手が敵の身体だった場合
        if (other->AccessorTag() == "EnemyBody")
        {
            // 位置を留める
            m_tParam.m_f3Pos = m_f3OldPos;
        }
    }
}

void CPlayer::Damage(int inDamage)
{
    // ジョブのステータスであるHPを減らす
    m_pJob->Damage(inDamage);
}

int CPlayer::Inspecter(bool isEnd)
{
    // 親のインスペクターの描画処理から子要素の個数を受け取る
    int nChildCnt = CGameObject::Inspecter(false);

    // ステータスの表示
    if (ImGui::CollapsingHeader(std::string("[Status]").c_str()))
    {
        // 子要素の初期化
        ImGui::BeginChild(ImGui::GetID((void*)nChildCnt), ImVec2(ce_f2InspecterSize.x,ce_f2InspecterSize.y * 4));

        // ステータスの描画
        PlayerStatus tStatus = m_pJob->GetStatus();
        ImGui::Text(std::string("HP:" + std::to_string(tStatus.m_nHP)).c_str());
        ImGui::Text(std::string("ATK:" + std::to_string(tStatus.m_nAttack)).c_str());
        
        // 子要素の終了
        ImGui::EndChild();
        // 子要素の数をインクリメント
        nChildCnt++;
    }

    // IMGUIウィンドウの終了
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

    // デバッグモードでない場合
    if (!IsDebugMode())
    {
        // カーソルを非表示にする
        // ※ShowCursor関数は内部カウンタがあり、trueでインクリメント、falseでデクリメントを行う
        // 非表示が-1以下、表示が0以上の為、内部カウンタの結果が必ず非表示-1となるように制御する
        if (ShowCursor(false) < -1)
        {
            ShowCursor(true);
        }

        // マウスの座標を取得する
        POINT mousePos = *GetMousePosition();

        // 取得したマウス座標は中心(0,0)の為、取得した座標をそのまま中心からの移動量として扱う
        // 移動量に応じて回転を加算する
	    m_tParam.m_f3Rotate.y += DirectX::XMConvertToRadians(mousePos.x * ce_fRotatePow);
	    m_tParam.m_f3Rotate.x += DirectX::XMConvertToRadians(mousePos.y * ce_fRotatePow);

        // マウスの座標を中央に戻す
        POINT center;
        center.x = 0;
        center.y = 0;
        SetMousePosition(center);
    }
    else
    {
        // カーソルを表示する
        if (ShowCursor(true) > 0)
        {
            ShowCursor(false);
        }
    }
        
    // 回転の速度は1フレーム当たり-45度から45度の範囲に制限する
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

    // 移動している時にSEを鳴らす
    if ((m_f3Velocity.x != 0.0f || m_f3Velocity.z != 0.0f) && !m_pSE[(int)SEKind::Walk]->IsPlay())
    {
        m_pSE[(int)SEKind::Walk]->Play();
    }

    // ジャンプ処理
	if (IsKeyTrigger(VK_SPACE) && !m_bJump)
	{
        m_pSE[(int)SEKind::Jump]->Play();   // SE
		m_f3Velocity.y += 0.35f;    // Velocity加算
		m_bJump = true; // ジャンプフラグオン
	}

    // 移動量を使用してプレイヤーの位置を更新
    m_tParam.m_f3Pos.x += m_f3Velocity.x;
	m_tParam.m_f3Pos.y += m_f3Velocity.y;
	m_tParam.m_f3Pos.z += m_f3Velocity.z;

    // 地形モデルとの当たり判定を取る為にレイキャストを行う
    // レイの原点を足元にする
    DirectX::XMFLOAT3 origin = DirectX::XMFLOAT3(m_tParam.m_f3Pos.x, m_tParam.m_f3Pos.y - m_tParam.m_f3Size.y * 0.5f, m_tParam.m_f3Pos.z);
    // 地形モデルとの当たり判定を取得
    HitResult result = CField::RayIntersectsTriangle(m_tParam.m_f3Pos, DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f));
    // キャストした結果原点とヒット位置の距離がサイズの半分だったら
    if (result.Distance <= m_tParam.m_f3Size.y * 0.5f)
    {
        // その位置に留める
        m_tParam.m_f3Pos.y = result.Position.y + m_tParam.m_f3Size.y * 0.5f;
        // Y方向のVelocityを無効にする
        m_f3Velocity.y = 0.0f;
        // ジャンプフラグオフ
        m_bJump = false;
    }
    else
    {
        // 地形と衝突していない時は重力を加算する
        m_f3Velocity.y -= 0.015f;
    }
}

void CPlayer::PlayerSkill()
{
    // キー入力に応じて出すスキルを変える
    // スキル発動が成功したらSEを鳴らす
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

    // ジョブの更新処理
    m_pJob->Update();
}
