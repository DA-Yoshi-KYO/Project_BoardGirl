// インクルード部
#include "AttackObject.h"
#include "BillboardRenderer.h"
#include "CollisionObb.h"
#include "Oparation.h"

CAttackObject::CAttackObject()
    : CGameObject()
    , m_tAttackState{}, m_fTime(0.0f), m_nStep(0)
{
    m_tAttackState.m_nSpeed = 1;    // 速度の初期値は1とする
}

CAttackObject::~CAttackObject()
{

}

void CAttackObject::Init()
{
    // コンポーネントの追加
    AddComponent<CBillboardRenderer>();
}

void CAttackObject::Update()
{
    // 生成後の動きによって処理を変える
    switch (m_tAttackState.m_tDirectionState.m_eKind)
    {
    case DirectionKind::Stay:
        m_tAttackState.m_f3Center = m_tAttackState.m_tDirectionState.m_tStayPos.m_f3StayPos;    // 生成後の位置に留める
        break;
    case DirectionKind::Toward:
        m_tAttackState.m_f3Center += m_tAttackState.m_tDirectionState.m_tToward.m_f3Direction;  // 直線移動
        break;
    case DirectionKind::Helmite:
        // エルミート
        m_tAttackState.m_f3Center = HelmiteValue(m_fTime,
            m_tAttackState.m_tDirectionState.m_tHelmite.m_f3InitPos, m_tAttackState.m_tDirectionState.m_tHelmite.m_f3TargetPos,
            m_tAttackState.m_tDirectionState.m_tHelmite.m_fInitTangentVector, m_tAttackState.m_tDirectionState.m_tHelmite.m_fTargetTangentVector,
            m_tAttackState.m_fAttackDuration);
        break;
    case DirectionKind::FollowUp:
        if(m_tAttackState.m_tDirectionState.m_tFollowUp.pTarget)
            m_tAttackState.m_f3Center = m_tAttackState.m_tDirectionState.m_tFollowUp.pTarget->AccessorPos();    // GameObjectに追従
        break;
    default:
        break;
    }

    // 描画用パラメータの更新
    m_tParam.m_f3Pos = m_tAttackState.m_f3Center;
    m_tParam.m_f3Size = m_tAttackState.m_f3Size;

    // テクスチャアニメーション
    if (m_tAttackState.m_n2Split.x != 0 && m_tAttackState.m_n2Split.y != 0)
    {
        m_tParam.m_f2UVSize.x = 1.0f / (float)m_tAttackState.m_n2Split.x;
        m_tParam.m_f2UVSize.y = 1.0f / (float)m_tAttackState.m_n2Split.y;

        // 攻撃持続時間からアニメーションの進行度を求める
        float fStep = (m_tAttackState.m_fAttackDuration) / float(m_tAttackState.m_n2Split.x * m_tAttackState.m_n2Split.y);
        if (m_fTime >= (fStep * (m_nStep + 1)) / (float)m_tAttackState.m_nSpeed) m_nStep++;

        // 進行度からUV座標を求める
        m_tParam.m_f2UVPos.x = (1.0f / (float)m_tAttackState.m_n2Split.x) * (m_nStep % m_tAttackState.m_n2Split.x);
        m_tParam.m_f2UVPos.y = (1.0f / (float)m_tAttackState.m_n2Split.y) * (m_nStep / m_tAttackState.m_n2Split.x);
    }

    // コリジョン情報を更新する
    CCollisionObb* pCollision = GetComponent<CCollisionObb>();
    if (pCollision)
    {
        pCollision->AccessorCenter(m_tAttackState.m_f3Center);
        pCollision->AccessorHalfSize(m_tAttackState.m_f3Size * 0.5f);
    }

    // タイマーが攻撃持続時間を越えたら削除する
    if (m_fTime >= m_tAttackState.m_fAttackDuration)
        Destroy();

    // タイマーの加算
    m_fTime += fDeltaTime;

    CGameObject::Update();
}

void CAttackObject::Draw()
{
    // 描画に使用するテクスチャのキーをセットする
    if (m_tAttackState.m_sTexKey != "") GetComponent<CBillboardRenderer>()->SetKey(m_tAttackState.m_sTexKey);

    CGameObject::Draw();
}

void CAttackObject::OnColliderHit(CCollisionBase* other, std::string thisTag)
{

}
