#pragma once

enum class RenderType
{
	BottleA,
	BottleB,
	BottleC,
	BottleD,
	BottleE,
	BottleF,
};

enum class SitckState
{
	Intro,
	Idle,
	Back,
	Move,
	RollBack,
	End,
};

// Ό³Έν :
class Stick : public GameEngineActor
{
public:
	// constrcuter destructer
	Stick();
	~Stick();

	// delete Function
	Stick(const Stick& _Other) = delete;
	Stick(Stick&& _Other) noexcept = delete;
	Stick& operator=(const Stick& _Other) = delete;
	Stick& operator=(Stick&& _Other) noexcept = delete;

	void SelectRenderType(RenderType _Type, bool _Direct);

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
		InitPosition = GetTransform()->GetLocalPosition();
	}

	void StartAction()
	{
		IsAction = true;
	}

	bool GetIsAction()
	{
		return IsAction;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BottleRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> StickRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> AttackCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> AttackCollisionPtr = nullptr;

	void BottleRotation(float _DeltaTime, float _Value);

	SitckState StateValue = SitckState::Intro;
	bool Directbool = true;
	bool IsAction = false;
	bool Vibrationbool = false;

	float4 InitPosition = float4::Zero;
	float4 IdlePosition = float4::Zero;
	float4 BackPosition = float4::Zero;
	float4 MovePosition = float4::Zero;
	float4 MoveDistance = float4::Zero;

	float4 EndStartPosition = float4::Zero;

	float Angle = 0.0f;
	float VibrationTime = 0.0f;
	float RollDesc = 0.0f;
	float EndMoveTime = 0.0f;

	void ChangeState(SitckState _StateValue);
	void UpdateState(float _DeltaTime);

	void IntroStart();
	void IntroUpdate(float _DeltaTime);
	void IntroEnd();

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void BackStart();
	void BackUpdate(float _DeltaTime);
	void BackEnd();

	void MoveStart();
	void MoveUpdate(float _DeltaTime);
	void MoveEnd();

	void RollBackStart();
	void RollBackUpdate(float _DeltaTime);
	void RollBackEnd();

	void EndStart();
	void EndUpdate(float _DeltaTime);
	void EndEnd();
};

