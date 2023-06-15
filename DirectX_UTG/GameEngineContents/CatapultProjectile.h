#pragma once

// Ό³Έν :
class CatapultProjectile : public GameEngineActor
{
public:
	// constrcuter destructer
	CatapultProjectile();
	~CatapultProjectile();

	// delete Function
	CatapultProjectile(const CatapultProjectile& _Other) = delete;
	CatapultProjectile(CatapultProjectile&& _Other) noexcept = delete;
	CatapultProjectile& operator=(const CatapultProjectile& _Other) = delete;
	CatapultProjectile& operator=(CatapultProjectile&& _Other) noexcept = delete;

	void SetDirection(bool _Direction)
	{
		if (true == _Direction)
		{
			GetTransform()->SetLocalPositiveScaleX();
		}

		Directbool = _Direction;
	}

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
		StartPosition = GetTransform()->GetLocalPosition();
	}

	void SetProjectileRotation(const float4& _Rotation)
	{
		GetTransform()->SetLocalRotation(_Rotation);
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

	void SetParryProjectileCreate()
	{
		IsParryProjectile = true;
	}

	void SetProjectileRandomAnimation();

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
	float MoveSpeed = 500.0f;

	bool Directbool = false;
	bool IsDeath = false;
	bool IsParryProjectile = false;

	void MoveDirection(float _DeltaTime);
	void CollisionCheck();
	void DeathCheck();

};

