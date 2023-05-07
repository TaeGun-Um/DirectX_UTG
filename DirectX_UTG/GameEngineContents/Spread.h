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

	void SetMoveSpeed(float _MoveSpeed)
	{
		MoveSpeed = _MoveSpeed;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {};

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

	float MoveSpeed = 1200.0f;

	void MoveDirection(float _DeltaTime);
	void DeathCheck();

};

