#pragma once

enum class CloudState
{
	Idle,
	Plat_Intro,
	Plat,
	Plat_Outro,
};

// Ό³Έν :
class Dragon_CloudPlatform : public GameEngineActor
{
public:
	// constrcuter destructer
	Dragon_CloudPlatform();
	~Dragon_CloudPlatform();

	// delete Function
	Dragon_CloudPlatform(const Dragon_CloudPlatform& _Other) = delete;
	Dragon_CloudPlatform(Dragon_CloudPlatform&& _Other) noexcept = delete;
	Dragon_CloudPlatform& operator=(const Dragon_CloudPlatform& _Other) = delete;
	Dragon_CloudPlatform& operator=(Dragon_CloudPlatform&& _Other) noexcept = delete;

	void SetActorInitPosition(float4 _Value)
	{
		ActorInitPosition = _Value;
	}

	void SetIsMove()
	{
		IsMove = true;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> CloudRenderPtr = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> PlatformCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> PlatformCollisionPtr = nullptr;

	float MoveSpeed = 0.0f;
	float MoveDis = 0.0f;

	float4 ActorInitPosition = float4::Zero;

	bool IsStanding = false;
	bool IsMove = false;

	void CollisionCheck();

	CloudState StateValue = CloudState::Idle;

	void ChangeState(CloudState _StateValue);
	void UpdateState(float _DeltaTime);

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void Plat_IntroStart();
	void Plat_IntroUpdate(float _DeltaTime);
	void Plat_IntroEnd();

	void PlatStart();
	void PlatUpdate(float _DeltaTime);
	void PlatEnd();

	void Plat_OutroStart();
	void Plat_OutroUpdate(float _DeltaTime);
	void Plat_OutroEnd();
};

