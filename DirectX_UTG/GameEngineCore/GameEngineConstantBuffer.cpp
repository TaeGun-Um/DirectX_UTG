#include "PrecompileHeader.h"
#include "GameEngineConstantBuffer.h"

std::map<int, std::map<std::string, std::shared_ptr<GameEngineConstantBuffer>>> GameEngineConstantBuffer::ConstantBufferRes;

GameEngineConstantBuffer::GameEngineConstantBuffer()
{
}

GameEngineConstantBuffer::~GameEngineConstantBuffer()
{
}

// ���ҽ� Ŭ����, Core_ReSource�� �����Ͽ� ������� ����
void GameEngineConstantBuffer::ResourcesClear()
{
	GameEngineResource<GameEngineConstantBuffer>::ResourcesClear();

	ConstantBufferRes.clear();
}

// �ε��� ���ۿ� ������ ���¸� ���� ResCreate
void GameEngineConstantBuffer::ResCreate(const D3D11_SHADER_BUFFER_DESC& _BufferDesc)
{
	BufferInfo.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // ��� ���ۿ� �÷���
	BufferInfo.ByteWidth = _BufferDesc.Size;           // ���� ������

	BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE; // CPU�÷��װ� Write�� ������ ���� ���ֱ� �����̴�. ��� ���ۿ��� WorldMatrix�� ���� ���شٴ� ��
	if (0 == BufferInfo.CPUAccessFlags)
	{
		BufferInfo.Usage = D3D11_USAGE_DEFAULT;
	}
	else 
	{
		BufferInfo.Usage = D3D11_USAGE_DYNAMIC;                                // ��� ���̳������� �����ȴ�.
	}

	// ��ӹ��� Buffer�� CreateBuffer()�� ���� ����
	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferInfo, nullptr, &Buffer))
	{
		MsgAssert("���ؽ� ���� ������ �����߽��ϴ�.");
	}
}