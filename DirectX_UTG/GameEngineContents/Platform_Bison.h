#pragma once

// Ό³Έν :
class Platform_Bison : public GameEngineActor
{
public:
	// constrcuter destructer
	Platform_Bison();
	~Platform_Bison();

	// delete Function
	Platform_Bison(const Platform_Bison& _Other) = delete;
	Platform_Bison(Platform_Bison&& _Other) noexcept = delete;
	Platform_Bison& operator=(const Platform_Bison& _Other) = delete;
	Platform_Bison& operator=(Platform_Bison&& _Other) noexcept = delete;

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
		StartPosition = GetTransform()->GetLocalPosition();
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> PlatformCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> HitCollisionRenderPtr = nullptr;

	std::shared_ptr<class GameEngineCollision> PlatformCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> HitCollisionPtr = nullptr;

	void MoveDirection(float _DeltaTime);
	void DeathCheck();

	float4 StartPosition = float4::Zero;

};

