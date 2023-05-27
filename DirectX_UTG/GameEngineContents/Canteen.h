#pragma once

#include "NPCDataBase.h"

// Ό³Έν :
class Canteen : public NPCDataBase
{
public:
	static Canteen* CanteenPtr;

	// constrcuter destructer
	Canteen();
	~Canteen();

	// delete Function
	Canteen(const Canteen& _Other) = delete;
	Canteen(Canteen&& _Other) noexcept = delete;
	Canteen& operator=(const Canteen& _Other) = delete;
	Canteen& operator=(Canteen&& _Other) noexcept = delete;

	void CollisionRenderOn()
	{
		CollisionRenderPtr->On();
	}

	void CollisionRenderOff()
	{
		CollisionRenderPtr->Off();
	}

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

