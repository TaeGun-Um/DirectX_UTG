#pragma once

enum class FireState
{
	Intro,
	Fire,
	FireLoop,
	Outro,
};

// Ό³Έν :
class Flamethrower : public GameEngineActor
{
public:
	// constrcuter destructer
	Flamethrower();
	~Flamethrower();

	// delete Function
	Flamethrower(const Flamethrower& _Other) = delete;
	Flamethrower(Flamethrower&& _Other) noexcept = delete;
	Flamethrower& operator=(const Flamethrower& _Other) = delete;
	Flamethrower& operator=(Flamethrower&& _Other) noexcept = delete;

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
	}

	void SetDirectionNegative()
	{
		GetTransform()->SetLocalNegativeScaleX();
	}

	void SetCollisionRenderOn()
	{
		IsDebugRender = true;
	}

	void SetCollisionRenderOff()
	{
		IsDebugRender = false;
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

	float MinAlpha = 0.0f;
	float MaxAlpha = 0.0f;
	float DelayTime = 0.0f;
	float IntroLoopTime = 0.0f;
	float FireLoopTime = 0.0f;

	bool IsEnd = false;
	bool IsDebugRender = false;

	FireState StateValue = FireState::Intro;

	void ChangeState(FireState _StateValue);
	void UpdateState(float _DeltaTime);

	void IntroStart();
	void IntroUpdate(float _DeltaTime);
	void IntroEnd();

	void FireStart();
	void FireUpdate(float _DeltaTime);
	void FireEnd();

	void FireLoopStart();
	void FireLoopUpdate(float _DeltaTime);
	void FireLoopEnd();

	void OutroStart();
	void OutroUpdate(float _DeltaTime);
	void OutroEnd();

};

