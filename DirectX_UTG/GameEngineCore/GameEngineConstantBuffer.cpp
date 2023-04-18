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

// 세팅된 초기값에서 다른 값으로 변경할 경우 해당 함수 호출
// 물론 ResCreate에서 CreateBuffer를 통해 상수 버퍼가 만들어지지 않았다면 호출이 안되는 함수(Assert로 오류 출력)
void GameEngineConstantBuffer::ChangeData(const void* _Data, UINT _Size)
{
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

	// 상수 버퍼는 GPU의 VRAM 안에 존재한다.
	// 물론 그래픽카드는 쓰레드로 연산을 진행하고 있긴 하지만, GPU가 작업을 진행하는 도중, 특정 쓰레드 내의 연산 값을 변경하는 것은 위험한 행위임(오버헤드가 발생할 수 있다)
	// 그래도 일단 해당 쓰레드의 연산을 진행하려고 할 경우, 잠시 그래픽카드의 작업을 멈추는 함수가 Map

	// 1번 인자 : 이 버퍼를 고치겠다.
	// 2번 인자 : 필요없음
	// 3번 인자 : D3D11_MAP_WRITE_DISCARD == 최대한 빠르게 처리하라는 뜻
	// 4번 인자 : D3D11_MAPPED_SUBRESOURCE == 여기에 수정된 값이 채워진다.
	GameEngineDevice::GetContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &SettingResources);

	// 수정된 값이 널포인터인 경우
	if (SettingResources.pData == nullptr)
	{
		std::string Name = GetName().data();
		MsgAssert(Name + " 그래픽카드에게 메모리 접근을 허가받지 못했습니다.");
		return;
	}

	// 수정된 값(SettingResources.pData)을 BufferInfo.ByteWidth에 복사(memcpy_s)
	memcpy_s(SettingResources.pData, BufferInfo.ByteWidth, _Data, BufferInfo.ByteWidth);

	// Map의 사용과 값 복사가 끝났다며느 Umap으로 Map 사용이 끝났음을 선언
	// 1번 인자 : 해당 버퍼 다썼다
	// 2번 인자 : 필요없음
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
	}                                                                          // CreateBuffer 2번 인자가 널에 다이나믹이라면, 상수 버퍼가 시시각각으로 변경될 수 있다는 뜻

	// 상속받은 Buffer에 CreateBuffer()의 내용 저장
	// 어떤 형태로 값을 만들 지 정하지 않았다 (2번 인자가 널포인터로 전달됨), 이러면 나중에 형태를 바꿀 수 있음(ChangeData 가능(04.18))
	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferInfo, nullptr, &Buffer))
	{
		MsgAssert("버텍스 버퍼 생성에 실패했습니다.");
	}
}

// VSSetConstantBuffers 활용, 어떤 슬롯(BindPoint)인지 구분 필요
void GameEngineConstantBuffer::VSSetting(UINT _Slot)
{
	// 1번 인자 : 몇 번 슬롯? BindPoint
	// 2번 인자 : 몇 개냐, 여러 개 가능하지만 우선 1
	// 3번 인자 : ID3D11Buffer 전달
	GameEngineDevice::GetContext()->VSSetConstantBuffers(_Slot, 1, &Buffer);
}

// PSSetConstantBuffers 활용, 어떤 슬롯(BindPoint)인지 구분 필요
void GameEngineConstantBuffer::PSSetting(UINT _Slot)
{
	GameEngineDevice::GetContext()->PSSetConstantBuffers(_Slot, 1, &Buffer);
}