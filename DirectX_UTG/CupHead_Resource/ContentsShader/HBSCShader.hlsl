struct Input
{
    float4 Pos : POSITION;
    float4 UV : TEXCOORD;
};

struct OutPut
{
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};

OutPut HBSC_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
    OutPutValue.Pos = _Value.Pos;
    OutPutValue.UV = _Value.UV;
    
    return OutPutValue;
}

cbuffer FadeData : register(b1)
{
    float4 FadeValue;
}

Texture2D DiffuseTex : register(t0);
SamplerState WRAPSAMPLER : register(s0);

float4 HBSC_PS(OutPut _Value) : SV_Target0
{
    float4 Color = DiffuseTex.Sample(WRAPSAMPLER, _Value.UV.xy);
    float Value = FadeValue.x;
    Value = saturate(Value);
    Color.xyz *= Value;
    return Color;
}