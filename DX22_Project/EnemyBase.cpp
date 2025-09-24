#include "EnemyBase.h"
#include "Main.h"
#include "Oparation.h"
#include "DebugSystem.h"
#include "Field.h"
#include "Score.h"
#include "Player.h"
#include "CollisionObb.h"
#include "HPBar.h"

CEnemyBase::CEnemyBase()
    : CGameObject()
    , m_tEnemyStatus{}, m_f3Velocity{}
    , m_pPlayer(nullptr), m_pHPBar(nullptr), m_pCollision{}
    , m_fInvincibleTime(0.0f), m_fAttackTime(0.0f)
{

}

CEnemyBase::~CEnemyBase()
{

}

void CEnemyBase::Init()
{
    // コリジョンの種類分追加する
    for (int i = 0; i < (int)eEnemyCollision::Max; i++)
    {
        // コンポーネントの追加
        m_pCollision[i] = AddComponent<CCollisionObb>();

        // アクティブにする
        m_pCollision[i]->AccessorActive(true);

        // 中心座標のセット
        m_pCollision[i]->AccessorCenter(m_tParam.m_f3Pos);
    };
    // サイズは派生先で決定する

    // HPバーを作成し、自身のIDとHPをセット
    m_pHPBar = GetScene()->AddGameObject<CHPBar>("HPBar",Tag::GameObject);
    m_pHPBar->SetRenderState(DirectX::XMFLOAT3(2.0f, 0.25f, 1.0f), DirectX::XMFLOAT4(1.0f,0.0f,0.0f,1.0f));
    m_pHPBar->SetMaxHP(m_tEnemyStatus.m_nHP);
    m_pHPBar->SetCurrentHP(m_tEnemyStatus.m_nHP);
    m_pHPBar->SetParentID(m_tID);

    // プレイヤーのインスタンスを取得
    m_pPlayer = GetScene()->GetGameObject<CPlayer>();
}

