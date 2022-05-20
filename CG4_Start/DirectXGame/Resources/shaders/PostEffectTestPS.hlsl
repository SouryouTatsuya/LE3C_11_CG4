#include "PostEffectTest.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
	//float4 texcolor = tex.Sample(smp, input.uv);
	//return float4(texcolor.rgb, 1);
	float u = 1.0f / 1280.0f;
    float v = 1.0f / 720.0f;
	float4 color = { 0,0,0,0 };
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			color += tex.Sample(smp, 
				input.uv - float2(u * 5, v * 5) + float2(u * i, v * j));
		}
	}
	return float4(color.rgb / (11 * 11), 1);
}