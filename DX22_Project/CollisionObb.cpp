// CCollisionObbコンポーネント実装 [obbColider.cpp]
#include "CollisionObb.h"
#include "gameObject.h"
#include "modelRenderer.h"
#include "Geometory.h"

bool CCollisionObb::IsHit(CCollisionBase* other)
{
	DirectX::XMFLOAT4X4* pWA = other->GetGameObject()->GetWorld();
	DirectX::XMFLOAT4X4* pWB = this->GetGameObject()->GetWorld();
	DirectX::XMMATRIX wa = DirectX::XMLoadFloat4x4(pWA);
	DirectX::XMMATRIX wb = DirectX::XMLoadFloat4x4(pWB);

	// ワールド空間上の境界ボックス中心座標を求める
	DirectX::XMFLOAT3 vPA, vPB;
	DirectX::XMFLOAT3 fCenterA, fCenterB;
    fCenterA = dynamic_cast<CCollisionObb*>(this)->AccessorCenter();
    fCenterB = dynamic_cast<CCollisionObb*>(other)->AccessorCenter();
	DirectX::XMStoreFloat3(&vPA, DirectX::XMVector3TransformCoord(
		DirectX::XMLoadFloat3(&fCenterA), wa));
	DirectX::XMStoreFloat3(&vPB, DirectX::XMVector3TransformCoord(
		DirectX::XMLoadFloat3(&fCenterB), wb));

	// 中心座標間のベクトルを求める
	DirectX::XMVECTOR vD =
		DirectX::XMVectorSet(vPA.x - vPB.x, vPA.y - vPB.y, vPA.z - vPB.z, 0.0f);

	// モデル座標軸を求める
	DirectX::XMVECTOR vN[6];
	vN[0] = DirectX::XMVectorSet(pWA->_11, pWA->_12, pWA->_13, 0.0f);
	vN[1] = DirectX::XMVectorSet(pWA->_21, pWA->_22, pWA->_23, 0.0f);
	vN[2] = DirectX::XMVectorSet(pWA->_31, pWA->_32, pWA->_33, 0.0f);
	vN[3] = DirectX::XMVectorSet(pWB->_11, pWB->_12, pWB->_13, 0.0f);
	vN[4] = DirectX::XMVectorSet(pWB->_21, pWB->_22, pWB->_23, 0.0f);
	vN[5] = DirectX::XMVectorSet(pWB->_31, pWB->_32, pWB->_33, 0.0f);

	// OBBの大きさ(半分)の長さを掛けたベクトルを求める
	DirectX::XMVECTOR vL[6];
	DirectX::XMFLOAT3 hsA = dynamic_cast<CCollisionObb*>(this)->AccessorHalfSize();
	DirectX::XMFLOAT3 hsB = dynamic_cast<CCollisionObb*>(this)->AccessorHalfSize();
	vL[0] = DirectX::XMVectorSet(pWA->_11 * hsA.x, pWA->_12 * hsA.x, pWA->_13 * hsA.x, 0.0f);
	vL[1] = DirectX::XMVectorSet(pWA->_21 * hsA.y, pWA->_22 * hsA.y, pWA->_23 * hsA.y, 0.0f);
	vL[2] = DirectX::XMVectorSet(pWA->_31 * hsA.z, pWA->_32 * hsA.z, pWA->_33 * hsA.z, 0.0f);
	vL[3] = DirectX::XMVectorSet(pWB->_11 * hsB.x, pWB->_12 * hsB.x, pWB->_13 * hsB.x, 0.0f);
	vL[4] = DirectX::XMVectorSet(pWB->_21 * hsB.y, pWB->_22 * hsB.y, pWB->_23 * hsB.y, 0.0f);
	vL[5] = DirectX::XMVectorSet(pWB->_31 * hsB.z, pWB->_32 * hsB.z, pWB->_33 * hsB.z, 0.0f);

	// 分離軸候補はモデル座標軸
	float fL, fD, f;
	DirectX::XMVECTOR vS;	// 分離軸候補
	for (int i = 0; i < 6; ++i) {
		vS = vN[i];
		// OBBの影(半分)の合計
		fL = 0.0f;
		for (int j = 0; j < 6; ++j) {
			DirectX::XMStoreFloat(&f, DirectX::XMVector3Dot(vS, vL[j]));
			fL += fabsf(f);
		}
		// 影と中心間の距離の比較
		DirectX::XMStoreFloat(&f, DirectX::XMVector3Dot(vS, vD));
		fD = fabsf(f);
		if (fL < fD) {
			return false;		// 当たっていない
		}
	}
	// 分離軸候補は2辺から生成
	for (int i = 0; i < 3; ++i) {
		for (int j = 3; j < 6; ++j) {
			// 分離軸候補を計算
			vS = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(vN[i], vN[j]));
			// OBBの影(半分)の合計
			fL = 0.0f;
			for (int k = 0; k < 6; ++k) {
				DirectX::XMStoreFloat(&f, DirectX::XMVector3Dot(vS, vL[k]));
				fL += fabsf(f);
			}
			// 影と中心間の距離の比較
			DirectX::XMStoreFloat(&f, DirectX::XMVector3Dot(vS, vD));
			fD = fabsf(f);
			if (fL < fD) {
				return false;	// 当たっていない
			}
		}
	}
	return true;				// 当たっている
}

