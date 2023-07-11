#pragma once

// Ό³Έν :
class Object_GreenRing : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_GreenRing();
	~Object_GreenRing();

	// delete Function
	Object_GreenRing(const Object_GreenRing& _Other) = delete;
	Object_GreenRing(Object_GreenRing&& _Other) noexcept = delete;
	Object_GreenRing& operator=(const Object_GreenRing& _Other) = delete;
	Object_GreenRing& operator=(Object_GreenRing&& _Other) noexcept = delete;

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
		InitPosition = GetTransform()->GetLocalPosition();
	}

	void SetCollisionRenderOn()
	{
		BodyCollisionRenderPtr->On();
	}

	void SetCollisionRenderOff()
	{
		BodyCollisionRenderPtr->Off();
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BodyCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> BodyCollisionPtr = nullptr;

	void MoveCalculation(float _DeltaTime);
	void DeathCheck();

	float MoveSpeed = 300.0f;

	float4 InitPosition = float4::Zero;

};

