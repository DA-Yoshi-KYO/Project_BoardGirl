#include "Sprite.h"
#include "Camera.h"

Sprite::Data Sprite::m_data;
std::shared_ptr<VertexShader> Sprite::m_defVS;
std::shared_ptr<PixelShader> Sprite::m_defPS;

void Sprite::Init()
{
	const char* VS = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float2 uv : TEXCOORD0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};
cbuffer Matrix : register(b0) {
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};
cbuffer Param : register(b1) {
	float2 offset;
	float2 size;
	float2 uvPos;
	float2 uvScale;
	float4 color;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos.xy *= size;
	vout.pos.xy += offset;
	vout.pos = mul(vout.pos, world);
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);
	vout.uv = vin.uv;
	vout.uv *= uvScale;
	vout.uv += uvPos;
	vout.color = color;
	return vout;
})EOT";
	const char* PS = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};
Texture2D tex : register(t0);
SamplerState samp : register(s0);
float4 main(PS_IN pin) : SV_TARGET {
	return tex.Sample(samp, pin.uv) * pin.color;
})EOT";

	struct Vertex
	{
		float pos[3];
		float uv[2];
	} vtx[] = {
		{{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f}},
		{{ 0.5f, 0.5f, 0.0f}, {1.0f, 0.0f}},
		{{-0.5f,-0.5f, 0.0f}, {0.0f, 1.0f}},
		{{ 0.5f,-0.5f, 0.0f}, {1.0f, 1.0f}},
	};

	// メッシュ
	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxSize = sizeof(Vertex);
	desc.vtxCount = _countof(vtx);
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	m_data.mesh = std::make_shared<MeshBuffer>();
	m_data.mesh->Create(desc);

	// パラメーター
	m_data.param[0] = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	m_data.param[1] = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	m_data.param[2] = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	DirectX::XMStoreFloat4x4(&m_data.matrix[0], DirectX::XMMatrixIdentity());
	DirectX::XMStoreFloat4x4(&m_data.matrix[1], DirectX::XMMatrixIdentity());
	DirectX::XMStoreFloat4x4(&m_data.matrix[2], DirectX::XMMatrixIdentity());

	// シェーダー
	m_defVS = std::make_shared<VertexShader>();
	m_defVS->Compile(VS);
	m_data.vs = m_defVS.get();
	m_defPS = std::make_shared <PixelShader>();
	m_defPS->Compile(PS);
	m_data.ps = m_defPS.get();
}
void Sprite::Uninit()
{
}
void Sprite::Draw()
{
	m_data.vs->WriteBuffer(0, m_data.matrix);
	m_data.vs->WriteBuffer(1, m_data.param);
	m_data.vs->Bind();
	m_data.ps->SetTexture(0, m_data.texture);
	m_data.ps->Bind();
	m_data.mesh->Draw();
}

void Sprite::SetOffset(DirectX::XMFLOAT2 offset)
{
	m_data.param[0].x = offset.x;
	m_data.param[0].y = offset.y;
}
void Sprite::SetSize(DirectX::XMFLOAT2 size)
{
	m_data.param[0].z = size.x;
	m_data.param[0].w = size.y;
}

void Sprite::SetUVPos(DirectX::XMFLOAT2 pos)
{
	m_data.param[1].x = pos.x;
	m_data.param[1].y = pos.y;
}
void Sprite::SetUVScale(DirectX::XMFLOAT2 scale)
{
	m_data.param[1].z = scale.x;
	m_data.param[1].w = scale.y;
}
void Sprite::SetColor(DirectX::XMFLOAT4 color)
{
	m_data.param[2] = color;
}
void Sprite::SetTexture(Texture* tex)
{
	m_data.texture = tex;
}
void Sprite::SetWorld(DirectX::XMFLOAT4X4 world)
{
	m_data.matrix[0] = world;
}
void Sprite::SetView(DirectX::XMFLOAT4X4 view)
{
	m_data.matrix[1] = view;
}
void Sprite::SetProjection(DirectX::XMFLOAT4X4 proj)
{
	m_data.matrix[2] = proj;
}
void Sprite::SetVertexShader(Shader* vs)
{
	if (vs && typeid(VertexShader) == typeid(*vs))
		m_data.vs = vs;
	else
		m_data.vs = m_defVS.get();
}
void Sprite::SetPixelShader(Shader* ps)
{
	if (ps && typeid(PixelShader) == typeid(*ps))
		m_data.ps = ps;
	else
		m_data.ps = m_defPS.get();
}

