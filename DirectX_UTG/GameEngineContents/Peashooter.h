#pragma once

class Player;

// Ό³Έν :
class Peashooter : public GameEngineActor
{
public:
	// constrcuter destructer
	Peashooter();
	~Peashooter();

	// delete Function
	Peashooter(const Peashooter& _Other) = delete;
	Peashooter(Peashooter&& _Other) noexcept = delete;
	Peashooter& operator=(const Peashooter& _Other) = delete;
	Peashooter& operator=(Peashooter&& _Other) noexcept = delete;

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

	void SetMoveSpeed(float _MoveSpeed)
	{
		MoveSpeed = _MoveSpeed;
	}

	void SetColMap(const std::shared_ptr<class GameEngineTexture>& _ColMap, PixelCollision::Coordinate _Pivot)
	{
		PixelCollisionCheck.SetColMap(_ColMap, _Pivot);
	}

	void SetPeashooterDeath();

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

	float MoveSpeed = 1300.0f;
	bool IsDeath = false;
	bool Check = false;
	bool IsHit = false;

	void MoveDirection(float _DeltaTime);
	void HitCheck();
	void PixelCheck();
	void DeathCheck();
};

