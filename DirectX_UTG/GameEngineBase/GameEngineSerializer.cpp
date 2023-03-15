#include "GameEngineSerializer.h"

GameEngineSerializer::GameEngineSerializer()
{
}

GameEngineSerializer::~GameEngineSerializer()
{
}



void GameEngineSerializer::Write(const void* _Ptr, size_t _Size)
{
	//  1024             1023   + 4
	if (Datas.size() <= Offset + _Size)
	{
		Datas.resize(Datas.size() + 1024);
	}

	//       여기에 복사해라   복사할 위치의 여유크기는
	memcpy_s(&Datas[Offset], Datas.size() - Offset, _Ptr, _Size);

	Offset += _Size;
}

// 
// [][][][][][][][][][]

void GameEngineSerializer::Write(const int& _Value)
{
	Write(&_Value, sizeof(int));
}

void GameEngineSerializer::Write(const std::string_view& _Value)
{
	// const char*

	// Write(_Value, sizeof(std::string_view));
}