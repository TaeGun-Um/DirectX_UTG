#include "PrecompileHeader.h"
#include "GameEngineDirectBuffer.h"

GameEngineDirectBuffer::GameEngineDirectBuffer()
{
}

// ������ �Ҵ��� ������ �߻��� ���̱� ������, GameEngineDirectBuffer�� �Ҹ��ڿ� Buffer Relase �߰�
GameEngineDirectBuffer::~GameEngineDirectBuffer()
{
	if (nullptr != Buffer)
	{
		Buffer->Release();
		Buffer = nullptr;
	}
}

