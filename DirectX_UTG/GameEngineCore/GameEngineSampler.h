#pragma once
#include "GameEngineResource.h"

// 설명 : 쉐이더의 샘플러를 위한 클래스
class GameEngineSampler : public GameEngineResource<GameEngineSampler>
{
	friend class GameEngineSamplerSetter;

public:
	// constrcuter destructer
	GameEngineSampler();
	~GameEngineSampler();

	// delete Function
	GameEngineSampler(const GameEngineSampler& _Other) = delete;
	GameEngineSampler(GameEngineSampler&& _Other) noexcept = delete;
	GameEngineSampler& operator=(const GameEngineSampler& _Other) = delete;
	GameEngineSampler& operator=(GameEngineSampler&& _Other) noexcept = delete;

	// 생성된 샘플러를 GameEngineResource에 담는다.
	static std::shared_ptr<GameEngineSampler> Create(const std::string_view& _Name, const D3D11_SAMPLER_DESC& Desc)
	{
		std::shared_ptr<GameEngineSampler> NewTexture = GameEngineResource::Create(_Name);
		NewTexture->ResCreate(Desc);
		return NewTexture;
	}

protected:

private:
	D3D11_SAMPLER_DESC Desc;   // 샘플러 정보, Core_resource에서 전달받음
	ID3D11SamplerState* State; // CreateSamplerState 후 정보를 받을 것

	void ResCreate(const D3D11_SAMPLER_DESC& _Desc);

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);
};

