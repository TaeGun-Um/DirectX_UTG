#pragma once

// ���� :
class Peashooter_EX : public GameEngineActor
{
public:
	// constrcuter destructer
	Peashooter_EX();
	~Peashooter_EX();

	// delete Function
	Peashooter_EX(const Peashooter_EX& _Other) = delete;
	Peashooter_EX(Peashooter_EX&& _Other) noexcept = delete;
	Peashooter_EX& operator=(const Peashooter_EX& _Other) = delete;
	Peashooter_EX& operator=(Peashooter_EX&& _Other) noexcept = delete;

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

	void SetHitture()
	{
		IsHit = true;
		--Stack;
		EffectPlayer = GameEngineSound::Play("player_weapon_peashot_death_001.wav");
	}

	void SetPeashooter_EXDeath();

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
	GameEngineSoundPlayer EffectPlayer;

	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> ProjectileCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> ProjectileCollisionPtr = nullptr;

	float MoveSpeed = 600.0f;
	float StopTime = 0.0f;
	bool IsDeath = false;
	bool Check = false;
	bool IsHit = false;
	int Stack = 3;

	void MoveDirection(float _DeltaTime);
	void DeathCheck();

};

