#include "PrecompileHeader.h"
#include "GameEngineVertexBuffer.h"

GameEngineVertexBuffer::GameEngineVertexBuffer()
{
}

GameEngineVertexBuffer::~GameEngineVertexBuffer()
{
}

void GameEngineVertexBuffer::Create(const void* _Data, UINT _VertexSize, UINT _VertexCount)
{
	VertexSize = _VertexSize;
	VertexCount = _VertexCount;

	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = _Data;

	BufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER; // VRAM에 공간을 만들고 어떤 용도로 활용할 지 알려주는 것. 용도는 D3D11_BIND_VERTEX_BUFFER, 버텍스 버퍼용이다.
	BufferInfo.ByteWidth = VertexSize * VertexCount; // 공간의 크기가 얼마인지 지정, DirectX 관점에서 Vertex의 갯수는 파악할 필요가 없기 때문에 그냥 곱으로 할당

	//	D3D11_USAGE_DEFAULT
	//	값 : 0
	//	GPU에서 읽기 및 쓰기 액세스가 필요한 리소스입니다.이는 가장 일반적인 사용 선택일 수 있습니다.
	//  cpu에서 접근못함.

	//	D3D11_USAGE_IMMUTABLE
	//	값 : 1
	//	GPU에서만 읽을 수 있는 리소스입니다.GPU에서 쓸 수 없으며 CPU에서 전혀 액세스할 수 없습니다.만든 후에는 변경할 수 없으므로 이 유형의 리소스는 생성될 때 초기화해야 합니다.

	//	D3D11_USAGE_DYNAMIC
	//	값 : 2
	//	GPU(읽기 전용)와 CPU(쓰기 전용)에서 모두 액세스할 수 있는 리소스입니다.동적 리소스는 CPU에서 프레임당 한 번 이상 업데이트되는 리소스에 적합합니다.동적 리소스를 업데이트하려면 Map 메서드를 사용합니다.
	//	동적 리소스를 사용하는 방법에 대한 자세한 내용은 방법 : 동적 리소스 사용 방법을 참조하세요.

	//	D3D11_USAGE_STAGING
	//	값 : 3
	//	GPU에서 CPU로의 데이터 전송(복사)을 지원하는 리소스입니다. 비트코인


	//D3D11_CPU_ACCESS_WRITE
	//	값 : 0x10000L
	//	CPU가 내용을 변경할 수 있도록 리소스를 매핑할 수 있습니다.이 플래그로 생성된 리소스는 파이프라인의 출력으로 설정할 수 없으며 동적 또는 스테이징 사용으로 생성되어야 합니다(D3D11_USAGE 참조).

	//	D3D11_CPU_ACCESS_READ
	//	값 : 0x20000L
	//	CPU가 내용을 읽을 수 있도록 리소스를 매핑할 수 있습니다.이 플래그로 생성된 리소스는 파이프라인에 대한 입력 또는 출력으로 설정할 수 없으며 스테이징 용도로 생성해야 합니다(D3D11_USAGE 참조).

	BufferInfo.CPUAccessFlags = 0;                    // 0은 접근하지 않겠다는 뜻이다.

	// Usage == 메모리 어디에 둘 것인지 정하는 것
	if (0 == BufferInfo.CPUAccessFlags)
	{
		BufferInfo.Usage = D3D11_USAGE_DEFAULT;       // DEFAULT(값 0), CPU는 접근 못하며 GPU에게 읽기 및 쓰기가 가능하도록 함
	}
	else
	{
		BufferInfo.Usage = D3D11_USAGE_DYNAMIC;       // DYNAMIC(값 2), GPU와 CPU 모두에서 액세스할 수 있도록 함
	}

	// 이제 디바이스에 리소스를 만드는 작업을 요청
	// Data = 이 데이터대로 만들어 달라는 뜻으로 전달
	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferInfo, &Data, &Buffer))
	{
		MsgAssert("버텍스 버퍼 생성에 실패했습니다.");
	}

}