void CEnemyBase::Update()
{
    // 古い座標の保存
    m_f3OldPos = m_tParam.m_f3Pos;

    // 動ける状態なら
    if (m_tEnemyStatus.m_bMove)
    {
        // プレイヤーへのベクトルを測り、その方向へ移動する

        // プレイヤーの位置を取得
        DirectX::XMFLOAT3 f3PlayerPos = m_pPlayer->AccessorPos();
        // XZ方向への座標に限定する
        DirectX::XMFLOAT2 f2PlayerPosXZ = DirectX::XMFLOAT2(f3PlayerPos.x, f3PlayerPos.z);
        // 計算用にVECTORに変換
        DirectX::XMVECTOR vecPlayerPos = DirectX::XMLoadFloat2(&f2PlayerPosXZ);

        // 敵の座標からXZを取得する
        DirectX::XMFLOAT2 f2EnemyPosXZ = DirectX::XMFLOAT2(m_tParam.m_f3Pos.x, m_tParam.m_f3Pos.z);
        // 計算用にVECTORに変換
        DirectX::XMVECTOR vecEnemyPos = DirectX::XMLoadFloat2(&f2EnemyPosXZ);

        // 二点の距離を測り、正規化する
        DirectX::XMVECTOR vecDirection = DirectX::XMVector2Normalize(vecPlayerPos - vecEnemyPos);
        // 速度をかける
        DirectX::XMVECTOR vecVelocity = vecDirection * m_tEnemyStatus.m_fSpeed;

        // VECTORから移動量に変換する
        DirectX::XMFLOAT2 f2Velocity;
        DirectX::XMStoreFloat2(&f2Velocity, vecVelocity);
        m_f3Velocity.x = f2Velocity.x;
        m_f3Velocity.z = f2Velocity.y;

        // 座標を更新する
        m_tParam.m_f3Pos.x += m_f3Velocity.x;
        m_tParam.m_f3Pos.z += m_f3Velocity.z;

        // 移動方向を向いている方向とし、atan2を使い回転を計算する
        // 回転の結果はOBBの処理で使用する
        DirectX::XMFLOAT2 f2Direction;
        DirectX::XMStoreFloat2(&f2Direction, vecDirection);
        m_tParam.m_f3Rotate.y = atan2(f2Direction.x, f2Direction.y);
    }
    // 移動できるかは後の索敵範囲にいるかで決定するので、フラグを毎フレーム初期化する
    m_tEnemyStatus.m_bMove = false;

    // 各種コリジョンの中心座標を更新する
    for (int i = 0; i <= (int)eEnemyCollision::Attack; i++)
    {
        m_pCollision[i]->AccessorCenter(m_tParam.m_f3Pos);
    }

    // Y方向のVelocityは常に加算する
    m_tParam.m_f3Pos.y += m_f3Velocity.y;

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
    }
    else
    {
        // 地形と衝突していない時は重力を加算する
        m_f3Velocity.y -= 0.015f;
    }

    // ダメージを受けている時に点滅させる処理
    static float fSwitchTime = 0.0f;
    if (m_tEnemyStatus.m_bDamage)
    {
        // 透明度の切り替えは0.1秒ごとに行う
        if (fSwitchTime >= 0.1f)
        {
            // 一度現在のα値を受け取る
            int alpha = (int)m_tParam.m_f4Color.w;
            // 排他的論理和を使い、α値を反転させる
            alpha ^= 1;
            // 反転させたα値を適用
            m_tParam.m_f4Color.w = static_cast<float>(alpha);
            // 切り替え時間の初期化
            fSwitchTime = 0.0f;
        }

        // 点滅時間(無敵時間)は1秒とする
        if (m_fInvincibleTime >= 1.0f)
        {
            // 無敵状態の解除
            m_tEnemyStatus.m_bDamage = false;
            // α値を元に戻す
            m_tParam.m_f4Color.w = 1.0f;
            // タイマーの初期化
            m_fInvincibleTime = 0.0f;
            fSwitchTime = 0.0f;
        }
        // タイマーを加算する
        m_fInvincibleTime += fDeltaTime;
        fSwitchTime += fDeltaTime;
    }

    // 攻撃は2秒ごとに行う
    if (m_fAttackTime >= 2.0f)
    {
        Attack();
        m_fAttackTime = 0.0f;
    }

    // HPバーに現在のHPを渡す
    m_pHPBar->SetCurrentHP(m_tEnemyStatus.m_nHP);

    CGameObject::Update();
}

void CEnemyBase::OnColliderHit(CCollisionBase* other, std::string thisTag)
{
    // 衝突先のコリジョン識別用タグを取得
    std::string otherTag = other->AccessorTag();

    // 自身の身体に当たった際の処理
    if (thisTag == "EnemyBody")
    {
        if (otherTag == "PlayerBody" || otherTag == "EnemyBody")
        {
            // プレイヤーや敵の身体に当たったらその位置に留める
            m_tParam.m_f3Pos = m_f3OldPos;
        }
        return;
    }

    // 索敵範囲に入った際の処理
    if (thisTag == "EnemySearch")
    {
        if (otherTag == "PlayerBody")
        {
            // プレイヤーが入ってきたら動ける状態にし、追跡する
            m_tEnemyStatus.m_bMove = true;
        }
        return;
    }

    // 敵の攻撃可能範囲に入った際の処理
    if (thisTag == "EnemyAttack")
    {
        if (other->AccessorTag() == "PlayerBody")
        {
            // プレイヤーが入ってきたら動きを止めてタイマーを加算し、規定時間が経ったら攻撃を行う
            m_fAttackTime += fDeltaTime;
            m_tEnemyStatus.m_bMove = false;
        }

        return;
    }
}

void CEnemyBase::Attack()
{
    // 派生先で攻撃ステータスを決定
}

void CEnemyBase::Attack(AttackState inState)
{
    // 攻撃用オブジェクトの生成
    CEnemyAttack* pAttack = GetScene()->AddGameObject<CEnemyAttack>("EnemyAttack", Tag::GameObject);
    pAttack->Init();

    // 派生先から受け取ったステータスを設定
    pAttack->SetAttackState(inState);

    // OBBに使用する為回転情報を渡す
    pAttack->AccessorRotate(m_tParam.m_f3Rotate);
}

