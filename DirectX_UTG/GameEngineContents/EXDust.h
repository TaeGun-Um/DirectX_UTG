#pragma once

// Ό³Έν :
class EXDust : public GameEngineActor
{
public:
	// constrcuter destructer
	EXDust();
	~EXDust();

	// delete Function
	EXDust(const EXDust& _Other) = delete;
	EXDust(EXDust&& _Other) noexcept = delete;
	EXDust& operator=(const EXDust& _Other) = delete;
	EXDust& operator=(EXDust&& _Other) noexcept = delete;

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
		if (true == _Direction)
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

	float MoveSpeed = 600.0f;
	bool IsDeath = false;

	void MoveDirection(float _DeltaTime);
	void DeathCheck();

};

