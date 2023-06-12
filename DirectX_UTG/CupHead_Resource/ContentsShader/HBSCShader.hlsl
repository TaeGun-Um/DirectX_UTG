
cbuffer TransformData : register(b0)
{
    float4 Scale;
    float4 Rotation;
    float4 Quaternion;
    float4 Position;

    float4 LocalScale;
    float4 LocalRotation;
    float4 LocalQuaternion;
    float4 LocalPosition;

    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldQuaternion;
    float4 WorldPosition;

    float4x4 ScaleMatrix;
    float4x4 RotationMatrix;
    float4x4 PositionMatrix;
    float4x4 LocalWorldMatrix;
    float4x4 WorldMatrix;
    float4x4 View;
    float4x4 Projection;
    float4x4 ViewPort;
    float4x4 WorldViewProjectionMatrix;
}

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

cbuffer AtlasData : register(b1)
{
    float2 FramePos;
    float2 FrameScale;
}

OutPut HBSC_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut)0;

    _Value.Pos.w = 1.0f;
    OutPutValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);

    OutPutValue.UV.x = (_Value.UV.x * FrameScale.x) + FramePos.x;
    OutPutValue.UV.y = (_Value.UV.y * FrameScale.y) + FramePos.y;

    return OutPutValue;
}

cbuffer HBSCOption : register(b0)
{
    float4 MulColor;
    float4 PlusColor;
    float4 HBSCColor;
}

Texture2D DiffuseTex : register(t0);
SamplerState CLAMPSAMPLER : register(s0);

struct OutColor
{
    float4 Color0 : SV_Target0;
    //float4 Color1 : SV_Target1;
    //float4 Color2 : SV_Target2;
    //float4 Color3 : SV_Target3;
};

float4 HBSC_PS(OutPut _Value) : SV_Target0
{
    float4 Color = DiffuseTex.Sample(CLAMPSAMPLER, _Value.UV.xy);
    //float4 outputColor = startColor;
    //float hue = 360 * HBSCColor.r;
    float saturation = HBSCColor.g * 2;
    float brightness = HBSCColor.b * 2 - 1;
    float contrast = HBSCColor.a * 2;

    Color += PlusColor;
    Color *= MulColor;

    //Color.rgb = applyHue(Color.rgb, hue);
    Color.rgb = (Color.rgb - 0.5f) * contrast + 0.5f;
    Color.rgb = Color.rgb + brightness;
	float3 intensity = dot(Color.rgb, float3(0.39, 0.59, 0.11));

    Color.rgb = lerp(intensity, Color.rgb, saturation);

    return Color;
}

//Shader "Unlit/HSBC Effect"
//{
//    Properties
//    {
//        _MainTex("Texture", 2D) = "white" {}
//        _Hue("Hue", Range(0, 1.0)) = 0
//        _Saturation("Saturation", Range(0, 1.0)) = 0.5
//        _Brightness("Brightness", Range(0, 1.0)) = 0.5
//        _Contrast("Contrast", Range(0, 1.0)) = 0.5
//    }
//        SubShader
//        {
//                        Tags {"Queue" = "Transparent" "IgnoreProjector" = "true" "RenderType" = "Transparent"}
//                Blend SrcAlpha OneMinusSrcAlpha Cull Off
//            Pass
//            {
//                CGPROGRAM
//                #pragma vertex vert
//                #pragma fragment frag
//
//                #include "UnityCG.cginc"
//
//
//                inline float3 applyHue(float3 aColor, float aHue)
//                {
//                    float angle = radians(aHue);
//                    float3 k = float3(0.57735, 0.57735, 0.57735);
//                    float cosAngle = cos(angle);
//
//                    return aColor * cosAngle + cross(k, aColor) * sin(angle) + k * dot(k, aColor) * (1 - cosAngle);
//                }
//
//                inline float4 applyHSBCEffect(float4 startColor, fixed4 hsbc)
//                {
//                    float hue = 360 * hsbc.r;
//                    float saturation = hsbc.g * 2;
//                    float brightness = hsbc.b * 2 - 1;
//                    float contrast = hsbc.a * 2;
//
//                    float4 outputColor = startColor;
//                    outputColor.rgb = applyHue(outputColor.rgb, hue);
//                    outputColor.rgb = (outputColor.rgb - 0.5f) * contrast + 0.5f;
//                    outputColor.rgb = outputColor.rgb + brightness;
//                    float3 intensity = dot(outputColor.rgb, float3(0.39, 0.59, 0.11));
//                    outputColor.rgb = lerp(intensity, outputColor.rgb, saturation);
//
//                    return outputColor;
//                }
//
//                struct appdata
//                {
//                    float4 vertex : POSITION;
//                    float2 uv : TEXCOORD0;
//                    fixed4 color : COLOR;
//                };
//
//                struct v2f
//                {
//                    float4 vertex : SV_POSITION;
//                    float2 uv : TEXCOORD0;
//                    fixed4 hsbc : COLOR;
//                };
//
//                sampler2D _MainTex;
//                float4 _MainTex_ST;
//                fixed _Hue, _Saturation, _Brightness, _Contrast;
//
//                v2f vert(appdata v)
//                {
//                    v2f o;
//                    o.vertex = UnityObjectToClipPos(v.vertex);
//                    o.uv = TRANSFORM_TEX(v.uv, _MainTex);
//                    o.hsbc = fixed4(_Hue, _Saturation, _Brightness, _Contrast);
//
//                    return o;
//                }
//
//                fixed4 frag(v2f i) : COLOR
//                {
//                    fixed4 startColor = tex2D(_MainTex, i.uv);
//                    float4 hsbcColor = applyHSBCEffect(startColor, i.hsbc);
//
//                    return hsbcColor * startColor.a;
//                }
//                ENDCG
//            }
//        }
//}