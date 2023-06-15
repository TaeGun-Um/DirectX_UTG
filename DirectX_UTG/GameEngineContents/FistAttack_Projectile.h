#pragma once

#include <GameEngineCore/GameEngineCollision.h>

// Ό³Έν :
class FistAttack_Projectile : public GameEngineActor
{
public:
	// constrcuter destructer
	FistAttack_Projectile();
	~FistAttack_Projectile();

	// delete Function
	FistAttack_Projectile(const FistAttack_Projectile& _Other) = delete;
	FistAttack_Projectile(FistAttack_Projectile&& _Other) noexcept = delete;
	FistAttack_Projectile& operator=(const FistAttack_Projectile& _Other) = delete;
	FistAttack_Projectile& operator=(FistAttack_Projectile&& _Other) noexcept = delete;

	void SetDirection(bool _Direction)
	{
		if (false == _Direction)
		{
			GetTransform()->SetLocalNegativeScaleX();
		}
	}

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
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

	void SetParryFistCreate()
	{
		IsParryProjectile = true;
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

	float MoveSpeed = 700.0f;

	bool IsDeath = false;
	bool IsParryProjectile = false;

	void MoveDirection(float _DeltaTime);
	void CollisionCheck();
	void DeathCheck();

};