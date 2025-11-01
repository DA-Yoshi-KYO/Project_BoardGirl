// インクルード部
#include "Field.h"
#include "Main.h"
#include "Oparation.h"

// 静的変数の初期化
std::vector<Model::Mesh> CField::m_Mesh = {};
HitResult CField::m_tResult = {};

CField::~CField()
{

}

void CField::Init()
{
    // コンポーネントの追加
    CModelRenderer* pRenderer = AddComponent<CModelRenderer>();
    //  描画に使用するモデルのキーをセット
    pRenderer->SetKey("Field");
    // 震度バッファを無効
    pRenderer->SetDepth(false);

    // メッシュ情報を取得
    m_Mesh = pRenderer->GetMesh();

    // 描画用パラメータの指定
    m_tParam.m_f3Pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
}

HitResult CField::RayIntersectsTriangle(const DirectX::XMFLOAT3& rayOrigin, const DirectX::XMFLOAT3& rayDir)
{
    // 計算用に使う変数を定義
    DirectX::XMVECTOR vRayOrigin = DirectX::XMLoadFloat3(&rayOrigin);   // レイの原点位置ベクトル
    DirectX::XMVECTOR vRayDir = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&rayDir));    // レイの方向ベクトル

    // リザルト情報の初期化
    m_tResult.m_bHit = false;
    m_tResult.m_f3Position = {};
    m_tResult.m_f3Normal = {};
    m_tResult.m_fDistance = FLT_MAX;

    // メッシュの数だけループを回す
    for (unsigned int meshNum = 0; meshNum < m_Mesh.size(); meshNum++)
    {
        Model::Vertices ver = m_Mesh[meshNum].vertices; // メッシュの頂点情報を取得
        Model::Indices ind = m_Mesh[meshNum].indices;   // メッシュのインデックス情報を取得

        // モデルの三角形の数だけループを回す
        for (unsigned int i = 0; i < ind.size(); i += 3)
        {
            // 三角形に使用する頂点を定義
            const DirectX::XMFLOAT3& f3Vertex0 = ver[ind[i]].pos;
            const DirectX::XMFLOAT3& f3Vertex1 = ver[ind[i + 1]].pos;
            const DirectX::XMFLOAT3& f3Vertex2 = ver[ind[i + 2]].pos;

            float fDis = 0.0f;  // 原点からヒット位置までの距離

            // レイと三角形の当たり判定を確認
            if (CheckHit(vRayOrigin, vRayDir, f3Vertex0, f3Vertex1, f3Vertex2, fDis))
            {
                // 当たっていたらそれまでの距離と比較し、最近距離を更新する
                if (fDis < m_tResult.m_fDistance)
                {
                    m_tResult.m_bHit = true;        // 衝突した
                    m_tResult.m_fDistance = fDis;   // 原点からヒット位置までの距離を更新

                    // 原点座標 + 方向ベクトル * 距離でヒット位置を求める
                    DirectX::XMVECTOR hitPos = vRayOrigin + vRayDir * fDis; 
                    DirectX::XMStoreFloat3(&m_tResult.m_f3Position, hitPos);

                    // 三角形の頂点から外積を使用し、法線ベクトルを計算する
                    DirectX::XMVECTOR normal = DirectX::XMVector3Normalize(
                        DirectX::XMVector3Cross(DirectX::XMLoadFloat3(&f3Vertex1) - DirectX::XMLoadFloat3(&f3Vertex0),
                            DirectX::XMLoadFloat3(&f3Vertex2) - DirectX::XMLoadFloat3(&f3Vertex0)));
                    DirectX::XMStoreFloat3(&m_tResult.m_f3Normal, normal);
                }
            }

        }
    }

    return m_tResult;
}

bool CField::CheckHit(const DirectX::XMVECTOR& inRayOrigin, const DirectX::XMVECTOR& rayDir, const DirectX::XMFLOAT3& inVertex0, const DirectX::XMFLOAT3& inVertex1, const DirectX::XMFLOAT3& inVertex2, float& outDis)
{
    // 各頂点を計算用にVECTORに変換する
    DirectX::XMVECTOR v0 = DirectX::XMLoadFloat3(&inVertex0);
    DirectX::XMVECTOR v1 = DirectX::XMLoadFloat3(&inVertex1);
    DirectX::XMVECTOR v2 = DirectX::XMLoadFloat3(&inVertex2);

    // 三角形の1つの頂点を基準にして辺ベクトルを作る
    DirectX::XMVECTOR v0v1 = v1 - v0;   // (辺v0→v1)
    DirectX::XMVECTOR v0v2 = v2 - v0;   // (辺v0→v2)
    // レイの方向ベクトルと辺ベクトルの外積から平面に対する補助ベクトル、Pベクトルを求める
    DirectX::XMVECTOR vP = DirectX::XMVector3Cross(rayDir, v0v2);

    // v0v2ベクトルとPベクトルの内積からX成分を取得し、並行チェックを行う
    // ここでのfDetはアルゴリズムMöller–Trumbore法にも使用する
    // 参考：https://pheema.hatenablog.jp/entry/ray-triangle-intersection
    float fDet = DirectX::XMVectorGetX(DirectX::XMVector3Dot(v0v1, vP));
    // fDetが0に限りなく近い場合、レイと三角形が交差しない並行であるとみなし非衝突を返す
    const float fEpsilon = 1e-6f;
    if (fabs(fDet) < fEpsilon) return false;

    // 交差判定を求めるための式
    // Origin + t ⋅ Dir = (1 − u − v)Ver0 + uVer1 + vVer2
    // を解く為に行列式Detの逆数を係数として使用する
    float fInvDet = 1.0f / fDet;

    // レイの方向にベクトルを伸ばし
    // 交差した点から求めたバリセン座標u,vが
    // 規定値以内ならば三角形の範囲内

    // レイの原点から頂点v0までのベクトル、Tベクトルを計算
    DirectX::XMVECTOR vT = inRayOrigin - v0;
    // 式に使用するバリセン座標uを求め、規定値内かチェックする
    float u = DirectX::XMVectorGetX(DirectX::XMVector3Dot(vT, vP)) * fInvDet;
    if (u < 0 || u > 1) return false;

    // Tベクトルと辺ベクトル01の内積、Qベクトルを求める
    DirectX::XMVECTOR vQ = DirectX::XMVector3Cross(vT, v0v1);
    // 式に使用するバリセン座標vを求め、規定値内かチェックする
    float v = DirectX::XMVectorGetX(DirectX::XMVector3Dot(rayDir, vQ)) * fInvDet;
    if (v < 0 || u + v > 1) return false;

    // uvが規定値以内ならば式を満たすtを計算する
    // tがレイの原点から衝突点までの距離となる
    float t = DirectX::XMVectorGetX(DirectX::XMVector3Dot(v0v2, vQ)) * fInvDet;
    outDis = t;

    return true;
}

