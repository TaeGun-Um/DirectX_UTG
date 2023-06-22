#pragma once

enum class BallState
{
	Intro,
	Loop,
	Death,
};

// Ό³Έν :
class GhostMouse_Projectile : public GameEngineActor
{
public:
	// constrcuter destructer
	GhostMouse_Projectile();
	~GhostMouse_Projectile();

	// delete Function
	GhostMouse_Projectile(const GhostMouse_Projectile& _Other) = delete;
	GhostMouse_Projectile(GhostMouse_Projectile&& _Other) noexcept = delete;
	GhostMouse_Projectile& operator=(const GhostMouse_Projectile& _Other) = delete;
	GhostMouse_Projectile& operator=(GhostMouse_Projectile&& _Other) noexcept = delete;

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
		StartPosition = GetTransform()->GetLocalPosition();
	}

	void SetCollisionRenderOn()
	{
		ProjectileCollisionRenderPtr->On();
		ParryCollisionRenderPtr->On();

		if (false == IsParryProjectile)
		{
			ParryCollisionRenderPtr->Off();
		}
	}

	void SetCollisionRenderOff()
	{
		ProjectileCollisionRenderPtr->Off();
		ParryCollisionRenderPtr->Off();
	}

	void SetParryCreate(bool _Is)
	{
		IsParryProjectile = _Is;
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
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> ProjectileCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> ProjectileCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> ParryCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> ParryCollisionPtr = nullptr;

	float4 StartPosition = float4::Zero;
	float4 DirectNormal = float4::Zero;
	float MoveSpeed = 550.0f;

	bool IsDeath = false;
	bool IsParryProjectile = false;
	bool IsPink = false;
	bool IsCreateSmall = false;

	int MoveSet = 1;

	PixelCollision PixelCollisionCheck;

	void CreateSmallBall();
	void CollisionCheck();
	void MoveDirection(float _DeltaTime);
	void PixelCheck(float _DeltaTime);

	BallState StateValue = BallState::Intro;

	void ChangeState(BallState _StateValue);
	void UpdateState(float _DeltaTime);

	void IntroStart();
	void IntroUpdate(float _DeltaTime);
	void IntroEnd();

	void LoopStart();
	void LoopUpdate(float _DeltaTime);
	void LoopEnd();

	void DeathStart();
	void DeathUpdate(float _DeltaTime);
	void DeathEnd();
};

