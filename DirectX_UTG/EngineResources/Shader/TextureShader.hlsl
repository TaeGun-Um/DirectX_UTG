
// ���̴��� ���忡 ���Ե��� �ʴ´�.

// ���̴� ��Ģ
// � ������ �������� ���� ����ü�� �����.
struct Input 
{
    // �ø�ƽ == �� : ��
    // �� == �ڿ� �ִ°� � ������ ���������� ���� ����
    // �� == ����
	float4 Pos   : POSITION0;
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