void CEnemyBase::Destroy()
{
    m_bDestroy = true;

    // 敵が破棄される際HPBarも同時に破棄する
    m_pHPBar->Destroy();
}

void CEnemyBase::Damage(int inDamage)
{
    // ダメージが0ならば処理を行わない
    if (inDamage <= 0) return;

    // 無敵時間中ならば処理を行わない
    if (m_tEnemyStatus.m_bDamage) return;

    // ダメージ処理
    m_tEnemyStatus.m_nHP -= inDamage;
    // ダメージを受けたら無敵状態にする
    m_tEnemyStatus.m_bDamage = true;

    // HPが0以下になったらスコアを加算しオブジェクトを破棄する
    if (m_tEnemyStatus.m_nHP <= 0)
    {
        CScore::AddScore(m_tEnemyStatus.m_nScore);
        Destroy();
    }
}

void CEnemyBase::SetInvincibly(bool isInvincibly)
{
    m_tEnemyStatus.m_bDamage = isInvincibly;
}

eEnemyStatePattern CEnemyBase::GetPattern(DirectX::XMFLOAT3 inAttackHarfSize)
{
    // プレイヤーの位置を取得
    DirectX::XMFLOAT3 f3PlayerPos = m_pPlayer->AccessorPos();
    // XZ方向への座標に限定する
    DirectX::XMFLOAT2 f2PlayerPosXZ = DirectX::XMFLOAT2(f3PlayerPos.x, f3PlayerPos.z);
    // 計算用にVECTORに変換
    DirectX::XMVECTOR vecPlayerPos = DirectX::XMLoadFloat2(&f2PlayerPosXZ);

    // 敵の座標からXZを取得する
    DirectX::XMFLOAT2 f2EnemyPosXZ = DirectX::XMFLOAT2(m_tParam.m_f3Pos.x, m_tParam.m_f3Pos.z);
    // 計算用にVECTORに変換
    DirectX::XMVECTOR vecEnemyPos = DirectX::XMLoadFloat2(&f2EnemyPosXZ);

    // 距離を測る
    DirectX::XMVECTOR vDistance = vecPlayerPos - vecEnemyPos;
    float fDistance = fabsf(DirectX::XMVectorGetX(vDistance));

    // 測定しうる最大の距離を求める
    float fMaxDistance = sqrtf(powf(inAttackHarfSize.x, 2) + powf(inAttackHarfSize.z, 2));

    // 距離を測る
    float fValue = fDistance / fMaxDistance;
    // 距離の基準点
    float fStandardValue = 1.0f / (int)eEnemyStatePattern::Max;

    // 距離に応じてステートパターンを設定する
    eEnemyStatePattern ePattern;
    if (fValue <= fStandardValue) ePattern = eEnemyStatePattern::Near;
    else if (fValue <= fStandardValue * 2) ePattern = eEnemyStatePattern::Middle;
    else ePattern = eEnemyStatePattern::Far;

    return ePattern;
}

int CEnemyBase::Inspecter(bool isEnd)
{
    // 親オブジェクトのヒエラルキーを描画し、子要素の数を受け取る
    int nChildCnt = CGameObject::Inspecter(false);

    // ステータスを表示
    if (ImGui::CollapsingHeader(std::string("[Status]").c_str()))
    {
        // 子要素の初期化
        ImGui::BeginChild(ImGui::GetID((void*)nChildCnt), ImVec2(ce_f2InspecterSize.x, ce_f2InspecterSize.y * 4));

        // 各種ステータスの表示
        ImGui::Text(std::string("HP:" + std::to_string(m_tEnemyStatus.m_nHP)).c_str());
        ImGui::Text(std::string("ATK:" + std::to_string(m_tEnemyStatus.m_nAttack)).c_str());
        ImGui::Text(std::string("SPD:" + std::to_string(m_tEnemyStatus.m_fSpeed)).c_str());

        // 子要素の終了
        ImGui::EndChild();
        // 子要素の数をインクリメント
        nChildCnt++;
    }

    // IMGUIウィンドウの終了
    ImGui::End();

    return nChildCnt;
}
