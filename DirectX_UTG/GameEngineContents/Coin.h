#pragma once

#include "NPCDataBase.h"

// Ό³Έν :
class Coin : public NPCDataBase
{
public:
	// constrcuter destructer
	Coin();
	~Coin();

	// delete Function
	Coin(const Coin& _Other) = delete;
	Coin(Coin&& _Other) noexcept = delete;
	Coin& operator=(const Coin& _Other) = delete;
	Coin& operator=(Coin&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> CollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> CollisionPtr = nullptr;

	void InitRenderSetting();
	void InitCollisionSetting();

	float TransitionTime = 0.0f;
	float EyeTime = 0.0f;
	float WaitTime1 = 0.0f;
	float WaitTime2 = 0.0f;
	float WaitTime3 = 0.0f;

	int Count1 = 1;
	int Count2 = 1;
	int Count3 = 1;
	int Count4 = 1;
	int Count5 = 1;
	int Count6 = 1;
	int Count7 = 1;
	int Count8 = 1;
	int Count9 = 1;
	int Count10 = 1;
};

