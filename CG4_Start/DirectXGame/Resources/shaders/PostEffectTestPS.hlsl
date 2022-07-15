#include "PostEffectTest.hlsli"

Texture2D<float4> tex0 : register(t0);  // 0番スロットに設定されたテクスチャ
Texture2D<float4> tex1 : register(t1);  // 1番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
	float u = 1.0f / 1280.0f;
	float v = 1.0f / 720.0f;
	float4 color1 = { 0,0,0,0 };
	int count = 10;
	for (int i = 0; i < count * 2 + 1; i++)
	{
		for (int j = 0; j < count * 2 + 1; j++)
		{
			color1 += tex0.Sample(smp,
				input.uv - float2(u * count, v * count) + float2(u * i, v * j));
		}
	}

	float4 colortex1 = float4(color1.rgb / ((count * 2 + 1) * (count * 2 + 1)), 1);
	float4 colortex0 = float4(1.0 - tex0.Sample(smp, input.uv).rgb, 1);

	float4 color = colortex0;
	if (fmod(input.uv.y, 0.1f) < 0.05f)
	{
		color = colortex1;
	}

	return float4(color.rgb, 1);
}