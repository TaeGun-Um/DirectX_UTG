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

// ���÷��� Create�� �����Ͷ������� ������ �����ϴ�.
// GetDevice->CreateSamplerState �ǽ�
void GameEngineSampler::ResCreate(const D3D11_SAMPLER_DESC& _Desc)
{
	Desc = _Desc;

	// 1�� ���� : D3D11_SAMPLER_DESC
	// 2�� ���� : ID3D11SamplerState
	if (S_OK != GameEngineDevice::GetDevice()->CreateSamplerState(&Desc, &State))
	{
		MsgAssert("���÷� ������ �����߽��ϴ�." + GetNameToString());
	}
}

// ���޹��� State�� ���� VSSetSamplers, PSSetSamplers �ǽ�
void GameEngineSampler::VSSetting(UINT _Slot)
{
	GameEngineDevice::GetContext()->VSSetSamplers(_Slot, 1, &State);
}

void GameEngineSampler::PSSetting(UINT _Slot)
{
	GameEngineDevice::GetContext()->PSSetSamplers(_Slot, 1, &State);
}
