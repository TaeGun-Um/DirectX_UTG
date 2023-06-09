#pragma once

// Ό³Έν :
class CoinAttack_Projectile : public GameEngineActor
{
public:
	// constrcuter destructer
	CoinAttack_Projectile();
	~CoinAttack_Projectile();

	// delete Function
	CoinAttack_Projectile(const CoinAttack_Projectile& _Other) = delete;
	CoinAttack_Projectile(CoinAttack_Projectile&& _Other) noexcept = delete;
	CoinAttack_Projectile& operator=(const CoinAttack_Projectile& _Other) = delete;
	CoinAttack_Projectile& operator=(CoinAttack_Projectile&& _Other) noexcept = delete;

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

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> ProjectileCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> ProjectileCollisionPtr = nullptr;

	float4 StartPosition = float4::Zero;
	float4 DirectNormal = float4::Zero;

	float MoveSpeed = 650.0f;
	int MoveSet = 1;

	void MoveDirection(float _DeltaTime);
	void DeathCheck();
};

