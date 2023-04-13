#include "PrecompileHeader.h"
#include "GameEngineRasterizer.h"

GameEngineRasterizer::GameEngineRasterizer()
{
}

GameEngineRasterizer::~GameEngineRasterizer()
{
	Release();
}

void GameEngineRasterizer::Release()
{
	if (nullptr != SolidState)
	{
		SolidState->Release();
		SolidState = nullptr;
	}

	if (nullptr != WireframeState)
	{
		WireframeState->Release();
		WireframeState = nullptr;
	}
}

void GameEngineRasterizer::Setting()
{
	if (nullptr == CurState)
	{
		MsgAssert("생성되지 않은 레스터라이저 스테이트 입니다.");
	}

	GameEngineDevice::GetContext()->RSSetState(CurState);
	// 현재 저장된 State로 레스터라이저 RSSetState() 실시
}

// GameEngineCore_Resources 의 Desc 확인
void GameEngineRasterizer::ResCreate(const D3D11_RASTERIZER_DESC& _Value)
{
	Release();     // 여기에 릴리즈가 있어서 의문일 수 있겠지만, ResCreate()가 재호출되면 싹 지우고 다시 만드는 구조로 해도 상관없는 것이
	               // 그렇게 해도 빠르기 때문에 괜찮은 것이다. 그리고 게임 도중에 호출될 인터페이스가 아니기 때문에 가능한 일.
	               // 여기는 엔진이라 괜찮다.

	Desc = _Value;

	// 우리의 엔진 구조는 FILLMode를 둘 다 만들기 때문에, 여기서 두 번 CreateRasterizerState()를 실시한다.
	// CreateRasterizerState(와이어프레임)
	Desc.FillMode = D3D11_FILL_WIREFRAME; 
	if (S_OK != GameEngineDevice::GetDevice()->CreateRasterizerState(&Desc, &WireframeState))
	{
		MsgAssert("와이어 프레임 레스터라이저 스테이트 생성에 실패했습니다.");
	}

	// CreateRasterizerState(솔리드)
	Desc.FillMode = D3D11_FILL_SOLID;
	if (S_OK != GameEngineDevice::GetDevice()->CreateRasterizerState(&Desc, &SolidState))
	{
		MsgAssert("솔리드 레스터라이저 스테이트 생성에 실패했습니다.");
	}

	// 두 개 만들었지만, 기본은 솔리드로 설정
	SetFILL_MODE(D3D11_FILL_SOLID);
}
