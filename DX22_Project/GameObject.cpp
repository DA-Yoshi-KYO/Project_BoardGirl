// インクルード部
#include "GameObject.h"
#include "DebugSystem.h"

CGameObject::CGameObject()
    : m_bDestroy(false)
    , m_eTag(Tag::None)
    , m_tID{ "Object", 0 }
{
    // 汎用パラメータの初期化
    m_tParam.m_f3Pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_tParam.m_f3Size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
    m_tParam.m_f3Rotate = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_tParam.m_f4Color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    m_tParam.m_f2UVPos = DirectX::XMFLOAT2(0.0f, 0.0f);
    m_tParam.m_f2UVSize = DirectX::XMFLOAT2(1.0f, 1.0f);
    m_f3OldPos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

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
	for (auto comp : m_pComponent_List)
	{
        if (!comp) continue;
		comp->Update();
	}
}

void CGameObject::Draw()
{
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
    // 子要素の数
    int nChildCnt = 0;

    // IMGUIウィンドウの初期化
    ImGui::SetNextWindowPos(ImVec2(SCREEN_WIDTH - 300, 20));
    ImGui::SetNextWindowSize(ImVec2(280, SCREEN_HEIGHT - 140));
    ImGui::Begin("Inspecter");

    // 子要素の初期化
    ImGui::BeginChild(ImGui::GetID((void*)nChildCnt), ImVec2(250, 30), ImGuiWindowFlags_NoTitleBar);

    // インスペクターに名前を表示
    ObjectID id = m_tID;
    std::string name = id.m_sName;

    // 同オブジェクトが2つ以上ある場合、そのindexも名前に表示する
    if (id.m_nSameCount != 0) name += std::to_string(id.m_nSameCount);
    name = "Name:" + name;
    ImGui::Text(name.c_str());

    // 子要素の終了
    ImGui::EndChild();
    // 子要素の数をインクリメント
    nChildCnt++;

    // 子要素の初期化
    ImGui::BeginChild(ImGui::GetID((void*)nChildCnt), ImVec2(250, 270), ImGuiWindowFlags_NoTitleBar);

    if (CDebugSystem::GetInstance()->IsUpdate())
    {
        // アップデートが有効な時はパラメータの表示のみ行う
        // トランスフォームの表示
        if (ImGui::CollapsingHeader(std::string("[Transform]").c_str()))
        {
            // 座標の表示
            ImGui::Text(std::string("Position").c_str());
            DirectX::XMFLOAT3 pos = m_tParam.m_f3Pos;
            ImGui::Text(std::string("PosX:" + std::to_string(pos.x)).c_str());
            ImGui::Text(std::string("PosY:" + std::to_string(pos.y)).c_str());
            ImGui::Text(std::string("PosZ:" + std::to_string(pos.z)).c_str());
            ImGui::Text("\n");

            // サイズの表示
            ImGui::Text(std::string("Size").c_str());
            DirectX::XMFLOAT3 size = m_tParam.m_f3Size;
            ImGui::Text(std::string("SizeX:" + std::to_string(size.x)).c_str());
            ImGui::Text(std::string("SizeY:" + std::to_string(size.y)).c_str());
            ImGui::Text(std::string("SizeZ:" + std::to_string(size.z)).c_str());
            ImGui::Text("\n");

            // 回転の表示
            ImGui::Text(std::string("Rotation").c_str());
            DirectX::XMFLOAT3 rotate = m_tParam.m_f3Rotate;
            ImGui::Text(std::string("RotateX:" + std::to_string(rotate.x)).c_str());
            ImGui::Text(std::string("RotateY:" + std::to_string(rotate.y)).c_str());
            ImGui::Text(std::string("RotateZ:" + std::to_string(rotate.z)).c_str());

        }
    }
    else
    {
        // アップデートが無効な時はパラメータの変更も行う
        // トランスフォームの表示
        if (ImGui::CollapsingHeader(std::string("[Transform]").c_str()))
        {
            // 座標の表示と変更
            DirectX::XMFLOAT3* pos = &m_tParam.m_f3Pos;
            float inputPos[3] = { pos->x,pos->y,pos->z };
            ImGui::InputFloat3("Position", inputPos);
            ImGui::Text("\n");
            *pos = DirectX::XMFLOAT3(inputPos[0], inputPos[1], inputPos[2]);

            // サイズの表示と変更
            DirectX::XMFLOAT3* size = &m_tParam.m_f3Size;
            float inputSize[3] = { size->x,size->y,size->z };
            ImGui::InputFloat3("Size", inputSize);
            ImGui::Text("\n");
            *size = DirectX::XMFLOAT3(inputSize[0], inputSize[1], inputSize[2]);

            // 回転の表示と変更
            DirectX::XMFLOAT3* rotate = &m_tParam.m_f3Rotate;
            float inputRotate[3] = { rotate->x,rotate->y,rotate->z };
            ImGui::InputFloat3("Rotate", inputRotate);
            ImGui::Text("\n");
            *rotate = DirectX::XMFLOAT3(inputRotate[0], inputRotate[1], inputRotate[2]);

        }
    }

    // 子要素の終了
    ImGui::EndChild();
    // 子要素の数をインクリメント
    nChildCnt++;

    // IMGUIウィンドウの終了
    if (isEnd) ImGui::End();

    // 子要素の数を返し、派生先のインスペクターに使用する
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

DirectX::XMFLOAT4X4* CGameObject::GetWorld()
{
    DirectX::XMFLOAT4X4 world;

    DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixScaling(m_tParam.m_f3Size.x, m_tParam.m_f3Size.y, m_tParam.m_f3Size.z) *
        DirectX::XMMatrixRotationRollPitchYaw(m_tParam.m_f3Rotate.x, m_tParam.m_f3Rotate.y, m_tParam.m_f3Rotate.z) *
        DirectX::XMMatrixTranslation(m_tParam.m_f3Pos.x, m_tParam.m_f3Pos.y, m_tParam.m_f3Pos.z));

    return &world;
}
