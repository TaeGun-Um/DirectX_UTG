#include "PrecompileHeader.h"
#include "GameEngineRenderingPipeLine.h"
#include <GameEngineCore/GameEngineDevice.h>
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"

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
		MsgAssert("���ؽ� ���۰� �������� �ʾƼ� ��ǲ�����1 ������ ������ �� �����ϴ�.");
		return;
	}

	// ��ǲ���̾ƿ� ����
	// D3D11 ERROR: ID3D11DeviceContext::DrawIndexed: The Vertex Shader expects 
	// application provided input data (which is to say data other than hardware 
	// auto-generated values such as VertexID or InstanceID). Therefore an Input 
	// Assembler object is expected, but none is bound. 
	// [ EXECUTION ERROR #349: DEVICE_DRAW_INPUTLAYOUT_NOT_SET]

	// GameEngineVertexBuffer::Setting() �ǽ�, GetContext()->IASetVertexBuffers()
	VertexBufferPtr->Setting();
}

// InputAssembler1() ���� �ش� �ܰ�� �Ѿ���� �ٽ� �� �� InputAssembler1() �ܰ�� �Ѿ �� ����. ���߿� �˷���.
void GameEngineRenderingPipeLine::VertexShader()
{
	if (nullptr == VertexShaderPtr)
	{
		MsgAssert("���ؽ� ���̴��� �������� �ʾƼ� ���ؽ� ���̴� ������ ������ �� �����ϴ�.");
		return;
	}

	// GameEngineVertexShader::Setting() �ǽ�, GetContext()->VSSetShader()
	VertexShaderPtr->Setting();
}

// ������ ���� � ������ �׸� ������ �Ǵ�, InputAssembler1�� ����ϴ� Ŭ������ �������̽��� �ſ� ����ϴ�.
void GameEngineRenderingPipeLine::InputAssembler2()
{
	// Topology ������ ���� IASetPrimitiveTopology() ȣ��
	GameEngineDevice::GetContext()->IASetPrimitiveTopology(TOPOLOGY);

	if (nullptr == IndexBufferPtr)
	{
		MsgAssert("�ε��� ���۰� �������� �ʾƼ� ��ǲ �����2 ������ ������ �� �����ϴ�.");
		return;
	}

	// GameEngineIndexBuffer::Setting() �ǽ�, GetContext()->IASetIndexBuffer()
	IndexBufferPtr->Setting();
}

// ------------------------- ȭ�� ��¿� ���õ� �߿��� ����� �ƴ� -----------------------------
void GameEngineRenderingPipeLine::HullShader() {}       // ���ؽ��� �ɰ��� ���� ǥ�ø� �����
void GameEngineRenderingPipeLine::Tessellator() {}      // �ɰ���.
void GameEngineRenderingPipeLine::DomainShader() {}     // ����ó��
void GameEngineRenderingPipeLine::GeometryShaeder() {}  // ���ؽ� ����.
// ------------------------- ---------------------------------- -----------------------------

void GameEngineRenderingPipeLine::Rasterizer()
{
	if (nullptr == RasterizerPtr)
	{
		MsgAssert("�����Ͷ������� �������� �ʾƼ� ������ �Ұ����մϴ�.");
		return;
	}

	RasterizerPtr->SetFILL_MODE(FILL_MODE);
	RasterizerPtr->Setting();

	// GameEngineDevice::GetContext()->RSSetState
}

void GameEngineRenderingPipeLine::PixelShader()
{
	if (nullptr == PixelShaderPtr)
	{
		MsgAssert("�ȼ� ���̴��� �������� �ʾƼ� �ȼ� ���̴� ������ ������ �� �����ϴ�.");
		return;
	}

	PixelShaderPtr->Setting();

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
		MsgAssert("�������� �ʴ� ���ؽ� ���۸� ����Ϸ��� �߽��ϴ�.");
	}
}

void GameEngineRenderingPipeLine::SetIndexBuffer(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	IndexBufferPtr = GameEngineIndexBuffer::Find(UpperName);

	if (nullptr == IndexBufferPtr)
	{
		MsgAssert("�������� �ʴ� ���ؽ� ���۸� ����Ϸ��� �߽��ϴ�.");
	}
}

void GameEngineRenderingPipeLine::SetVertexShader(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	VertexShaderPtr = GameEngineVertexShader::Find(UpperName);

	if (nullptr == VertexShaderPtr)
	{
		MsgAssert("�������� �ʴ� ���ؽ� ���̴��� ����Ϸ��� �߽��ϴ�.");
	}
}

void GameEngineRenderingPipeLine::SetPixelShader(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	PixelShaderPtr = GameEnginePixelShader::Find(UpperName);

	if (nullptr == PixelShaderPtr)
	{
		MsgAssert("�������� �ʴ� �ȼ� ���̴��� ����Ϸ��� �߽��ϴ�.");
	}
}

void GameEngineRenderingPipeLine::SetRasterizer(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	RasterizerPtr = GameEngineRasterizer::Find(UpperName);

	if (nullptr == RasterizerPtr)
	{
		MsgAssert("�������� �ʴ� �����Ͷ������� ����Ϸ��� �߽��ϴ�.");
	}
}

// �Ž� + ���͸���, Renderer�� �ڽ��� ���� GameEngineRenderingPipeLine Pipe ������ ���� �ش� �Լ��� ȣ���� ����
// ������� �ϴ� �κ��� ������ ������������ �ѹٲ� ������ ���̴�.
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

	// �ε��� ���۰� ���õǾ������� �̰� ����ؼ� �׸��ǵ�.
	GameEngineDevice::GetContext()->DrawIndexed(IndexBufferPtr->GetIndexCount(), 0, 0);

	// �� �����ٸ�

	// �޽� <= ������ ��� ���ϰ��ΰ�.
	//         �ȼ����������� ������ �����ϴ� Rasterizer
	//         w�����⸦ �ϰ� ����Ʈ�� ���ؼ�

	// ��Ƽ���� <= ������ ��� ���ð��ΰ�?
	//             �����Ͷ����� + �ȼ����̴� + ���ؽ� ���̴�
}