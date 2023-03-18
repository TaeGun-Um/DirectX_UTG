#pragma once
#include <vector>
#include <string>
#include <string_view>

// 설명 :
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

	// Data 덩어리를 가져온다(불러오기용)
	inline void* GetData()
	{
		return &Datas[0];
	}

	// Data 덩어리를 가져온다(저장용)
	inline const void* GetConstData() const
	{
		return &Datas[0];
	}

	// 저장할 수 있는 Data 크기를 가져온다.
	inline size_t GetBufferSize() const
	{
		return Datas.size();
	}

	// 현재까지 저장한 Data 크기를 가져온다.
	inline size_t GetOffset() const
	{
		return Offset;
	}

	// 읽어온 데이터에 대해 저장 공간을 확보하기 위한 함수
	void BufferResize(size_t _Size);

	////////////////////// Write
	void Write(const int& _Value);              // 정수 자료형 저장 (바이너리)
	void Write(const std::string_view& _Value); // 텍스트 자료형 저장 (텍스트)
	void Write(const void* _Ptr, size_t _Size); // 저장 함수

	////////////////////// Read
	void Read(int& _Value);                     // 정수 자료형 불러오기 (바이너리)
	void Read(std::string& _Value);             // 텍스트 자료형 불러오기 (텍스트)
	void Read(void* _Ptr, size_t _Size);        // 불러오기 함수

protected:

private:
	std::vector<char> Datas = std::vector<char>(1024); // 데이터 덩어리를 저장할 벡터 (1024byte로 초기화 후 부족할 시 resize)
	size_t Offset = 0;                                 // 현재까지 저장된 데이터 크기
};

