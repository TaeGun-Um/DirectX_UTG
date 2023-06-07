#pragma once

enum class FlyState
{
	Idle,
	Move,
	Death,
};

enum class FlyDirect
{
	Up,
	Right_DU,
	Right,
	Right_DD,
	Down,
	Left_DD,
	Left,
	Left_DU,
};

// Ό³Έν :
class Croak_Firefly : public GameEngineActor
{
public:
	// constrcuter destructer
	Croak_Firefly();
	~Croak_Firefly();

	// delete Function
	Croak_Firefly(const Croak_Firefly& _Other) = delete;
	Croak_Firefly(Croak_Firefly&& _Other) noexcept = delete;
	Croak_Firefly& operator=(const Croak_Firefly& _Other) = delete;
	Croak_Firefly& operator=(Croak_Firefly&& _Other) noexcept = delete;

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
		StartPosition = GetTransform()->GetLocalPosition();
	}

	void SetCollisionRenderOn()
	{
		ProjectileCollisionRenderPtr->On();
	}

	void SetCollisionRenderOff()
	{
		ProjectileCollisionRenderPtr->Off();
	}

	void SetIsFirstSpawn()
	{
		IsFirst = true;
		SpawnPosition = StartPosition + float4{ -700, 120 };
	}

	void SetIsSecondSpawn()
	{
		IsSecond = true;
		SpawnPosition = StartPosition + float4{ -150, 120 };
	}

	void SetIsThirdSpawn()
	{
		IsThird = true;
		SpawnPosition = StartPosition + float4{ -550, 120 };
	}

	void SetIsFourthSpawn()
	{
		IsFourth = true;
		SpawnPosition = StartPosition + float4{ -270, 120 };
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> ProjectileCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> ProjectileCollisionPtr = nullptr;

	void SpawnMove(float _DeltaTime);
	void CollisionCheck();

	bool IsFirst = false;
	bool IsSecond = false;
	bool IsThird = false;
	bool IsFourth = false;

	FlyState StateValue = FlyState::Idle;
	FlyDirect DV = FlyDirect::Left;

	float4 StartPosition = float4::Zero;
	float4 CurPosition = float4::Zero;
	float4 SpawnPosition = float4::Zero;
	float4 MoveDistance = float4::Zero;

	float4 TrackingPosition = float4::Zero;
	float4 DirectNormal = float4::Zero;

	float MoveSpeed = 200.0f;
	float MoveTime = 0.0f;
	float IdleDelayTime = 0.0f;
	bool IsSpawn = true;
	bool IsDeath = false;

	void ChangeState(FlyState _StateValue);
	void UpdateState(float _DeltaTime);

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void MoveStart();
	void MoveUpdate(float _DeltaTime);
	void MoveEnd();

	void DeathStart();
	void DeathUpdate(float _DeltaTime);
	void DeathEnd();
};

