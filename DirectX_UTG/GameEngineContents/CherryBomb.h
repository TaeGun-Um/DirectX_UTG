#pragma once

// Ό³Έν :
class CherryBomb : public GameEngineActor
{
public:
	// constrcuter destructer
	CherryBomb();
	~CherryBomb();

	// delete Function
	CherryBomb(const CherryBomb& _Other) = delete;
	CherryBomb(CherryBomb&& _Other) noexcept = delete;
	CherryBomb& operator=(const CherryBomb& _Other) = delete;
	CherryBomb& operator=(CherryBomb&& _Other) noexcept = delete;

	void SetDirection(bool _Direction)
	{
		if (false == _Direction)
		{
			GetTransform()->SetLocalNegativeScaleX();
		}

		Directbool = _Direction;
	}

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
	}

	void SetJumpPower(float _Value)
	{
		JumpPower = _Value;
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
	std::shared_ptr<class GameEngineSpriteRenderer> ProjectileCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> ProjectileCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> ParryCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> ParryCollisionPtr = nullptr;

	float4 MoveDirect = float4::Zero;
	float MoveSpeed = 330.0f;
	float JumpPower = 0.0f;

	bool Directbool = false;
	bool IsJump = false;
	bool IsDeath = false;
	bool IsParryProjectile = false;

	void BombExplodeSound();
	void MoveDirection(float _DeltaTime);
	void PixelCheck(float _DeltaTime);
	void CollisionCheck();
	void DeathCheck();
	void CreateBombSFX();

	PixelCollision PixelCollisionCheck;

};

