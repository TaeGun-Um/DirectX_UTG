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

	void SetStartPosition(float4 _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
		InitPlayerPosition = _PlayerPosition;
		InitPlayerXPosition = _PlayerPosition.x;
	}

	void SetDirection(bool _Direction)
	{
		Direction = _Direction;

		if (false == _Direction)
		{
			GetTransform()->SetLocalNegativeScaleX();
		}
	}

	void SetADValue(AttackDirection _ADValue)
	{
		ADValue = _ADValue;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {};

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

	float4 InitPlayerPosition = float4::Zero;
	float InitPlayerXPosition = 0.0f;
	float MoveSpeed = 1200.0f;
	bool Direction = true;   // true == Right // false == Left

	void MoveDirection(float _DeltaTime);
	void DeathCheck();

	AttackDirection ADValue = AttackDirection::Right_Front;
};

