#include "PrecompileHeader.h"
#include "GameEngineRenderingPipeLine.h"
#include <GameEngineCore/GameEngineDevice.h>
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineInputLayOut.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine()
{
	InputLayOutPtr = std::make_shared<GameEngineInputLayOut>(); // 인풋 레이아웃이 RenderingPipeLine의 생성과 동시에 생성
}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine()
{
}

// 인풋레이아웃 오류
// D3D11 ERROR: ID3D11DeviceContext::DrawIndexed: The Vertex Shader expects 
// application provided input data (which is to say data other than hardware 
// auto-generated values such as VertexID or InstanceID). Therefore an Input 
// Assembler object is expected, but none is bound. 
// [ EXECUTION ERROR #349: DEVICE_DRAW_INPUTLAYOUT_NOT_SET]
// 드로우 이후 나타나는 오류로, 밑에 단계로 넘어올 수 있음이라 주석건 것이 있다. 지금이 그 시점임
// 쉐이더의 시멘틱을 봤을 때, 구조체 내부에 따라 순서가 결정된다고 했지만, 사실은 그게 아니다.
// 뭔가 (LayOut)를 직접 만들어서 전달해줘야 한다.
// 그것은 이제 GameEngineVertex에서 실시

void GameEngineRenderingPipeLine::InputAssembler1()
{
	// 생성된 인풋레이아웃 Setting
	if (nullptr == InputLayOutPtr)
	{
		MsgAssert("인풋 레이아웃이 존재하지 않아서 인풋어셈블러1 과정을 실행할 수 없습니다.");
		return;
	}

	// GameEngineInputLayOut::Setting() 실시, GetContext()->IASetInputLayout();
	InputLayOutPtr->Setting();

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
	// Topology 셋팅을 위한 IASetPrimitiveTopology() 호출
	// TOPOLOGY == D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST == 삼각형으로 그려라. 애초에 우리의 인덱스도 삼각형으로 그리게 설정되어 있음
	GameEngineDevice::GetContext()->IASetPrimitiveTopology(TOPOLOGY);

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

// 레스터라이저는 고정단계라는 것을 정확하게 알고 있어야 한다.
void GameEngineRenderingPipeLine::Rasterizer()
{
	if (nullptr == RasterizerPtr)
	{
		MsgAssert("레스터라이저가 존재하지 않아서 세팅이 불가능합니다.");
		return;
	}

	RasterizerPtr->SetFILL_MODE(FILL_MODE); // 고정단계는 보통 State를 넘기라고 한다. 기본값은 솔리드, 물론 우리는 둘 다 만들 예정

	// GameEngineRasterizer::Setting() 실시, GetContext()->RSSetState(CurState);
	RasterizerPtr->Setting();
}

void GameEngineRenderingPipeLine::PixelShader()
{
	if (nullptr == PixelShaderPtr)
	{
		MsgAssert("픽셀 쉐이더가 존재하지 않아서 픽셀 쉐이더 과정을 실행할 수 없습니다.");
		return;
	}

	// GameEnginePixelShader::Setting() 실시, GetContext()->PSSetShader();
	PixelShaderPtr->Setting();
}
void GameEngineRenderingPipeLine::OutputMerger()
{
	// 아웃풋머저는 여기서 실시하지 않고, GameEngineRenderTarget에서 실시함
}

void GameEngineRenderingPipeLine::SetVertexBuffer(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	VertexBufferPtr = GameEngineVertexBuffer::Find(UpperName);

	if (nullptr == VertexBufferPtr)
	{
		MsgAssert("존재하지 않는 버텍스 버퍼를 사용하려고 했습니다.");
	}

	// SetVertexBuffer와 SetVertexShader에서 이런 식으로 구조가 되어 있는 이유
	// 세팅 단계에서는 둘 중 어떤 것이 먼저 만들어질지 모른다.
	// 또한, 인풋 레이아웃의 GameEngineDevice::GetDevice()->CreateInputLayout() 함수는
	// 버텍스 버퍼의 D3D11_INPUT_ELEMENT_DESC와 쉐이더의 바이너리 코드를 기반으로 인풋 레이아웃을 만드는 것이다.
	// 따라서, 둘 중 하나의 단계에서 만들어졌을 때, InputLayOutPtr->ResCreate(VertexBufferPtr, VertexShaderPtr); 로 진입할 수 있는 인터페이스로 구성
	if (nullptr == VertexShaderPtr)
	{
		return;
	}

	InputLayOutPtr->ResCreate(VertexBufferPtr, VertexShaderPtr);
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

	// SetVertexBuffer와 SetVertexShader에서 이런 식으로 구조가 되어 있는 이유 (SetVertexBuffer에서 설명)
	if (nullptr == VertexBufferPtr)
	{
		return;
	}

	InputLayOutPtr->ResCreate(VertexBufferPtr, VertexShaderPtr);
}

void GameEngineRenderingPipeLine::SetPixelShader(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	PixelShaderPtr = GameEnginePixelShader::Find(UpperName);

	if (nullptr == PixelShaderPtr)
	{
		MsgAssert("존재하지 않는 픽셀 쉐이더를 사용하려고 했습니다.");
	}
}

void GameEngineRenderingPipeLine::SetRasterizer(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	RasterizerPtr = GameEngineRasterizer::Find(UpperName);

	if (nullptr == RasterizerPtr)
	{
		MsgAssert("존재하지 않는 레스터라이저를 사용하려고 했습니다.");
	}
}

// 매쉬 + 머터리얼, Renderer는 자신이 가진 GameEngineRenderingPipeLine Pipe 변수로 부터 해당 함수를 호출할 예정
// 랜더라고 하는 부분은 랜더링 파이프라인을 한바뀌 돌리는 것이다.
void GameEngineRenderingPipeLine::Render()
{
	// 메쉬    <= 외형이 어떻게 보일것인가.
	//            픽셀건져내기할 범위를 지정하는 Rasterizer
	//            w나누기를 하고 뷰포트를 곱해서

	// 머티리얼 <= 색깔이 어떻게 나올것인가?
	//             레스터라이저 + 픽셀쉐이더 + 버텍스 쉐이더

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

	// 위의 세팅이 모두 끝났다면 Draw 실시
	// DrawIndexed()는 인덱스버퍼 세팅이 됐을 때만 그리겠다는 뜻이다.
	// 우리의 인터페이스는 세팅을 안할 생각이 없기 때문이 이것으로만 Draw를 실시할 것이다.
	// DrawIndexed()는 내가 번호까지 지정해서 그려주는 느낌이라 직관적이라서 좋음. Auto같은 경우에는 012345 햇으면 6개 고정에 4개로는 못그림 이런 느낌
	// 사실 나머지는 까먹어서 그냥 이걸로 실시
	UINT IndexCount = IndexBufferPtr->GetIndexCount();
	GameEngineDevice::GetContext()->DrawIndexed(IndexCount, 0, 0);
	// 1번 인자 : IndexCount
	// 2번 인자 : 인덱스 몇 번부터 그리는가? 0
	// 3번 인자 : 버텍스 몇 번부터 그리는가? 0

	// 여기까지만 하면 오류가 뜬다.
	// 1. Rimitive Topology : InputAssmebler2 단계에서 IASetPrimitiveTopology() 실시.
	// 2. ViewPort Setting  : 뷰포트 세팅을 안해줌. Camera에 Setting 추가 후 GameEngineDevice::GetContext()->RSSetViewport() 실시.
	// 3. Vertex InputData  : 인풋레이아웃 낫셋. 쉐이더의 시멘틱에게 버텍스 구성이 어떻게 되어있는지의 인풋데이터를 생성 후 전달 필요
	//                        GameEngineVertex로 이동하여 인풋 레이아웃 생성 함수 만들기
}