void CCollisionObb::Update()
{
    m_Center = this->GetGameObject()->AccessorPos();
    m_HalfSize = this->GetGameObject()->AccessorSize();
    m_HalfSize /= 2.0f;
}

void CCollisionObb::Draw()
{
    DirectX::XMFLOAT3 vertex[8] = {
       {-m_HalfSize.x, +m_HalfSize.y, -m_HalfSize.z}, // 0
       {-m_HalfSize.x, -m_HalfSize.y, -m_HalfSize.z}, // 1
       {+m_HalfSize.x, +m_HalfSize.y, -m_HalfSize.z}, // 2
       {+m_HalfSize.x, -m_HalfSize.y, -m_HalfSize.z}, // 3
       {-m_HalfSize.x, +m_HalfSize.y, +m_HalfSize.z}, // 4
       {-m_HalfSize.x, -m_HalfSize.y, +m_HalfSize.z}, // 5
       {+m_HalfSize.x, +m_HalfSize.y, +m_HalfSize.z}, // 6
       {+m_HalfSize.x, -m_HalfSize.y, +m_HalfSize.z}, // 7
    };

    DirectX::XMFLOAT3 rotate = this->GetGameObject()->AccessorRotate();
    DirectX::XMMATRIX rot = DirectX::XMMatrixRotationRollPitchYaw(rotate.x, rotate.y, rotate.z);

    for (int i = 0; i < 8; ++i)
    {
        DirectX::XMVECTOR v = DirectX::XMLoadFloat3(&vertex[i]);    // ローカル空間
        v = DirectX::XMVector3Transform(v, rot);           // 回転適用
        v = DirectX::XMVectorAdd(v, DirectX::XMLoadFloat3(&m_Center)); // ワールド中心を加算
        DirectX::XMStoreFloat3(&vertex[i], v);             // 結果を保存
    }

    // 前面
    Geometory::AddLine(vertex[0], vertex[1], DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f));
    Geometory::AddLine(vertex[0], vertex[2], DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f));
    Geometory::AddLine(vertex[3], vertex[1], DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f));
    Geometory::AddLine(vertex[3], vertex[2], DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f));

    // 背面
    Geometory::AddLine(vertex[4], vertex[5], DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f));
    Geometory::AddLine(vertex[4], vertex[6], DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f));
    Geometory::AddLine(vertex[7], vertex[5], DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f));
    Geometory::AddLine(vertex[7], vertex[6], DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f));

    // 側面の接続
    Geometory::AddLine(vertex[0], vertex[4], DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f));
    Geometory::AddLine(vertex[1], vertex[5], DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f));
    Geometory::AddLine(vertex[2], vertex[6], DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f));
    Geometory::AddLine(vertex[3], vertex[7], DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f));

}
