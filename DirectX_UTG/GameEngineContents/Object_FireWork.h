#pragma once

enum class FireWorkType
{
	Leader,
	Work_A,
	Work_B,
	Work_C,
};

enum class FireWorkState
{
	Move,
	Jump_Intro,
	Jump_Inter,
	Jump,
};

// Ό³Έν :
class Object_FireWork : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_FireWork();
	~Object_FireWork();

	// delete Function
	Object_FireWork(const Object_FireWork& _Other) = delete;
	Object_FireWork(Object_FireWork&& _Other) noexcept = delete;
	Object_FireWork& operator=(const Object_FireWork& _Other) = delete;
	Object_FireWork& operator=(Object_FireWork&& _Other) noexcept = delete;

	void SelectFireWork(FireWorkType _Type);

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
		InitPosition = GetTransform()->GetLocalPosition();
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
	float4 MoveDirect = float4::Zero;
	float MoveSpeed = 300.0f;
	
	bool Directbool = true;

	FireWorkType TypeValue = FireWorkType::Leader;
	FireWorkState StateValue = FireWorkState::Move;

	void ChangeState(FireWorkState _StateValue);
	void UpdateState(float _DeltaTime);
	
	void MoveStart();
	void MoveUpdate(float _DeltaTime);
	void MoveEnd();

	void Jump_IntroStart();
	void Jump_IntroUpdate(float _DeltaTime);
	void Jump_IntroEnd();

	void Jump_InterStart();
	void Jump_InterUpdate(float _DeltaTime);
	void Jump_InterEnd();

	void JumpStart();
	void JumpUpdate(float _DeltaTime);
	void JumpEnd();

};

