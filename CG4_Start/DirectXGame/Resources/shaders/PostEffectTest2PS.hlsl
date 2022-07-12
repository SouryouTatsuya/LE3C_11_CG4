#include "PostEffectTest2.hlsli"

Texture2D<float4> tex0 : register(t0);  // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
Texture2D<float4> tex1 : register(t1);  // 1�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(VSOutput input) : SV_TARGET
{
	float u = 1.0f / 1280.0f;
	float v = 1.0f / 720.0f;
	float4 color = { 0,0,0,0 };
	int count = 10;
	for (int i = 0; i < count * 2 + 1; i++)
	{
		for (int j = 0; j < count * 2 + 1; j++)
		{
			color += tex0.Sample(smp,
				input.uv - float2(u * count, v * count) + float2(u * i, v * j));
		}
	}
	return float4(color.rgb / ((count * 2 + 1) * (count * 2 + 1)), 1);
}