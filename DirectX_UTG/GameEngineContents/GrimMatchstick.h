#pragma once

enum class DragonState
{
	Intro,
	Idle,

};

// Ό³Έν :
class GrimMatchstick : public GameEngineActor
{
public:
	static GrimMatchstick* GrimMatchstickPtr;

	// constrcuter destructer
	GrimMatchstick();
	~GrimMatchstick();

	// delete Function
	GrimMatchstick(const GrimMatchstick& _Other) = delete;
	GrimMatchstick(GrimMatchstick&& _Other) noexcept = delete;
	GrimMatchstick& operator=(const GrimMatchstick& _Other) = delete;
	GrimMatchstick& operator=(GrimMatchstick&& _Other) noexcept = delete;

	float GetBossHP()
	{
		return HP;
	}

	void BossHPDown()
	{
		HP -= 100;
	}

	void DebugRenderOn()
	{
		IsDebugRender = true;
	}

	void DebugRenderOff()
	{
		IsDebugRender = false;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

	float HP = 1000.0f;
	bool IsDebugRender = false;
	bool IsStageEnd = false;
	bool IsBlink = false;

	float4 OriginMulColor = float4::Zero;
	float4 BlinkMulColor = float4::Zero;
	float BlinkTime = 0.0f;
	int BlinkCount = 1;

	void ActorInitSetting();

	DragonState StateValue = DragonState::Idle;

	void ChangeState(DragonState _StateValue);
	void UpdateState(float _DeltaTime);

	void IntroStart();
	void IntroUpdate(float _DeltaTime);
	void IntroEnd();

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

};

