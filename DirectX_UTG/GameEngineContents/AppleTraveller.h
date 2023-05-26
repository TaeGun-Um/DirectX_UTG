#pragma once

#include "NPCDataBase.h"

// Ό³Έν :
class AppleTraveller : public NPCDataBase
{
public:
	// constrcuter destructer
	AppleTraveller();
	~AppleTraveller();

	// delete Function
	AppleTraveller(const AppleTraveller& _Other) = delete;
	AppleTraveller(AppleTraveller&& _Other) noexcept = delete;
	AppleTraveller& operator=(const AppleTraveller& _Other) = delete;
	AppleTraveller& operator=(AppleTraveller&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> AssitantRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> CollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> CollisionPtr = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> WaveCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> WaveCollisionPtr = nullptr;

	void InitRenderSetting();
	void InitCollisionSetting();

	float BlinkTime = 0.0f;
	float WaveAcc = 0.0f;
	float WaveTime = 0.0f;
	bool WaveInit = false;
	bool IsWave = false;
	bool WaveEnd = false;
	bool IsBlink = false;
};

