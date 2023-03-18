#pragma once
#include <vector>
#include <string>
#include <string_view>

// ���� :
class GameEngineSerializer
{
public:
	// constrcuter destructer
	GameEngineSerializer();
	~GameEngineSerializer();

	// delete Function
	GameEngineSerializer(const GameEngineSerializer& _Other) = delete;
	GameEngineSerializer(GameEngineSerializer&& _Other) noexcept = delete;
	GameEngineSerializer& operator=(const GameEngineSerializer& _Other) = delete;
	GameEngineSerializer& operator=(GameEngineSerializer&& _Other) noexcept = delete;

	// Data ����� �����´�(�ҷ������)
	inline void* GetData()
	{
		return &Datas[0];
	}

	// Data ����� �����´�(�����)
	inline const void* GetConstData() const
	{
		return &Datas[0];
	}

	// ������ �� �ִ� Data ũ�⸦ �����´�.
	inline size_t GetBufferSize() const
	{
		return Datas.size();
	}

	// ������� ������ Data ũ�⸦ �����´�.
	inline size_t GetOffset() const
	{
		return Offset;
	}

	// �о�� �����Ϳ� ���� ���� ������ Ȯ���ϱ� ���� �Լ�
	void BufferResize(size_t _Size);

	////////////////////// Write
	void Write(const int& _Value);              // ���� �ڷ��� ���� (���̳ʸ�)
	void Write(const std::string_view& _Value); // �ؽ�Ʈ �ڷ��� ���� (�ؽ�Ʈ)
	void Write(const void* _Ptr, size_t _Size); // ���� �Լ�

	////////////////////// Read
	void Read(int& _Value);                     // ���� �ڷ��� �ҷ����� (���̳ʸ�)
	void Read(std::string& _Value);             // �ؽ�Ʈ �ڷ��� �ҷ����� (�ؽ�Ʈ)
	void Read(void* _Ptr, size_t _Size);        // �ҷ����� �Լ�

protected:

private:
	std::vector<char> Datas = std::vector<char>(1024); // ������ ����� ������ ���� (1024byte�� �ʱ�ȭ �� ������ �� resize)
	size_t Offset = 0;                                 // ������� ����� ������ ũ��
};

