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

OutPut OldFilm_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
    OutPutValue.Pos = _Value.Pos;
    OutPutValue.UV = _Value.UV;
    
    OutPutValue.UV.x = OutPutValue.UV.x / 2.0f + 0.2f;
    OutPutValue.UV.y = OutPutValue.UV.y / 2.0f + 0.2f;
    
    return OutPutValue;
}

cbuffer OldFilmData : register(b1)
{
    float4 OldFilmValue;
}

Texture2D DiffuseTex : register(t0);
SamplerState WRAPSAMPLER : register(s0);

float4 OldFilm_PS(OutPut _Value) : SV_Target0
{
    float4 Color = DiffuseTex.Sample(WRAPSAMPLER, _Value.UV.xy);
       
    Color.x = (1.0f - Color.x) * OldFilmValue.x;

    Color.yz = Color.x;
    Color.w = 0.1f;

    return Color;
}