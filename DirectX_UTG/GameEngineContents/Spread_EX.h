#pragma once

enum class Spread_EXState
{
	Spawn,
	Loop,
	Death,
};

// Ό³Έν :
class Spread_EX : public GameEngineActor
{
public:
	// constrcuter destructer
	Spread_EX();
	~Spread_EX();

	// delete Function
	Spread_EX(const Spread_EX& _Other) = delete;
	Spread_EX(Spread_EX&& _Other) noexcept = delete;
	Spread_EX& operator=(const Spread_EX& _Other) = delete;
	Spread_EX& operator=(Spread_EX&& _Other) noexcept = delete;

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
	}

	void SetProjectileRotation(const float4& _Rotation)
	{
		GetTransform()->SetLocalRotation(_Rotation);
	}

	void SetSpread_EXDeath();

	void SetCollisionRenderOn()
	{
		ProjectileCollisionRenderPtr->On();
	}

	void SetCollisionRenderOff()
	{
		ProjectileCollisionRenderPtr->Off();
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {};

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> FalmeRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> ProjectileCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> ProjectileCollisionPtr = nullptr;

	Spread_EXState StateValue = Spread_EXState::Spawn;

	float MoveSpeed = 300.0f;
	bool IsDeath = false;

	void ChangeState(Spread_EXState _StateValue);
	void UpdateState(float _DeltaTime);

	void SpawnStart();
	void SpawnUpdate(float _DeltaTime);
	void SpawnEnd();

	void LoopStart();
	void LoopUpdate(float _DeltaTime);
	void LoopEnd();

	void DeathStart();
	void DeathUpdate(float _DeltaTime);
	void DeathEnd();
};

