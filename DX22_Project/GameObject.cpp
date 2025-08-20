#include "GameObject.h"
#include "RendererComponent.h"
#include "DebugSystem.h"

CGameObject::CGameObject()
    : m_bDestroy(false)
    , m_eTag(Tag::None)
    , m_tID{"Object",0}
{
    m_tParam.m_f3Pos = { 0.0f, 0.0f, 0.0f };
    m_tParam.m_f3Size = { 1.0f, 1.0f, 1.0f };
    m_tParam.m_f3Rotate = { 0.0f, 0.0f, 0.0f };
    m_tParam.m_f4Color = { 1.0f, 1.0f, 1.0f, 1.0f };
    m_tParam.m_f2UVPos = { 0.0f, 0.0f };
    m_tParam.m_f2UVSize = { 1.0f, 1.0f };
    m_f3OldPos = { 0.0f, 0.0f, 0.0f };
    m_pSE.clear();
}

CGameObject::~CGameObject()
{
}

void CGameObject::Init()
{

}

void CGameObject::Uninit()
{
    // コンポーネントの解放
	for (auto comp : m_pComponent_List)
	{
        if (!comp) continue;
		comp->Uninit();
		delete comp;
	}
	m_pComponent_List.clear();
}

void CGameObject::Update()
{
    // コンポーネントの更新
	for (auto comp : m_pComponent_List)
	{
        if (!comp) continue;
		comp->Update();
	}
}

void CGameObject::Draw()
{
    // コンポーネントの描画
    for (auto comp : m_pComponent_List)
	{
        if (!comp) continue;
        // 描画用コンポーネントを使用する場合、汎用パラメータをコンポーネントに渡す
		if (dynamic_cast<CRendererComponent*>(comp))dynamic_cast<CRendererComponent*>(comp)->SetRendererParam(m_tParam);
        // 当たり判定描画はSceneで行う
        if (dynamic_cast<CCollisionBase*>(comp)) continue;
		comp->Draw();
	}	
}

void CGameObject::OnColliderHit(CCollisionBase* other, std::string thisTag)
{

}

void CGameObject::OnDestroy()
{

}

void CGameObject::Destroy()
{
	m_bDestroy = true;
}

bool CGameObject::IsDestroy()
{
	return m_bDestroy;
}

int CGameObject::Inspecter(bool isEnd)
{
    ImGui::SetNextWindowPos(ImVec2(SCREEN_WIDTH - 300, 20));
    ImGui::SetNextWindowSize(ImVec2(280, SCREEN_HEIGHT - 40));
    ImGui::Begin("Inspecter");

    int nChildCnt = 0;
    ObjectID id = m_tID;
    std::string name = id.m_sName;
    if (id.m_nSameCount != 0) name += std::to_string(id.m_nSameCount);
    name = "Name:" + name;
    ImGui::BeginChild(ImGui::GetID((void*)nChildCnt), ImVec2(250, 30), ImGuiWindowFlags_NoTitleBar);

    nChildCnt++;
    ImGui::Text(name.c_str());
    ImGui::EndChild();
    if (ImGui::CollapsingHeader(std::string("[Transform]").c_str()))
    {
        ImGui::BeginChild(ImGui::GetID((void*)nChildCnt), ImVec2(ce_f2InspecterSize.x, ce_f2InspecterSize.y * 9), ImGuiWindowFlags_NoTitleBar);

        ImGui::Text(std::string("Position").c_str());
        DirectX::XMFLOAT3 pos = m_tParam.m_f3Pos;
        ImGui::Text(std::string("PosX:" + std::to_string(pos.x)).c_str());
        ImGui::Text(std::string("PosY:" + std::to_string(pos.y)).c_str());
        ImGui::Text(std::string("PosZ:" + std::to_string(pos.z)).c_str());
        ImGui::Text("\n");

        ImGui::Text(std::string("Size").c_str());
        DirectX::XMFLOAT3 size = m_tParam.m_f3Size;
        ImGui::Text(std::string("SizeX:" + std::to_string(size.x)).c_str());
        ImGui::Text(std::string("SizeY:" + std::to_string(size.y)).c_str());
        ImGui::Text(std::string("SizeZ:" + std::to_string(size.z)).c_str());
        ImGui::Text("\n");

        ImGui::Text(std::string("Rotation").c_str());
        DirectX::XMFLOAT3 rotate = m_tParam.m_f3Rotate;
        ImGui::Text(std::string("RotateX:" + std::to_string(rotate.x)).c_str());
        ImGui::Text(std::string("RotateY:" + std::to_string(rotate.y)).c_str());
        ImGui::Text(std::string("RotateZ:" + std::to_string(rotate.z)).c_str());

        ImGui::EndChild();
    }

    if (isEnd) ImGui::End();

    return nChildCnt;
}

DirectX::XMFLOAT3 CGameObject::GetForward()
{
    DirectX::XMMATRIX mRotate = DirectX::XMMatrixRotationRollPitchYaw(m_tParam.m_f3Rotate.x, m_tParam.m_f3Rotate.y, m_tParam.m_f3Rotate.z);

    DirectX::XMFLOAT3 f3ForWard;
    DirectX::XMStoreFloat3(&f3ForWard, mRotate.r[2]);

    return f3ForWard;
}

DirectX::XMFLOAT3 CGameObject::GetRight()
{
    DirectX::XMMATRIX mRotate = DirectX::XMMatrixRotationRollPitchYaw(m_tParam.m_f3Rotate.x, m_tParam.m_f3Rotate.y, m_tParam.m_f3Rotate.z);

    DirectX::XMFLOAT3 f3Right;
    DirectX::XMStoreFloat3(&f3Right, mRotate.r[0]);

    return f3Right;
}

DirectX::XMFLOAT3 CGameObject::GetUp()
{
    DirectX::XMMATRIX mRotate = DirectX::XMMatrixRotationRollPitchYaw(m_tParam.m_f3Rotate.x, m_tParam.m_f3Rotate.y, m_tParam.m_f3Rotate.z);

    DirectX::XMFLOAT3 f3Up;
    DirectX::XMStoreFloat3(&f3Up, mRotate.r[1]);

    return f3Up;
}
