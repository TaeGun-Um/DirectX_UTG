#include "PrecompileHeader.h"
#include "GameEngineRenderingPipeLine.h"
#include <GameEngineCore/GameEngineDevice.h>
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineVertexShader.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine()
{
}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine()
{
}

void GameEngineRenderingPipeLine::InputAssembler1()
{
	if (nullptr == VertexBufferPtr)
	{
		MsgAssert("버텍스 버퍼가 존재하지 않아서 인풋어셈블러1 과정을 실행할 수 없습니다.");
		return;
	}

	// GameEngineVertexBuffer::Setting() 실시, GetContext()->IASetVertexBuffers()
	VertexBufferPtr->Setting();
}

// InputAssembler1() 이후 해당 단계로 넘어오면 다시 한 번 InputAssembler1() 단계로 넘어갈 수 있음. 나중에 알려줌.
void GameEngineRenderingPipeLine::VertexShader()
{
	if (nullptr == VertexShaderPtr)
	{
		MsgAssert("버텍스 쉐이더가 존재하지 않아서 버텍스 쉐이더 과정을 실행할 수 없습니다.");
		return;
	}

	// GameEngineVertexShader::Setting() 실시, GetContext()->VSSetShader()
	VertexShaderPtr->Setting();
}

// 정점에 따라 어떤 순서로 그릴 것인지 판단, InputAssembler1을 담당하는 클래스와 인터페이스가 매우 흡사하다.
void GameEngineRenderingPipeLine::InputAssembler2()
{
	if (nullptr == IndexBufferPtr)
	{
		MsgAssert("인덱스 버퍼가 존재하지 않아서 인풋 어셈블러2 과정을 실행할 수 없습니다.");
		return;
	}

	// GameEngineIndexBuffer::Setting() 실시, GetContext()->IASetIndexBuffer()
	IndexBufferPtr->Setting();
}

// ------------------------- 화면 출력에 관련된 중요한 기능은 아님 -----------------------------
void GameEngineRenderingPipeLine::HullShader() {}       // 버텍스를 쪼개기 위한 표시를 새기고
void GameEngineRenderingPipeLine::Tessellator() {}      // 쪼갠다.
void GameEngineRenderingPipeLine::DomainShader() {}     // 입자처리
void GameEngineRenderingPipeLine::GeometryShaeder() {}  // 버텍스 생성.
// ------------------------- ---------------------------------- -----------------------------

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
	VertexBufferPtr = GameEngineVertexBuffer::Find(UpperName);

	if (nullptr == VertexBufferPtr)
	{
		MsgAssert("존재하지 않는 버텍스 버퍼를 사용하려고 했습니다.");
	}
}

void GameEngineRenderingPipeLine::SetIndexBuffer(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	IndexBufferPtr = GameEngineIndexBuffer::Find(UpperName);

	if (nullptr == IndexBufferPtr)
	{
		MsgAssert("존재하지 않는 버텍스 버퍼를 사용하려고 했습니다.");
	}
}

void GameEngineRenderingPipeLine::SetVertexShader(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	VertexShaderPtr = GameEngineVertexShader::Find(UpperName);

	if (nullptr == VertexShaderPtr)
	{
		MsgAssert("존재하지 않는 버텍스 쉐이더를 사용하려고 했습니다.");
	}
}

// 매쉬 + 머터리얼, Renderer는 자신이 가진 GameEngineRenderingPipeLine Pipe 변수로 부터 해당 함수를 호출할 예정
// 랜더라고 하는 부분은 랜더링 파이프라인을 한바뀌 돌리는 것이다.
void GameEngineRenderingPipeLine::Render()
{
	InputAssembler1();
	VertexShader();
	InputAssembler2();
	HullShader();
	Tessellator();
	DomainShader();
	GeometryShaeder();
	Rasterizer();
	PixelShader();
	OutputMerger();

	// 메쉬 <= 외형이 어떻게 보일것인가.
	//         픽셀건져내기할 범위를 지정하는 Rasterizer
	//         w나누기를 하고 뷰포트를 곱해서

	// 머티리얼 <= 색깔이 어떻게 나올것인가?
	//             레스터라이저 + 픽셀쉐이더 + 버텍스 쉐이더
}