#include "PrecompileHeader.h"
#include "PrecompileHeader.h"
#include "GameEngineSerializer.h"
#include "GameEngineDebug.h"

GameEngineSerializer::GameEngineSerializer()
{
}

GameEngineSerializer::~GameEngineSerializer()
{
}

// ������ ���� ������ ���������Ѵ�.
void GameEngineSerializer::BufferResize(size_t _Size)
{
	Datas.resize(_Size);
}

// ���� �ڷ��� ���� (���̳ʸ�)
void GameEngineSerializer::Write(const int& _Value)
{
	// ���̳ʸ�ȭ�� _Value�� �����Ϳ� ���� ���� int ����
	Write(&_Value, sizeof(int)); // ���� �Լ� ����
}

// �ؽ�Ʈ �ڷ��� ���� (�ؽ�Ʈ)
void GameEngineSerializer::Write(const std::string_view& _Value)
{
	// ���ڿ��� ũ�� ����
	int Size = static_cast<int>(_Value.size());
	Write(&Size, sizeof(int));   // ����� ���� ����
	Write(_Value.data(), Size);  // ���� �Լ� ����
}

// ���� �Լ�
void GameEngineSerializer::Write(const void* _Ptr, size_t _Size)
{
	if (Datas.size() <= Offset + _Size)    // ��������� �۴ٸ�
	{
		Datas.resize(Datas.size() + 1024); // ũ�� Ȯ��
	}

	//       ���⿡           ���� ũ��            �����Ұ� ������ ������
	memcpy_s(&Datas[Offset], Datas.size() - Offset, _Ptr, _Size);

	Offset += _Size;   // �������� ������ ũ�⸸ŭ ����
}

// ���� �ڷ��� �ҷ����� (���̳ʸ�)
void GameEngineSerializer::Read(int& _Value)
{
	Read(&_Value, sizeof(int)); // �ҷ����� �Լ� ����
}

// �ؽ�Ʈ �ڷ��� �ҷ����� (�ؽ�Ʈ)
void GameEngineSerializer::Read(std::string& _Value)
{
	int Size = 0;
	Read(&Size, sizeof(int));   // �ҷ��� ���� ũ�⸦ ������ ���� ����

	_Value.clear();             // �ҷ��� �����͸� ���� ���ڿ� �ʱ�ȭ
	_Value.resize(Size);        // �ҷ��� �����͸� ���� ���ڿ� resize

	Read(_Value.data(), Size);  // �ҷ����� �Լ� ����
}

// �ҷ����� �Լ�
void GameEngineSerializer::Read(void* _Ptr, size_t _Size)
{
	if (Datas.size() <= Offset + _Size)  // ������ ������ �̻����� �ҷ����� ������ ���� �ȵȴ�.
	{
		MsgAssert("�������� �ѵ��̻����� �������� �߽��ϴ�.");
	}

	//    �ҷ��ð� �ҷ��û�����  ���⿡     �̸�ŭ
	memcpy_s(_Ptr, _Size, &Datas[Offset], _Size);

	Offset += _Size; // �������� ������ ũ�⸸ŭ ����
}