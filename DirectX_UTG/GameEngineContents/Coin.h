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

};

