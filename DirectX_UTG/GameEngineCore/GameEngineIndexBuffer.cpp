#include "PrecompileHeader.h"
#include "GameEngineIndexBuffer.h"

GameEngineIndexBuffer::GameEngineIndexBuffer()
{
}

GameEngineIndexBuffer::~GameEngineIndexBuffer()
{
}

// ���� �׸� ������ Create�ϴ� �ܰ�.
void GameEngineIndexBuffer::ResCreate(const void* _Data, UINT _VertexSize, UINT _VertexCount)
{
	// ������ ũ��
	IndexSize = _VertexSize;

	// IndexSize(VertexSize)�� ���� ��ȭ
	switch (IndexSize)
	{
	case 2:
		Format = DXGI_FORMAT_R16_UINT; // 2�� ���, R16 : 2byte ����
		break;
	case 4:
		Format = DXGI_FORMAT_R32_UINT; // 4�� ���, R32 : 4byte ����
		break;
	default:
		break;
	}

	// ������ ����
	IndexCount = _VertexCount;

	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = _Data;

	BufferInfo.BindFlags = D3D11_BIND_INDEX_BUFFER; // VRAM�� ������ ����� � �뵵�� Ȱ���� �� �˷��ִ� ��. �뵵�� D3D11_BIND_INDEX_BUFFER, �ε��� ���ۿ��̴�.
	BufferInfo.ByteWidth = IndexSize * IndexCount;  // ������ ũ�Ⱑ ������ ����, DirectX �������� Vertex�� ������ �ľ��� �ʿ䰡 ���� ������ �׳� ������ �Ҵ�
	BufferInfo.CPUAccessFlags = 0;                  // ������ �ٲ� �ʿ䰡 ����. 0 ����

	if (0 == BufferInfo.CPUAccessFlags)
	{
		BufferInfo.Usage = D3D11_USAGE_DEFAULT;
	}
	else 
	{
		BufferInfo.Usage = D3D11_USAGE_DYNAMIC;
	}

	// ��ӹ��� Buffer�� CreateBuffer()�� ���� ����
	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferInfo, &Data, &Buffer))
	{
		MsgAssert("���ؽ� ���� ������ �����߽��ϴ�.");
	}

}

void GameEngineIndexBuffer::Setting()
{
	if (nullptr == Buffer)
	{
		MsgAssert("ID3DBuffer�� ��������� ���� ���ؽ� ���� �Դϴ�.");
		return;
	}

	GameEngineDevice::GetContext()->IASetIndexBuffer(Buffer, Format, Offset);
	// 1 : ���� ���� ������ �� ���� �����̱� ������ Buffer�� �׳� �־��ش�.
	// 2 : ������ �־�޶�� ��, DXGI_FORMAT�� ���� Format ����
	// 3 : Offset
}