#pragma once

enum class RibbyState
{
	Intro,
	Intro_Loop,
	Intro_End,
	Idle,

	FistAttack_Intro,
	FistAttack_Intro_Loop,
	FistAttack_Intro_Out,
	FistAttack_Loop,
	FistAttack_End,

	Roll_Intro,
	Roll_Intro_Loop,
	Roll_Intro_Out,
	Roll_Loop,
	Roll_End,

	ClapAttack_Intro,
	ClapAttack,
	ClapAttack_Loop,
	ClapAttack_LoopBack,
	ClapAttack_End,
};

// Ό³Έν :
class Ribby : public GameEngineActor
{
	friend class Croak;

public:
	static Ribby* RibbyPtr;

	// constrcuter destructer
	Ribby();
	~Ribby();

	// delete Function
	Ribby(const Ribby& _Other) = delete;
	Ribby(Ribby&& _Other) noexcept = delete;
	Ribby& operator=(const Ribby& _Other) = delete;
	Ribby& operator=(Ribby&& _Other) noexcept = delete;

	bool GetIsStageEnd()
	{
		return IsStageEnd;
	}

	void SetInitReset()
	{
		MoveAbleTime = 0.0f;
		StateValue = RibbyState::Idle;
		IsStageEnd = false;
		IsIntro = true;
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

	bool IsStageEnd = false;
	bool IsDebugRender = false;
	bool IsBlink = false;

	void ActorInitSetting();
	void DirectCheck();
	void CollisionCheck();
	void CollisionSetting();
	void HitBlink(float _DeltaTime);

	void CreateFistProjectile();
	void CreateBallProjectile();
	void CreateFistSFX(float4 _Position);

	float BlinkTime = 0.0f;
	float OriginMulColor = 0.0f;
	float BlinkMulColor = 0.0f;
	int BlinkCount = 1;

	RibbyState StateValue = RibbyState::Intro;

	float4 RollStartPosition = float4::Zero;
	float4 RollEndPosition = float4::Zero;
	float4 MoveDistance = float4::Zero;

	float IntroLoopTime = 0.0f;
	float IdleDelayTime = 0.0f;
	float FistLoopDelayTime = 0.0f;
	float FistAttackDelayTime = 0.0f;
	float LoopInterDelayTime = 0.0f;
	float RollDelayTime = 0.0f;
	float ClapLoopTime = 0.0f;

	bool Directbool = false;
	bool IsIntro = true;
	bool IsRoll = false;
	bool IsClap = false;
	bool IsFistAttak = false;
	bool ParryFistCreate = false;

	int FistCreateCount = 0;
	int ParryFistCount = 1;
	int ClapCount = 4;
	int CreateBallCount = 1;

	void ChangeState(RibbyState _StateValue);
	void UpdateState(float _DeltaTime);

	void IntroStart();
	void IntroUpdate(float _DeltaTime);
	void IntroEnd();

	void Intro_LoopStart();
	void Intro_LoopUpdate(float _DeltaTime);
	void Intro_LoopEnd();

	void Intro_EndStart();
	void Intro_EndUpdate(float _DeltaTime);
	void Intro_EndEnd();

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void FistAttack_IntroStart();
	void FistAttack_IntroUpdate(float _DeltaTime);
	void FistAttack_IntroEnd();

	void FistAttack_Intro_LoopStart();
	void FistAttack_Intro_LoopUpdate(float _DeltaTime);
	void FistAttack_Intro_LoopEnd();

	void FistAttack_Intro_OutStart();
	void FistAttack_Intro_OutUpdate(float _DeltaTime);
	void FistAttack_Intro_OutEnd();

	void FistAttack_LoopStart();
	void FistAttack_LoopUpdate(float _DeltaTime);
	void FistAttack_LoopEnd();

	void FistAttack_EndStart();
	void FistAttack_EndUpdate(float _DeltaTime);
	void FistAttack_EndEnd();

	void Roll_IntroStart();
	void Roll_IntroUpdate(float _DeltaTime);
	void Roll_IntroEnd();

	void Roll_Intro_LoopStart();
	void Roll_Intro_LoopUpdate(float _DeltaTime);
	void Roll_Intro_LoopEnd();

	void Roll_Intro_OutStart();
	void Roll_Intro_OutUpdate(float _DeltaTime);
	void Roll_Intro_OutEnd();

	void Roll_LoopStart();
	void Roll_LoopUpdate(float _DeltaTime);
	void Roll_LoopEnd();

	void Roll_EndStart();
	void Roll_EndUpdate(float _DeltaTime);
	void Roll_EndEnd();

	void ClapAttack_IntroStart();
	void ClapAttack_IntroUpdate(float _DeltaTime);
	void ClapAttack_IntroEnd();

	void ClapAttackStart();
	void ClapAttackUpdate(float _DeltaTime);
	void ClapAttackEnd();

	void ClapAttack_LoopStart();
	void ClapAttack_LoopUpdate(float _DeltaTime);
	void ClapAttack_LoopEnd();

	void ClapAttack_LoopBackStart();
	void ClapAttack_LoopBackUpdate(float _DeltaTime);
	void ClapAttack_LoopBackEnd();

	void ClapAttack_EndStart();
	void ClapAttack_EndUpdate(float _DeltaTime);
	void ClapAttack_EndEnd();
};

