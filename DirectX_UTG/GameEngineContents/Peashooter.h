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

