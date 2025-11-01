cbuffer MatrixBuffer : register(b0)
{
    matrix g_mCurrentViewProjInv;
    matrix g_mPrevViewProj;
    float2 g_ScreenSize;
};

Texture2D g_ColorTex : register(t0);
Texture2D g_DepthTex : register(t1);
SamplerState samLinear : register(s0);

struct PS_IN
{
    float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD0;
};

float LinearizeDepth(float z)
{
    float nearZ = 0.1f;
    float farZ = 1000.0f;
    return (2.0f * nearZ) / (farZ + nearZ - z * (farZ - nearZ));
}

float4 main(PS_IN input) : SV_TARGET
{
    float depth = g_DepthTex.Sample(samLinear, input.UV).r;
    depth = LinearizeDepth(depth);

    float4 curPos = float4(input.UV * 2.0f - 1.0f, depth, 1.0f);
    float4 worldPos = mul(g_mCurrentViewProjInv, curPos);
    worldPos /= worldPos.w;

    float4 prevPos = mul(g_mPrevViewProj, worldPos);
    prevPos /= prevPos.w;

    float2 prevUV = prevPos.xy * 0.5f + 0.5f;
    float2 velocity = (input.UV - prevUV) * g_ScreenSize;

    // ブラー強度調整
    int blurSamples = 10;
    float2 blurStep = velocity / blurSamples;

    float4 color = float4(0, 0, 0, 0);
    for (int i = 0; i < blurSamples; ++i)
    {
        float2 sampleUV = input.UV - blurStep * i;
        color += g_ColorTex.Sample(samLinear, sampleUV);
    }

    color /= blurSamples;
    return color;
}
