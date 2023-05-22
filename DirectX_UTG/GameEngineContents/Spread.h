#pragma once

// Ό³Έν :
class Spread : public GameEngineActor
{
public:
	// constrcuter destructer
	Spread();
	~Spread();

	// delete Function
	Spread(const Spread& _Other) = delete;
	Spread(Spread&& _Other) noexcept = delete;
	Spread& operator=(const Spread& _Other) = delete;
	Spread& operator=(Spread&& _Other) noexcept = delete;

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
	}

	void SetProjectileRotation(const float4& _Rotation)
	{
		GetTransform()->SetLocalRotation(_Rotation);
	}

	void SetDirection(bool _Direction)
	{
		if (false == _Direction)
		{
			GetTransform()->SetLocalNegativeScaleX();
		}
	}

	void SetDeathType(bool _DeathType)
	{
		DeathType = _DeathType;
	}

	void SetMoveSpeed(float _MoveSpeed)
	{
		MoveSpeed = _MoveSpeed;
	}

	void SetColMap(const std::shared_ptr<class GameEngineTexture>& _ColMap, PixelCollision::Coordinate _Pivot)
	{
		PixelCollisionCheck.SetColMap(_ColMap, _Pivot);
	}

	void SetSpreadDeath();
	
	void SetHitture()
	{
		IsHit = true;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {};

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> ProjectileCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> ProjectileCollisionPtr = nullptr;
	PixelCollision PixelCollisionCheck;

	float MoveSpeed = 1200.0f;
	bool DeathType = true;
	bool IsDeath = false;
	bool Check = false;
	bool IsHit = false;

	void MoveDirection(float _DeltaTime);
	void HitCheck();
	void PixelCheck();
	void DeathCheck();

	void SetSpreadDeathWeak();
};

