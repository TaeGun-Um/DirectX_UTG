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
		MsgAssert("���ؽ� ���۰� �������� �ʾƼ� ��ǲ�����1 ������ ������ �� �����ϴ�.");
		return;
	}

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

	// �޽� <= ������ ��� ���ϰ��ΰ�.
	//         �ȼ����������� ������ �����ϴ� Rasterizer
	//         w�����⸦ �ϰ� ����Ʈ�� ���ؼ�

	// ��Ƽ���� <= ������ ��� ���ð��ΰ�?
	//             �����Ͷ����� + �ȼ����̴� + ���ؽ� ���̴�
}