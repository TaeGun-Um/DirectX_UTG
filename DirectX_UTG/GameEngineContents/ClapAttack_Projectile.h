#pragma once

// 설명 :
class ClapAttack_Projectile : public GameEngineActor
{
public:
	// constrcuter destructer
	ClapAttack_Projectile();
	~ClapAttack_Projectile();

	// delete Function
	ClapAttack_Projectile(const ClapAttack_Projectile& _Other) = delete;
	ClapAttack_Projectile(ClapAttack_Projectile&& _Other) noexcept = delete;
	ClapAttack_Projectile& operator=(const ClapAttack_Projectile& _Other) = delete;
	ClapAttack_Projectile& operator=(ClapAttack_Projectile&& _Other) noexcept = delete;

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
		StartPosition = GetTransform()->GetLocalPosition();
	}

	void SetProjectileRotation(const float4& _Rotation, bool _Direct)
	{
		GetTransform()->SetLocalRotation(_Rotation);
		Directbool = _Direct;
	}

	void SetCollisionRenderOn()
	{
		ProjectileCollisionRenderPtr->On();
		DebugRenderPtr->On();
	}

	void SetCollisionRenderOff()
	{
		ProjectileCollisionRenderPtr->Off();
		DebugRenderPtr->Off();
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

	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr = nullptr;

private:
	void CreateClapAttackSFX();
	void PixelCheck(float _DeltaTime);
	void MoveDirection(float _DeltaTime);
	void DeathCheck();

	float4 StartPosition = float4::Zero;

	float MoveSpeed = 660.0f;
	float BouncingBufferTime = 0.0f;
	bool IsDeath = false;
	bool Directbool = true; // true = 위 // false == 아래
	int BoundCount = 0;

	PixelCollision PixelCollisionCheck;

};

