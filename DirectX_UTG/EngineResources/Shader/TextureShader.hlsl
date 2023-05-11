
// ��� ���̴����� �������������� �Ϸ���, �ܺο��� WorldMatrix�� �˷���� �Ѵ�.
// �̰� �����ϰ� ���ִ� ���� �ٷ� �������

// �ܽ��Ͻ� ����, �츮�� ���� ���
// �ؽ���, �׸� �־�� ������
// ����Ʈ��巹������, ����
// ��Ʈ���ĵ����, ����

// �������
// cbuffer TransformData : register(b0)
// {
//     int intValue0;
// }
// ���̷�Ʈ�� 0������ 16������ �ִ�.
// b0 ~ b16���� ����
// �̷� ������ ���� ���� ���ڴٰ� ����ϴ� ���̴�.
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

// ���̴��� ���忡 ���Ե��� �ʴ´�.

// ���̴� ��Ģ
// � ������ �������� ���� ����ü�� �����.
struct Input
{
    // �ø�ƽ == �� : ��
    // �� == �ڿ� �ִ°� � ������ ���������� ���� ����
    // �� == ����
    float4 Pos : POSITION;
    float4 UV : TEXCOORD;
};

// void GameEngineVertexBuffer::Setting() ����
// GameEngineDevice::GetContext()->IASetVertexBuffers(0, 1, &Buffer, &VertexSize, &Offset); �� ����
// ���� ũ��, �� ����, �迭 ������ ���� ������ void �����͸� ���� ����� ���޹ް� �ȴ�.
// �� ������ ������� Position�̳� Color�� ���� ������ ���� ������ ���ΰ� ��� �̷������ϴ��� �𸣴� ����
// ���� � ������ �ش� ������ ����� �ؼ��� ������ ����ü���� �ø�ƽ���� �ؼ��ϰ� ��

struct OutPut
{
    // SV_Position == �����Ͷ��������� w�� ���� �� ����Ʈ�� ���ϰ� �ȼ� ������ �� �� position ������ ������ ���� ���̶�� �˷��ִ� ��(���� ������ �ȼ� ������ ���� �𸣴� �˷��ִ� ��)
    // COLOR == ���ʷ� COLOR�� �Է��ϸ� COLOR[n]�� �����ȴ�. �̰� ����ü ������ COLOR�� COLOR0, COLOR1, COLOR2, ... �� ���� �� ����� �� �ֱ� ����
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};

cbuffer AtlasData : register(b1)
{
    // 0.0 0.5
    float2 FramePos;
    // 0.5 0.5 
    float2 FrameScale;
    // float4 AtlasUV;
}

// �ܺο��� ���̴��� �������� ��, EntryPount�� ���ϴ� ��찡 �ִ�.
// �Լ��� �̸�, "Texture_VS"�� �Է��ϴ� ���� EntryPoint �̴�.

// ������۸� �߰��ϸ� b0 -> b1 -> b2 �̷� ��
// �⺻���� *(���ϱ�)�� ���� �ڷ����� �����ϰ� �صױ� ������
// �ٸ� ������ �ڷ����� ���Ϸ��� mul(��)�� �̿��ؾ� �Ѵ�.

// Mesh�� ������ ũ�� ��ŭ���� �ȼ��� ������.
// ���� �ȼ��� ���̴����� �����Ͽ� ���� �κ��� �����ش޶�� ��
// ���� �̹������� Mesh�� Ŭ ���, �̹����� �� ��ŭ Ȯ��Ǵµ�, ��� �ȼ��� ä�����
// Mesh�� �̹����� ������ 0~1�� �����(������)
// �̰��� UV ��ǥ���� �Ѵ�. �̰� ���ִ°� ���÷�(Sampler)�Դϴ�.
OutPut Texture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
	
    _Value.Pos.w = 1.0f;
    OutPutValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    // OutPutValue.Pos = _Value.Pos;
    // OutPutValue.UV = _Value.UV;

    // OutPutValue.Pos *= �������������;
    
    OutPutValue.UV.x = (_Value.UV.x * FrameScale.x) + FramePos.x;
    OutPutValue.UV.y = (_Value.UV.y * FrameScale.y) + FramePos.y;
    
    return OutPutValue;
}

// �ȼ����̴� ���Ĵ� �ƿ�ǲ���� �ܰ迡 ����. �ƿ�ǲ������ ��ȭ���� ���(RenderTarget) ���⿡ �׸���� �ϴ� �ܰ�
// ���⼭ ���ÿ� 5�� �׸��� ���� ���� �� �� �ִ�.
// �Ʒ����� 
// float4 Color : SV_Target0;
// float4 Color : SV_Target1;
// float4 Color : SV_Target2;
// float4 Color : SV_Target3;
// float4 Color : SV_Target4;
// �̷� ������ �ϸ� ���ÿ� RenderTarget 5���� �׸� �� ����. �ٵ� �׷� �ʿ� ������ SV_Target0 �ϳ��� �����.

//struct OutColor
//{
//    float4 Color : SV_Target0; // 0��° ��ȭ���� ����϶�
//};

// �ȼ����̴��� ��Ʈ������Ʈ�� PS, ���⿡ OutPut ���� ���´�.
// �� ���̴��� ���� ���� ������ ���´�. �� ���� �����Ͷ����� �ѱ������� Output �ǽ�
// �׷��� �����Ͷ��������� w�����⸦ �ϰ� PS�� OutPut���� ���� �ȴ�.
// �̶�, ����Ʈ ���� Red�̱� ������ ����, ����, ����, ���� �̷� ������ ���� ���̴�.
//OutColor Texture_PS(OutPut _Value)
//{
//    OutColor ReturnColor = (OutColor) 0;
//    ReturnColor.Color = _Value.Color;     // ������ ����Ʈ �÷��� Red�� �־����, �Ƹ� ������ �ٲ��� ������ Red ������ ��µ� ����
    
//    return ReturnColor;
//}

// �ƿ�ǲ������ 0�� Ÿ�ٿ� ��µ� float4�� ����� ����϶�� ��

cbuffer OutPixelColor : register(b0)
{
    float4 OutColor;
}

Texture2D DiffuseTex : register(t0);
SamplerState CLAMPSAMPLER : register(s0); // �ɼ��� �̷���, ������Ʈ�� ������ �̷� ������ ������ ������ �� �ִ� ���� �ٷ� ���÷��̴�.

float4 Texture_PS(OutPut _Value) : SV_Target0
{
    // ������ ǥ����
    // float4�� float2�� �� �� ���� : float4.xy == float2
    float4 Color = DiffuseTex.Sample(CLAMPSAMPLER, _Value.UV.xy);
    
    //if (Color.a == 0)
    //{
    //    clip(-1);
    //}
    
    return Color;
}