void Sprite::SetParam(RendererParam param,SpriteKind inKind)
{
	// パラメーター設定
	// 座標
	m_data.param[0].x = 0.0f;
	m_data.param[0].y = 0.0f;
	// サイズ
	m_data.param[0].z = param.m_f3Size.x;
	m_data.param[0].w = param.m_f3Size.y;
	// uv座標
	m_data.param[1].x = param.m_f2UVPos.x;
	m_data.param[1].y = param.m_f2UVPos.y;
	// uvサイズ
	m_data.param[1].z = param.m_f2UVSize.x;
	m_data.param[1].w = param.m_f2UVSize.y;
	// 色
	m_data.param[2] = param.m_f4Color;

	CCamera* pCamera = CCamera::GetInstance().get();

	DirectX::XMMATRIX mWorld = DirectX::XMMatrixIdentity();
	DirectX::XMMATRIX mInvView = DirectX::XMMatrixIdentity();
	// ワールド行列
	switch (inKind)
	{
	case SpriteKind::Screen:
		mWorld =
			DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f) *
			DirectX::XMMatrixRotationRollPitchYawFromVector(DirectX::XMLoadFloat3(&param.m_f3Rotate)) *
			DirectX::XMMatrixTranslation(param.m_f3Pos.x + SCREEN_WIDTH * 0.5f, param.m_f3Pos.y + SCREEN_HEIGHT * 0.5f, param.m_f3Pos.z);
		mWorld = DirectX::XMMatrixTranspose(mWorld);

		DirectX::XMStoreFloat4x4(&m_data.matrix[0], mWorld);
		m_data.matrix[1] = Get2DView();
		m_data.matrix[2] = Get2DProj();
		break;
	case SpriteKind::World:
		mWorld =
			DirectX::XMMatrixRotationRollPitchYaw(param.m_f3Rotate.x, param.m_f3Rotate.y, param.m_f3Rotate.z) *
			DirectX::XMMatrixTranslation(param.m_f3Pos.x, param.m_f3Pos.y, param.m_f3Pos.z);
        mWorld = DirectX::XMMatrixTranspose(mWorld);
		DirectX::XMStoreFloat4x4(&m_data.matrix[0], mWorld);
		m_data.matrix[1] = pCamera->GetViewMatrix();
		m_data.matrix[2] = pCamera->GetProjectionMatrix();
		break;
	case SpriteKind::Billboard:
		m_data.matrix[0] = GetBillboardMatrix(param.m_f3Pos);
		m_data.matrix[1] = pCamera->GetViewMatrix();
		m_data.matrix[2] = pCamera->GetProjectionMatrix();
		break;
	default:
		break;
	}
}

DirectX::XMFLOAT4X4 Sprite::GetBillboardMatrix(DirectX::XMFLOAT3 pos)
{
	DirectX::XMMATRIX mCamInv = DirectX::XMMatrixIdentity();
	DirectX::XMFLOAT4X4 view = CCamera::GetInstance()->GetViewMatrix(false);
	mCamInv = DirectX::XMLoadFloat4x4(&view);
	mCamInv = DirectX::XMMatrixInverse(nullptr, mCamInv);
	DirectX::XMStoreFloat4x4(&view, mCamInv);
	view._41 = view._42 = view._43 = 0.0f;
	mCamInv = DirectX::XMLoadFloat4x4(&view);
	DirectX::XMMATRIX mWorld =
		mCamInv *
		DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);

	mWorld = DirectX::XMMatrixTranspose(mWorld);

	DirectX::XMFLOAT4X4 world;
	DirectX::XMStoreFloat4x4(&world, mWorld);

	return world;
}

DirectX::XMFLOAT4X4 Sprite::Get2DView()
{
	DirectX::XMFLOAT4X4 view;
	DirectX::XMMATRIX mView = DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(0.0f, 0.0f, -0.3f, 0.0f),
		DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	mView = DirectX::XMMatrixTranspose(mView);
	DirectX::XMStoreFloat4x4(&view, mView);
	return view;
}

DirectX::XMFLOAT4X4 Sprite::Get2DProj()
{
	DirectX::XMMATRIX mProj =
		DirectX::XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.1f, 10.0f);

	mProj = DirectX::XMMatrixTranspose(mProj);

	DirectX::XMFLOAT4X4 proj;
	DirectX::XMStoreFloat4x4(&proj, mProj);
	return proj;
}
