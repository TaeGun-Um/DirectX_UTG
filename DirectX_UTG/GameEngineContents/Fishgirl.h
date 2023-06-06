#pragma once

#include "NPCDataBase.h"
#include "NPC_TextBox.h"

// ���� :
class Fishgirl : public NPCDataBase
{
public:
	static Fishgirl* FishgirlPtr;

	// constrcuter destructer
	Fishgirl();
	~Fishgirl();

	// delete Function
	Fishgirl(const Fishgirl& _Other) = delete;
	Fishgirl(Fishgirl&& _Other) noexcept = delete;
	Fishgirl& operator=(const Fishgirl& _Other) = delete;
	Fishgirl& operator=(Fishgirl&& _Other) noexcept = delete;

	void CollisionRenderOn()
	{
		CollisionRenderPtr->On();
	}

	void CollisionRenderOff()
	{
		CollisionRenderPtr->Off();
	}

	void TextBoxPositionSetting()
	{
		float4 PlusLocalPosition = float4{ -170, 140, -50 };
		float4 ActorLocalPosition = GetTransform()->GetLocalPosition();

		NPC_TextBoxRender->LocalPositionSetting(ActorLocalPosition + PlusLocalPosition);
		TextEndCount = 5;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> CollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> CollisionPtr = nullptr;

	std::shared_ptr<class NPC_TextBox> NPC_TextBoxRender = nullptr;

	void InitRenderSetting();
	void InitCollisionSetting();
	void TextBoxOn(float _DeltaTime);
	void AnimationLoop(float _DeltaTime);

	float BlinkTime = 0.0f;
	float BoxInterActionDelayTime = 0.0f;

	int TextCount = 0;
	int TextEndCount = 0;

	bool IsBlink = false;
	bool NextStep = false;
};

