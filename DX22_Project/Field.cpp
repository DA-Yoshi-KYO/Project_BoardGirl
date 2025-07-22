// インクルード部
#include "Field.h"
#include "ModelRenderer.h"
#include "Main.h"
#include "Player.h"

CField::~CField()
{
}

void CField::Init()
{
    // コンポーネントの追加
    AddComponent<CModelRenderer>()->Load(MODEL_PATH("Terrain.obj"),TERRAIN_SCALE, Model::Flip::ZFlip);
    m_pHeightMap = std::make_unique<Texture>();
    m_pHeightMap->Create(DXGI_FORMAT_R32_TYPELESS, 513, 513, L"Assets\\Texture\\Heightmap.png");
}

void CField::Update()
{
    CPlayer* player = GetScene()->GetGameObject<CPlayer>();
    float height = GetGroundHeight(player->AccessorPos());
    OutputDebugString(std::to_string(height).c_str());
    OutputDebugString("\n");
    CGameObject::Update();
}

float CField::GetGroundHeight(DirectX::XMFLOAT3 pos)
{
    DirectX::XMINT2 index;
    index.x = static_cast<int>(pos.x / TERRAIN_SIZE);
    index.y = static_cast<int>(pos.z / TERRAIN_SIZE);
    float* pData = m_pHeightMap->GetHeightMapData();

    DirectX::XMINT2 posIndex;
    posIndex.x = pos.x - index.x * TERRAIN_SIZE;
    posIndex.y = pos.z - index.y * TERRAIN_SIZE;
    int width = m_pHeightMap->GetWidth();
    int height = m_pHeightMap->GetHeight();
    float calc = static_cast<float>(width) / static_cast<float>(TERRAIN_SIZE) ;

    posIndex.y = TERRAIN_SIZE - posIndex.y; // Y軸反転
    posIndex.x *= calc;
    posIndex.y *= calc;

    return pData[posIndex.y * posIndex.x];
}
