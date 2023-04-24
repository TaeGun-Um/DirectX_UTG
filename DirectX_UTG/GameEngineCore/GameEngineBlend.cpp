#include "PrecompileHeader.h"
#include "GameEngineBlend.h"

GameEngineBlend::GameEngineBlend()
{
}

GameEngineBlend::~GameEngineBlend()
{
	if (nullptr != State)
	{
		State->Release();
		State = nullptr;
	}
}

void GameEngineBlend::Setting()
{
	if (nullptr == State)
	{
		MsgAssert("생성되지 않은 레스터라이저 스테이트 입니다.");
	}

	if (Desc.RenderTarget[0].SrcBlend == D3D11_BLEND_BLEND_FACTOR)
	{
		MsgAssert("아직 처리 하지 않는 블랜드 방식입니다 블랜드 필터 입력기능을 만들어 주세요.");
	}

	GameEngineDevice::GetContext()->OMSetBlendState(State, nullptr, Mask);
	// 1번 : 블랜드 데스크
	// 2번 : 필터를 임의로 설정할 수 있다. 0.5f, 0.5f, 0.5f를 넣고 싶다면 그렇게 할 수 있음, 하지만 지정 시엔 아직 처리할 수 없는 방식이라고 assert함 (나중에 합시다)
	// 3번 : 0xFFFFFFFF을 두 자리씩 나눠서, 1~2는 R, 3~4는 G, 5~6은 B, 7~8은 알파다. 특정 자릿수에 00을 넣으면 해당 색은 블랜드하지 마라는 뜻. 쓸일이 없어서 FFFFFFFF로 고정할 예정
}

void GameEngineBlend::ResCreate(const D3D11_BLEND_DESC& _Value)
{
	Desc = _Value;

	if (S_OK != GameEngineDevice::GetDevice()->CreateBlendState(&Desc, &State))
	{
		MsgAssert("블랜드 스테이트 생성에 실패했습니다.");
	}
}