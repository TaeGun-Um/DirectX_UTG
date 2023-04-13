
// ���̴��� ���忡 ���Ե��� �ʴ´�.

// ���̴� ��Ģ
// � ������ �������� ���� ����ü�� �����.
struct Input 
{
    // �ø�ƽ == �� : ��
    // �� == �ڿ� �ִ°� � ������ ���������� ���� ����
    // �� == ����
	float4 Pos   : POSITION;
	float4 Color : COLOR;
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
    float4 Color : COLOR;
};

// �ܺο��� ���̴��� �������� ��, EntryPount�� ���ϴ� ��찡 �ִ�.
// �Լ��� �̸�, "Texture_VS"�� �Է��ϴ� ���� EntryPoint �̴�.
OutPut Texture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut)0;
	
    OutPutValue.Pos = _Value.Pos;
    OutPutValue.Color = _Value.Color;

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

struct OutColor
{
    float4 Color : SV_Target0; // 0��° ��ȭ���� ����϶�
};

// �ȼ����̴��� ��Ʈ������Ʈ�� PS, ���⿡ OutPut ���� ���´�.
// �� ���̴��� ���� ���� ������ ���´�. �� ���� �����Ͷ����� �ѱ������� Output �ǽ�
// �׷��� �����Ͷ��������� w�����⸦ �ϰ� PS�� OutPut���� ���� �ȴ�.
// �̶�, ����Ʈ ���� Red�̱� ������ ����, ����, ����, ���� �̷� ������ ���� ���̴�.
OutColor Texture_PS(OutPut _Value)
{
    OutColor ReturnColor = (OutColor) 0;
    ReturnColor.Color = _Value.Color;     // ������ ����Ʈ �÷��� Red�� �־����, �Ƹ� ������ �ٲ��� ������ Red ������ ��µ� ����
    return ReturnColor;
}
