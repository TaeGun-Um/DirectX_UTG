#pragma once

enum class CroakState
{
	Intro,
	Idle,
	CreateMob_Start,
	CreateMob_Boil,
	CreateMob,
	CreateMob_End,
	Fan_Intro,
	Fan_Loop_A,
	Fan_Loop_B,
	Fan_End,
};

// Ό³Έν :
class Croak : public GameEngineActor
{
public:
	// constrcuter destructer
	Croak();
	~Croak();

	// delete Function
	Croak(const Croak& _Other) = delete;
	Croak(Croak&& _Other) noexcept = delete;
	Croak& operator=(const Croak& _Other) = delete;
	Croak& operator=(Croak&& _Other) noexcept = delete;

	bool GetIsStageEnd()
	{
		return IsStageEnd;
	}

	void SetInitReset()
	{
		IsStageEnd = false;
		GetBossHP();
	}

	float GetBossHP()
	{
		return HP;
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
	std::shared_ptr<class GameEngineSpriteRenderer> BodyCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> EXCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> BodyCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> EXCollisionPtr = nullptr;
	
	float HP = 500;
	bool IsStageEnd = false;

	void ActorInitSetting();
	void CollisionCheck();
	void HitBlink(float _DeltaTime);

	bool IsDebugRender = false;
	bool IsBlink = false;

	float BlinkTime = 0.0f;
	float OriginMulColor = 0.0f;
	float BlinkMulColor = 0.0f;
	int BlinkCount = 1;

	CroakState StateValue = CroakState::Intro;

	void ChangeState(CroakState _StateValue);
	void UpdateState(float _DeltaTime);

	void IntroStart();
	void IntroUpdate(float _DeltaTime);
	void IntroEnd();

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void CreateMob_StartStart();
	void CreateMob_StartUpdate(float _DeltaTime);
	void CreateMob_StartEnd();

	void CreateMob_BoilStart();
	void CreateMob_BoilUpdate(float _DeltaTime);
	void CreateMob_BoilEnd();

	void CreateMobStart();
	void CreateMobUpdate(float _DeltaTime);
	void CreateMobEnd();

	void CreateMob_EndStart();
	void CreateMob_EndUpdate(float _DeltaTime);
	void CreateMob_EndEnd();

	void Fan_IntroStart();
	void Fan_IntroUpdate(float _DeltaTime);
	void Fan_IntroEnd();

	void Fan_Loop_AStart();
	void Fan_Loop_AUpdate(float _DeltaTime);
	void Fan_Loop_AEnd();

	void Fan_Loop_BStart();
	void Fan_Loop_BUpdate(float _DeltaTime);
	void Fan_Loop_BEnd();

	void Fan_EndStart();
	void Fan_EndUpdate(float _DeltaTime);
	void Fan_EndEnd();
};

