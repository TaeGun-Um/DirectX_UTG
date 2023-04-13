#include "PrecompileHeader.h"
#include "GameEngineIndexBuffer.h"

GameEngineIndexBuffer::GameEngineIndexBuffer()
{
}

GameEngineIndexBuffer::~GameEngineIndexBuffer()
{
}

// 점을 그릴 순서를 Create하는 단계.
void GameEngineIndexBuffer::ResCreate(const void* _Data, UINT _VertexSize, UINT _VertexCount)
{
	// 공간의 크기
	IndexSize = _VertexSize;

	// IndexSize(VertexSize)에 따라 변화
	switch (IndexSize)
	{
	case 2:
		Format = DXGI_FORMAT_R16_UINT; // 2인 경우, R16 : 2byte 정수
		break;
	case 4:
		Format = DXGI_FORMAT_R32_UINT; // 4인 경우, R32 : 4byte 정수
		break;
	default:
		break;
	}

	// 정점의 갯수
	IndexCount = _VertexCount;

	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = _Data;

	BufferInfo.BindFlags = D3D11_BIND_INDEX_BUFFER; // VRAM에 공간을 만들고 어떤 용도로 활용할 지 알려주는 것. 용도는 D3D11_BIND_INDEX_BUFFER, 인덱스 버퍼용이다.
	BufferInfo.ByteWidth = IndexSize * IndexCount;  // 공간의 크기가 얼마인지 지정, DirectX 관점에서 Vertex의 갯수는 파악할 필요가 없기 때문에 그냥 곱으로 할당
	BufferInfo.CPUAccessFlags = 0;                  // 순서를 바꿀 필요가 없다. 0 전달

	if (0 == BufferInfo.CPUAccessFlags)
	{
		BufferInfo.Usage = D3D11_USAGE_DEFAULT;
	}
	else 
	{
		BufferInfo.Usage = D3D11_USAGE_DYNAMIC;
	}

	// 상속받은 Buffer에 CreateBuffer()의 내용 저장
	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferInfo, &Data, &Buffer))
	{
		MsgAssert("버텍스 버퍼 생성에 실패했습니다.");
	}

}

void GameEngineIndexBuffer::Setting()
{
	if (nullptr == Buffer)
	{
		MsgAssert("ID3DBuffer가 만들어지지 않은 버텍스 버퍼 입니다.");
		return;
	}

	GameEngineDevice::GetContext()->IASetIndexBuffer(Buffer, Format, Offset);
	// 1 : 여러 개를 세팅할 수 없는 구조이기 때문에 Buffer를 그냥 넣어준다.
	// 2 : 포멧을 넣어달라는 뜻, DXGI_FORMAT의 변수 Format 전달
	// 3 : Offset
}