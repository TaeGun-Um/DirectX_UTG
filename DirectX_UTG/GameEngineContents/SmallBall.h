#pragma once

// Ό³Έν :
class SmallBall : public GameEngineActor
{
public:
	// constrcuter destructer
	SmallBall();
	~SmallBall();

	// delete Function
	SmallBall(const SmallBall& _Other) = delete;
	SmallBall(SmallBall&& _Other) noexcept = delete;
	SmallBall& operator=(const SmallBall& _Other) = delete;
	SmallBall& operator=(SmallBall&& _Other) noexcept = delete;

	void SetDirectionNegative()
	{
		Directbool = false;
		GetTransform()->SetLocalNegativeScaleX();
	}

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
		StartPosition = GetTransform()->GetLocalPosition();
	}

	void SetIsPink(bool _IsPink)
	{
		IsPink = _IsPink;
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

	bool IsPink = false;
	bool Directbool = true;
	float MoveSpeed = 650.0f;

	void MoveDirection(float _DeltaTime);
	void DeathCheck();

};

