#include "PrecompileHeader.h"
#include "GameEngineSampler.h"

GameEngineSampler::GameEngineSampler()
{
}

GameEngineSampler::~GameEngineSampler()
{
	if (nullptr != State)
	{
		State->Release();
		State = nullptr;
	}
}

// 샘플러의 Create는 래스터라이저와 굉장히 유사하다.
// GetDevice->CreateSamplerState 실시
void GameEngineSampler::ResCreate(const D3D11_SAMPLER_DESC& _Desc)
{
	Desc = _Desc;

	// 1번 인자 : D3D11_SAMPLER_DESC
	// 2번 인자 : ID3D11SamplerState
	if (S_OK != GameEngineDevice::GetDevice()->CreateSamplerState(&Desc, &State))
	{
		MsgAssert("샘플러 생성에 실패했습니다." + GetNameToString());
	}
}

// 전달받은 State를 통해 VSSetSamplers, PSSetSamplers 실시
void GameEngineSampler::VSSetting(UINT _Slot)
{
	GameEngineDevice::GetContext()->VSSetSamplers(_Slot, 1, &State);
}

void GameEngineSampler::PSSetting(UINT _Slot)
{
	GameEngineDevice::GetContext()->PSSetSamplers(_Slot, 1, &State);
}
