#pragma once

enum class SpringState
{
	Intro,
	Land,
	Idle_Loop,
	Launch,
	Death,
};

// Ό³Έν :
class SpringObject : public GameEngineActor
{
public:
	// constrcuter destructer
	SpringObject();
	~SpringObject();

	// delete Function
	SpringObject(const SpringObject& _Other) = delete;
	SpringObject(SpringObject&& _Other) noexcept = delete;
	SpringObject& operator=(const SpringObject& _Other) = delete;
	SpringObject& operator=(SpringObject&& _Other) noexcept = delete;

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
	}

	void SetMoveSpeed(float _Value)
	{
		MoveSpeed = _Value;
	}

	void SetCollisionRenderOn()
	{
		ParryCollisionRenderPtr->On();

		if (false == IsParryProjectile)
		{
			ParryCollisionRenderPtr->Off();
		}
	}

	void SetCollisionRenderOff()
	{
		ParryCollisionRenderPtr->Off();
	}

	void SetParryBombCreate()
	{
		IsParryProjectile = true;
	}

	void SetColMap(const std::shared_ptr<GameEngineTexture>& _ColMap, PixelCollision::Coordinate _Pivot)
	{
		PixelCollisionCheck.SetColMap(_ColMap, _Pivot);
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	GameEngineSoundPlayer EffectPlayer;

	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> ParryCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> ParryCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> BreakCollisionPtr = nullptr;

	float4 MoveDirect = float4::Zero;
	float MoveSpeed = 0.0f;
	float JumpPower = 600.0f;

	bool IsJump = false;
	bool IsLand = false;
	bool IsLaunch = false;
	bool IsDeath = false;
	bool IsParryProjectile = false;

	void MoveDirection(float _DeltaTime);
	void PixelCheck(float _DeltaTime);
	void CollisionCheck();

	PixelCollision PixelCollisionCheck;

	SpringState StateValue = SpringState::Intro;

	void ChangeState(SpringState _StateValue);
	void UpdateState(float _DeltaTime);

	void IntroStart();
	void IntroUpdate(float _DeltaTime);
	void IntroEnd();

	void LandStart();
	void LandUpdate(float _DeltaTime);
	void LandEnd();

	void Idle_LoopStart();
	void Idle_LoopUpdate(float _DeltaTime);
	void Idle_LoopEnd();

	void LaunchStart();
	void LaunchUpdate(float _DeltaTime);
	void LaunchEnd();

	void DeathStart();
	void DeathUpdate(float _DeltaTime);
	void DeathEnd();
};

