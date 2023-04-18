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

void GameEngineConstantBuffer::ChangeData(const void* _Data, UINT _Size)
{
	// 머티리얼들은 상수버퍼나 이런걸 통일해 놓은 것이다.
	if (nullptr == _Data)
	{
		std::string Name = GetName().data();
		MsgAssert(Name + "에 nullptr인 데이터를 세팅하려고 했습니다.");
		return;
	}

	if (BufferInfo.ByteWidth != _Size)
	{
		std::string Name = GetName().data();
		MsgAssert(Name + "크기가 다른 데이터가 들어왔습니다.");
		return;
	}

	D3D11_MAPPED_SUBRESOURCE SettingResources = { 0, };

	// 그래픽카드야 너한테 보낼께있어 잠깐 멈춰봐 
	// D3D11_MAP_WRITE_DISCARD 최대한 빠르게 처리하는 
	GameEngineDevice::GetContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &SettingResources);

	if (SettingResources.pData == nullptr)
	{
		std::string Name = GetName().data();
		MsgAssert(Name + " 그래픽카드에게 메모리 접근을 허가받지 못했습니다.");
		return;
	}
	memcpy_s(SettingResources.pData, BufferInfo.ByteWidth, _Data, BufferInfo.ByteWidth);

	GameEngineDevice::GetContext()->Unmap(Buffer, 0);
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

void GameEngineConstantBuffer::VSSetting(UINT _Slot)
{
	GameEngineDevice::GetContext()->VSSetConstantBuffers(_Slot, 1, &Buffer);
}
void GameEngineConstantBuffer::PSSetting(UINT _Slot)
{
	GameEngineDevice::GetContext()->PSSetConstantBuffers(_Slot, 1, &Buffer);
}