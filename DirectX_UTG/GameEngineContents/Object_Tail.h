#pragma once

// Ό³Έν :
class Object_Tail : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_Tail();
	~Object_Tail();

	// delete Function
	Object_Tail(const Object_Tail& _Other) = delete;
	Object_Tail(Object_Tail&& _Other) noexcept = delete;
	Object_Tail& operator=(const Object_Tail& _Other) = delete;
	Object_Tail& operator=(Object_Tail&& _Other) noexcept = delete;

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
		InitPosition = GetTransform()->GetLocalPosition();
		OneStepPosition = InitPosition + float4{0, 150};
		TwoStepPosition = OneStepPosition + float4{0, 450};
	}

	void SetCollisionRenderOn()
	{
		BodyCollisionRenderPtr->On();
	}

	void SetCollisionRenderOff()
	{
		BodyCollisionRenderPtr->Off();
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BodyCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> BodyCollisionPtr = nullptr;

	void MoveCalculation(float _DeltaTime);
	void DeathCheck();

	float4 InitPosition = float4::Zero;
	float4 OneStepPosition = float4::Zero;
	float4 TwoStepPosition = float4::Zero;
	float4 MoveAccel = float4::Zero;

	float MoveTime = 0.0f;
	float BackTime = 0.0f;

	bool OneStep = false;
	bool TwoStep = false;
};

