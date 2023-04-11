#include "PrecompileHeader.h"
#include "GameEngineRenderingPipeLine.h"
#include <GameEngineCore/GameEngineDevice.h>
#include "GameEngineVertexBuffer.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine()
{
}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine()
{
}

void GameEngineRenderingPipeLine::InputAssembler1()
{
	if (nullptr == VertexBuffer)
	{
		MsgAssert("버텍스 버퍼가 존재하지 않아서 인풋어셈블러1 과정을 실행할 수 없습니다.");
		return;
	}

	// GameEngineVertexBuffer::Setting() 실시
	VertexBuffer->Setting();
}

// InputAssembler1() 이후 해당 단계로 넘어오면 다시 한 번 InputAssembler1() 단계로 넘어갈 수 있음. 나중에 알려줌.
void GameEngineRenderingPipeLine::VertexShader()
{
	// GameEngineDevice::GetContext()->VSSetShader
}

void GameEngineRenderingPipeLine::InputAssembler2()
{
	// GameEngineDevice::GetContext()->IASetIndexBuffer
}

void GameEngineRenderingPipeLine::Rasterizer()
{
	// GameEngineDevice::GetContext()->RSSetState
}

void GameEngineRenderingPipeLine::PixelShader()
{
	// GameEngineDevice::GetContext()->PSSetShader
}
void GameEngineRenderingPipeLine::OutputMerger()
{
	// GameEngineDevice::GetContext()->OMSetRenderTargets
}

void GameEngineRenderingPipeLine::SetVertexBuffer(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	VertexBuffer = GameEngineVertexBuffer::Find(UpperName);

	if (nullptr == VertexBuffer)
	{
		MsgAssert("존재하지 않는 버텍스 버퍼를 사용하려고 했습니다.");
	}
}
