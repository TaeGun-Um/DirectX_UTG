#include "PrecompileHeader.h"
#include "GameEngineVertexBuffer.h"

GameEngineVertexBuffer::GameEngineVertexBuffer()
{
}

GameEngineVertexBuffer::~GameEngineVertexBuffer()
{
}

// ���ؽ� ����
void GameEngineVertexBuffer::Create(const void* _Data, UINT _VertexSize, UINT _VertexCount)
{
	VertexSize = _VertexSize;
	VertexCount = _VertexCount;

	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = _Data;

	BufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER; // VRAM�� ������ ����� � �뵵�� Ȱ���� �� �˷��ִ� ��. �뵵�� D3D11_BIND_VERTEX_BUFFER, ���ؽ� ���ۿ��̴�.
	BufferInfo.ByteWidth = VertexSize * VertexCount; // ������ ũ�Ⱑ ������ ����, DirectX �������� Vertex�� ������ �ľ��� �ʿ䰡 ���� ������ �׳� ������ �Ҵ�

	//	D3D11_USAGE_DEFAULT
	//	�� : 0
	//	GPU���� �б� �� ���� �׼����� �ʿ��� ���ҽ��Դϴ�.�̴� ���� �Ϲ����� ��� ������ �� �ֽ��ϴ�.
	//  cpu���� ���ٸ���.

	//	D3D11_USAGE_IMMUTABLE
	//	�� : 1
	//	GPU������ ���� �� �ִ� ���ҽ��Դϴ�.GPU���� �� �� ������ CPU���� ���� �׼����� �� �����ϴ�.���� �Ŀ��� ������ �� �����Ƿ� �� ������ ���ҽ��� ������ �� �ʱ�ȭ�ؾ� �մϴ�.

	//	D3D11_USAGE_DYNAMIC
	//	�� : 2
	//	GPU(�б� ����)�� CPU(���� ����)���� ��� �׼����� �� �ִ� ���ҽ��Դϴ�.���� ���ҽ��� CPU���� �����Ӵ� �� �� �̻� ������Ʈ�Ǵ� ���ҽ��� �����մϴ�.���� ���ҽ��� ������Ʈ�Ϸ��� Map �޼��带 ����մϴ�.
	//	���� ���ҽ��� ����ϴ� ����� ���� �ڼ��� ������ ��� : ���� ���ҽ� ��� ����� �����ϼ���.

	//	D3D11_USAGE_STAGING
	//	�� : 3
	//	GPU���� CPU���� ������ ����(����)�� �����ϴ� ���ҽ��Դϴ�. ��Ʈ����


	//D3D11_CPU_ACCESS_WRITE
	//	�� : 0x10000L
	//	CPU�� ������ ������ �� �ֵ��� ���ҽ��� ������ �� �ֽ��ϴ�.�� �÷��׷� ������ ���ҽ��� ������������ ������� ������ �� ������ ���� �Ǵ� ������¡ ������� �����Ǿ�� �մϴ�(D3D11_USAGE ����).

	//	D3D11_CPU_ACCESS_READ
	//	�� : 0x20000L
	//	CPU�� ������ ���� �� �ֵ��� ���ҽ��� ������ �� �ֽ��ϴ�.�� �÷��׷� ������ ���ҽ��� ���������ο� ���� �Է� �Ǵ� ������� ������ �� ������ ������¡ �뵵�� �����ؾ� �մϴ�(D3D11_USAGE ����).

	BufferInfo.CPUAccessFlags = 0;                    // 0�� �������� �ʰڴٴ� ���̴�.

	// Usage == �޸� ��� �� ������ ���ϴ� ��
	if (0 == BufferInfo.CPUAccessFlags)
	{
		BufferInfo.Usage = D3D11_USAGE_DEFAULT;       // DEFAULT(�� 0), CPU�� ���� ���ϸ� GPU���� �б� �� ���Ⱑ �����ϵ��� ��
	}
	else
	{
		BufferInfo.Usage = D3D11_USAGE_DYNAMIC;       // DYNAMIC(�� 2), GPU�� CPU ��ο��� �׼����� �� �ֵ��� ��
	}

	// ���� ����̽��� ���ҽ��� ����� �۾��� ��û
	// Data = �� �����ʹ�� ����� �޶�� ������ ����
	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferInfo, &Data, &Buffer))
	{
		MsgAssert("���ؽ� ���� ������ �����߽��ϴ�.");
	}

}

void GameEngineVertexBuffer::Setting()
{
	if (nullptr == Buffer)
	{
		MsgAssert("ID3DBuffer�� ��������� ���� ���ؽ� ���� �Դϴ�.");
		return;
	}

	GameEngineDevice::GetContext()->IASetVertexBuffers(0, 1, &Buffer, &VertexSize, &Offset);
	// 1�� ���� : UINT StartSlot, ���ؽ� ���۸� ������ ���� ���� �� �� �������� ���° ���� �����ؼ� �������� ����
	// 2�� ���� : UINT NumBuffers, ���ؽ� ���۸� � �����ߴ���
	// 3�� ���� : ID3D11Buffer* const* ppVertexBuffers, ������ �迭, �츮�� �迭 �Ѱ���
	// 4�� ���� : const UINT* pStrides, ���ؽ� 1���� ũ�Ⱑ ��?
	// 5�� ���� : const UINT* pOffsets ���ؽ� �� ��°���� �ұ�?
}