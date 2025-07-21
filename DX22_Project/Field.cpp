// インクルード部
#include "Field.h"
#include "ModelRenderer.h"

CField::~CField()
{
}

void CField::Init()
{
    // コンポーネントの追加
    AddComponent<CModelRenderer>()->Load(MODEL_PATH("Terrain.obj"),0.1f, Model::Flip::ZFlip);
}
