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

// ���õ� �ʱⰪ���� �ٸ� ������ ������ ��� �ش� �Լ� ȣ��
// ���� ResCreate���� CreateBuffer�� ���� ��� ���۰� ��������� �ʾҴٸ� ȣ���� �ȵǴ� �Լ�(Assert�� ���� ���)
void GameEngineConstantBuffer::ChangeData(const void* _Data, UINT _Size)
{
	if (nullptr == _Data)
	{
		std::string Name = GetName().data();
		MsgAssert(Name + "�� nullptr�� �����͸� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	if (BufferInfo.ByteWidth != _Size)
	{
		std::string Name = GetName().data();
		MsgAssert(Name + "ũ�Ⱑ �ٸ� �����Ͱ� ���Խ��ϴ�.");
		return;
	}

	D3D11_MAPPED_SUBRESOURCE SettingResources = { 0, };

	// ��� ���۴� GPU�� VRAM �ȿ� �����Ѵ�.
	// ���� �׷���ī��� ������� ������ �����ϰ� �ֱ� ������, GPU�� �۾��� �����ϴ� ����, Ư�� ������ ���� ���� ���� �����ϴ� ���� ������ ������(������尡 �߻��� �� �ִ�)
	// �׷��� �ϴ� �ش� �������� ������ �����Ϸ��� �� ���, ��� �׷���ī���� �۾��� ���ߴ� �Լ��� Map

	// 1�� ���� : �� ���۸� ��ġ�ڴ�.
	// 2�� ���� : �ʿ����
	// 3�� ���� : D3D11_MAP_WRITE_DISCARD == �ִ��� ������ ó���϶�� ��
	// 4�� ���� : D3D11_MAPPED_SUBRESOURCE == ���⿡ ������ ���� ä������.
	GameEngineDevice::GetContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &SettingResources);

	// ������ ���� ���������� ���
	if (SettingResources.pData == nullptr)
	{
		std::string Name = GetName().data();
		MsgAssert(Name + " �׷���ī�忡�� �޸� ������ �㰡���� ���߽��ϴ�.");
		return;
	}

	// ������ ��(SettingResources.pData)�� BufferInfo.ByteWidth�� ����(memcpy_s)
	memcpy_s(SettingResources.pData, BufferInfo.ByteWidth, _Data, BufferInfo.ByteWidth);

	// Map�� ���� �� ���簡 �����ٸ�� Umap���� Map ����� �������� ����
	// 1�� ���� : �ش� ���� �ٽ��
	// 2�� ���� : �ʿ����
	GameEngineDevice::GetContext()->Unmap(Buffer, 0);
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
	}                                                                          // CreateBuffer 2�� ���ڰ� �ο� ���̳����̶��, ��� ���۰� �ýð������� ����� �� �ִٴ� ��

	// ��ӹ��� Buffer�� CreateBuffer()�� ���� ����
	// � ���·� ���� ���� �� ������ �ʾҴ� (2�� ���ڰ� �������ͷ� ���޵�), �̷��� ���߿� ���¸� �ٲ� �� ����(ChangeData ����(04.18))
	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferInfo, nullptr, &Buffer))
	{
		MsgAssert("���ؽ� ���� ������ �����߽��ϴ�.");
	}
}

// VSSetConstantBuffers Ȱ��, � ����(BindPoint)���� ���� �ʿ�
void GameEngineConstantBuffer::VSSetting(UINT _Slot)
{
	// 1�� ���� : �� �� ����? BindPoint
	// 2�� ���� : �� ����, ���� �� ���������� �켱 1
	// 3�� ���� : ID3D11Buffer ����
	GameEngineDevice::GetContext()->VSSetConstantBuffers(_Slot, 1, &Buffer);
}

// PSSetConstantBuffers Ȱ��, � ����(BindPoint)���� ���� �ʿ�
void GameEngineConstantBuffer::PSSetting(UINT _Slot)
{
	GameEngineDevice::GetContext()->PSSetConstantBuffers(_Slot, 1, &Buffer);
}