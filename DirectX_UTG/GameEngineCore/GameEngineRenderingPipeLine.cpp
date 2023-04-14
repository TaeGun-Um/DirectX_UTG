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
	InputLayOutPtr = std::make_shared<GameEngineInputLayOut>(); // ��ǲ ���̾ƿ��� RenderingPipeLine�� ������ ���ÿ� ����
}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine()
{
}

// ��ǲ���̾ƿ� ����
// D3D11 ERROR: ID3D11DeviceContext::DrawIndexed: The Vertex Shader expects 
// application provided input data (which is to say data other than hardware 
// auto-generated values such as VertexID or InstanceID). Therefore an Input 
// Assembler object is expected, but none is bound. 
// [ EXECUTION ERROR #349: DEVICE_DRAW_INPUTLAYOUT_NOT_SET]
// ��ο� ���� ��Ÿ���� ������, �ؿ� �ܰ�� �Ѿ�� �� �����̶� �ּ��� ���� �ִ�. ������ �� ������
// ���̴��� �ø�ƽ�� ���� ��, ����ü ���ο� ���� ������ �����ȴٰ� ������, ����� �װ� �ƴϴ�.
// ���� (LayOut)�� ���� ���� ��������� �Ѵ�.
// �װ��� ���� GameEngineVertex���� �ǽ�

void GameEngineRenderingPipeLine::InputAssembler1()
{
	// ������ ��ǲ���̾ƿ� Setting
	if (nullptr == InputLayOutPtr)
	{
		MsgAssert("��ǲ ���̾ƿ��� �������� �ʾƼ� ��ǲ�����1 ������ ������ �� �����ϴ�.");
		return;
	}

	// GameEngineInputLayOut::Setting() �ǽ�, GetContext()->IASetInputLayout();
	InputLayOutPtr->Setting();

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
	// Topology ������ ���� IASetPrimitiveTopology() ȣ��
	// TOPOLOGY == D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST == �ﰢ������ �׷���. ���ʿ� �츮�� �ε����� �ﰢ������ �׸��� �����Ǿ� ����
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

// �����Ͷ������� �����ܰ��� ���� ��Ȯ�ϰ� �˰� �־�� �Ѵ�.
void GameEngineRenderingPipeLine::Rasterizer()
{
	if (nullptr == RasterizerPtr)
	{
		MsgAssert("�����Ͷ������� �������� �ʾƼ� ������ �Ұ����մϴ�.");
		return;
	}

	RasterizerPtr->SetFILL_MODE(FILL_MODE); // �����ܰ�� ���� State�� �ѱ��� �Ѵ�. �⺻���� �ָ���, ���� �츮�� �� �� ���� ����

	// GameEngineRasterizer::Setting() �ǽ�, GetContext()->RSSetState(CurState);
	RasterizerPtr->Setting();
}

void GameEngineRenderingPipeLine::PixelShader()
{
	if (nullptr == PixelShaderPtr)
	{
		MsgAssert("�ȼ� ���̴��� �������� �ʾƼ� �ȼ� ���̴� ������ ������ �� �����ϴ�.");
		return;
	}

	// GameEnginePixelShader::Setting() �ǽ�, GetContext()->PSSetShader();
	PixelShaderPtr->Setting();
}
void GameEngineRenderingPipeLine::OutputMerger()
{
	// �ƿ�ǲ������ ���⼭ �ǽ����� �ʰ�, GameEngineRenderTarget���� �ǽ���
}

void GameEngineRenderingPipeLine::SetVertexBuffer(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	VertexBufferPtr = GameEngineVertexBuffer::Find(UpperName);

	if (nullptr == VertexBufferPtr)
	{
		MsgAssert("�������� �ʴ� ���ؽ� ���۸� ����Ϸ��� �߽��ϴ�.");
	}

	// SetVertexBuffer�� SetVertexShader���� �̷� ������ ������ �Ǿ� �ִ� ����
	// ���� �ܰ迡���� �� �� � ���� ���� ��������� �𸥴�.
	// ����, ��ǲ ���̾ƿ��� GameEngineDevice::GetDevice()->CreateInputLayout() �Լ���
	// ���ؽ� ������ D3D11_INPUT_ELEMENT_DESC�� ���̴��� ���̳ʸ� �ڵ带 ������� ��ǲ ���̾ƿ��� ����� ���̴�.
	// ����, �� �� �ϳ��� �ܰ迡�� ��������� ��, InputLayOutPtr->ResCreate(VertexBufferPtr, VertexShaderPtr); �� ������ �� �ִ� �������̽��� ����
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

	// SetVertexBuffer�� SetVertexShader���� �̷� ������ ������ �Ǿ� �ִ� ���� (SetVertexBuffer���� ����)
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
	// �޽�    <= ������ ��� ���ϰ��ΰ�.
	//            �ȼ����������� ������ �����ϴ� Rasterizer
	//            w�����⸦ �ϰ� ����Ʈ�� ���ؼ�

	// ��Ƽ���� <= ������ ��� ���ð��ΰ�?
	//             �����Ͷ����� + �ȼ����̴� + ���ؽ� ���̴�

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

	// ���� ������ ��� �����ٸ� Draw �ǽ�
	// DrawIndexed()�� �ε������� ������ ���� ���� �׸��ڴٴ� ���̴�.
	// �츮�� �������̽��� ������ ���� ������ ���� ������ �̰����θ� Draw�� �ǽ��� ���̴�.
	// DrawIndexed()�� ���� ��ȣ���� �����ؼ� �׷��ִ� �����̶� �������̶� ����. Auto���� ��쿡�� 012345 ������ 6�� ������ 4���δ� ���׸� �̷� ����
	// ��� �������� ��Ծ �׳� �̰ɷ� �ǽ�
	UINT IndexCount = IndexBufferPtr->GetIndexCount();
	GameEngineDevice::GetContext()->DrawIndexed(IndexCount, 0, 0);
	// 1�� ���� : IndexCount
	// 2�� ���� : �ε��� �� ������ �׸��°�? 0
	// 3�� ���� : ���ؽ� �� ������ �׸��°�? 0

	// ��������� �ϸ� ������ ���.
	// 1. Rimitive Topology : InputAssmebler2 �ܰ迡�� IASetPrimitiveTopology() �ǽ�.
	// 2. ViewPort Setting  : ����Ʈ ������ ������. Camera�� Setting �߰� �� GameEngineDevice::GetContext()->RSSetViewport() �ǽ�.
	// 3. Vertex InputData  : ��ǲ���̾ƿ� ����. ���̴��� �ø�ƽ���� ���ؽ� ������ ��� �Ǿ��ִ����� ��ǲ�����͸� ���� �� ���� �ʿ�
	//                        GameEngineVertex�� �̵��Ͽ� ��ǲ ���̾ƿ� ���� �Լ� �����
}