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

// 데이터 저장 공간을 리사이즈한다.
void GameEngineSerializer::BufferResize(size_t _Size)
{
	Datas.resize(_Size);
}

// 정수 자료형 저장 (바이너리)
void GameEngineSerializer::Write(const int& _Value)
{
	// 바이너리화한 _Value의 포인터와 저장 단위 int 전달
	Write(&_Value, sizeof(int)); // 저장 함수 실행
}

// 텍스트 자료형 저장 (텍스트)
void GameEngineSerializer::Write(const std::string_view& _Value)
{
	// 문자열의 크기 측정
	int Size = static_cast<int>(_Value.size());
	Write(&Size, sizeof(int));   // 사이즈를 먼저 저장
	Write(_Value.data(), Size);  // 저장 함수 실행
}

// 저장 함수
void GameEngineSerializer::Write(const void* _Ptr, size_t _Size)
{
	if (Datas.size() <= Offset + _Size)    // 저장공간이 작다면
	{
		Datas.resize(Datas.size() + 1024); // 크기 확장
	}

	//       여기에           여유 크기            저장할것 저장할 사이즈
	memcpy_s(&Datas[Offset], Datas.size() - Offset, _Ptr, _Size);

	Offset += _Size;   // 오프셋은 저장한 크기만큼 증가
}

// 정수 자료형 불러오기 (바이너리)
void GameEngineSerializer::Read(int& _Value)
{
	Read(&_Value, sizeof(int)); // 불러오기 함수 실행
}

// 텍스트 자료형 불러오기 (텍스트)
void GameEngineSerializer::Read(std::string& _Value)
{
	int Size = 0;
	Read(&Size, sizeof(int));   // 불러올 파일 크기를 저장할 변수 선언

	_Value.clear();             // 불러온 데이터를 받을 문자열 초기화
	_Value.resize(Size);        // 불러온 데이터를 받을 문자열 resize

	Read(_Value.data(), Size);  // 불러오기 함수 실행
}

// 불러오기 함수
void GameEngineSerializer::Read(void* _Ptr, size_t _Size)
{
	if (Datas.size() <= Offset + _Size)  // 지정된 사이즈 이상으로 불러오는 행위는 말이 안된다.
	{
		MsgAssert("데이터의 한도이상으로 읽으려고 했습니다.");
	}

	//    불러올것 불러올사이즈  여기에     이만큼
	memcpy_s(_Ptr, _Size, &Datas[Offset], _Size);

	Offset += _Size; // 오프셋은 저장한 크기만큼 증가
}