#pragma once

#include "NPCDataBase.h"

// Ό³Έν :
class Axeman : public NPCDataBase
{
public:
	static Axeman* AxemanPtr;

	// constrcuter destructer
	Axeman();
	~Axeman();

	// delete Function
	Axeman(const Axeman& _Other) = delete;
	Axeman(Axeman&& _Other) noexcept = delete;
	Axeman& operator=(const Axeman& _Other) = delete;
	Axeman& operator=(Axeman&& _Other) noexcept = delete;

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

