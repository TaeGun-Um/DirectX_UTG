#pragma once

#include "NPCDataBase.h"
#include "NPC_TextBox.h"

// Ό³Έν :
class AppleTraveller : public NPCDataBase
{
public:
	static AppleTraveller* AppleTravellerPtr;

	// constrcuter destructer
	AppleTraveller();
	~AppleTraveller();

	// delete Function
	AppleTraveller(const AppleTraveller& _Other) = delete;
	AppleTraveller(AppleTraveller&& _Other) noexcept = delete;
	AppleTraveller& operator=(const AppleTraveller& _Other) = delete;
	AppleTraveller& operator=(AppleTraveller&& _Other) noexcept = delete;

	void CollisionRenderOn()
	{
		CollisionRenderPtr->On();
		WaveCollisionRenderPtr->On();
	}

	void CollisionRenderOff()
	{
		CollisionRenderPtr->Off();
		WaveCollisionRenderPtr->Off();
	}

	void TextBoxPositionSetting()
	{
		float4 PlusLocalPosition = float4{ -170, 140, -50 };
		float4 ActorLocalPosition = GetTransform()->GetLocalPosition();

		NPC_TextBoxRender->LocalPositionSetting(ActorLocalPosition + PlusLocalPosition);
		TextEndCount = 3;
	}

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

	std::shared_ptr<class NPC_TextBox> NPC_TextBoxRender = nullptr;

	void InitRenderSetting();
	void InitCollisionSetting();
	void AnimationLoop(float _DeltaTime);
	void TextBoxOn(float _DeltaTime);

	int TextCount = 0;
	int TextEndCount = 0;

	float BlinkTime = 0.0f;
	float WaveAcc = 0.0f;
	float WaveTime = 0.0f;
	float BoxInterActionDelayTime = 0.0f;

	bool WaveInit = false;
	bool IsWave = false;
	bool WaveEnd = false;
	bool IsBlink = false;
	bool NextStep = false;
};

