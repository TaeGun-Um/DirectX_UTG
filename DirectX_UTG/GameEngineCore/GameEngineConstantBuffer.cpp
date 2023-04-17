#include "PrecompileHeader.h"
#include "GameEngineConstantBuffer.h"

std::map<int, std::map<std::string, std::shared_ptr<GameEngineConstantBuffer>>> GameEngineConstantBuffer::ConstantBufferRes;

GameEngineConstantBuffer::GameEngineConstantBuffer()
{
}

GameEngineConstantBuffer::~GameEngineConstantBuffer()
{
}

// 리소스 클리어, Core_ReSource에 선언하여 명시적인 해제
void GameEngineConstantBuffer::ResourcesClear()
{
	GameEngineResource<GameEngineConstantBuffer>::ResourcesClear();

	ConstantBufferRes.clear();
}

// 인덱스 버퍼와 유사한 형태를 지닌 ResCreate
void GameEngineConstantBuffer::ResCreate(const D3D11_SHADER_BUFFER_DESC& _BufferDesc)
{
	BufferInfo.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // 상수 버퍼용 플래그
	BufferInfo.ByteWidth = _BufferDesc.Size;           // 버퍼 사이즈

	BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE; // CPU플래그가 Write인 이유는 값을 써주기 위함이다. 상수 버퍼에게 WorldMatrix가 뭔지 써준다는 뜻
	if (0 == BufferInfo.CPUAccessFlags)
	{
		BufferInfo.Usage = D3D11_USAGE_DEFAULT;
	}
	else 
	{
		BufferInfo.Usage = D3D11_USAGE_DYNAMIC;                                // 고로 다이나믹으로 결정된다.
	}

	// 상속받은 Buffer에 CreateBuffer()의 내용 저장
	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferInfo, nullptr, &Buffer))
	{
		MsgAssert("버텍스 버퍼 생성에 실패했습니다.");
	}
}