#pragma once

enum class CroakState
{
	Intro,
	Idle,
	CreateMob_Start,
	CreateMob_Start_Loop,
	CreateMob_Start_Out,
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
	friend class Ribby;

public:
	static Croak* CroakPtr;

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
		MoveAbleTime = 0.0f;
		StateValue = CroakState::Idle;
		IsStageEnd = false;
		IsIntro = true;
		HP = 1000;
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
	
	float MoveAbleTime = 0.0f;
	float HP = 1000;

	bool IsStageEnd = false;
	bool IsDebugRender = false;
	bool IsBlink = false;

	void ActorInitSetting();
	void CollisionCheck();
	void HitBlink(float _DeltaTime);
	void CreateFirefly();

	float BlinkTime = 0.0f;
	float OriginMulColor = 0.0f;
	float BlinkMulColor = 0.0f;
	int BlinkCount = 1;

	CroakState StateValue = CroakState::Intro;

	float IntroLoopTime = 0.0f;
	float IdleDelayTime = 0.0f;
	float CreateMob_LoopTime = 0.0f;

	int CreatePlus = 0;
	int CreateMobCount = 0;

	bool IsIntro = true;
	bool IsCreatefly = false;
	bool CreateAction = false;
	bool CreateLoop = false;
	bool LoopCreateAction = false;
	bool LoopCreateEnd = false;

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

	void CreateMob_Start_LoopStart();
	void CreateMob_Start_LoopUpdate(float _DeltaTime);
	void CreateMob_Start_LoopEnd();

	void CreateMob_Start_OutStart();
	void CreateMob_Start_OutUpdate(float _DeltaTime);
	void CreateMob_Start_OutEnd();

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

