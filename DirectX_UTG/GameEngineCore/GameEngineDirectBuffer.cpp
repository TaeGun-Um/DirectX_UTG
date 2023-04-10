#include "PrecompileHeader.h"
#include "GameEngineDirectBuffer.h"

GameEngineDirectBuffer::GameEngineDirectBuffer()
{
}

// 어차피 할당은 무조건 발생할 것이기 때문에, GameEngineDirectBuffer의 소멸자에 Buffer Relase 추가
GameEngineDirectBuffer::~GameEngineDirectBuffer()
{
	if (nullptr != Buffer)
	{
		Buffer->Release();
		Buffer = nullptr;
	}
}

