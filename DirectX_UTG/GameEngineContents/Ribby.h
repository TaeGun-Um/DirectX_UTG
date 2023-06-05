#pragma once

enum class RibbyState
{
	Intro,
	Intro_Loop,
	Intro_End,
	Idle,
	Roll_Intro,
	Roll_Intro_Loop,
	Roll_Loop,
	Roll_End,
	FistAttack_Intro,
	FistAttack_Loop,
	FistAttack_End,
	ClapAttack_Intro,
	ClapAttack_Boil,
	ClapAttack,
	ClapAttack_End,
};

// Ό³Έν :
class Ribby : public GameEngineActor
{
public:
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
		GetRibbyHP();
	}

	float GetRibbyHP()
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
	float HP = 500;

	bool IsStageEnd = false;
	bool IsDebugRender = false;
	bool IsBlink = false;

	void ActorInitSetting();
	void DirectCheck();
	void CollisionCheck();
	void HitBlink(float _DeltaTime);

	float BlinkTime = 0.0f;
	float OriginMulColor = 0.0f;
	float BlinkMulColor = 0.0f;
	int BlinkCount = 1;

	RibbyState StateValue = RibbyState::Intro;

	float IntroLoopTime = 0.0f;

	bool IsIntro = true;
	bool Directbool = false;

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

	void Roll_IntroStart();
	void Roll_IntroUpdate(float _DeltaTime);
	void Roll_IntroEnd();

	void Roll_Intro_LoopStart();
	void Roll_Intro_LoopUpdate(float _DeltaTime);
	void Roll_Intro_LoopEnd();

	void Roll_LoopStart();
	void Roll_LoopUpdate(float _DeltaTime);
	void Roll_LoopEnd();

	void Roll_EndStart();
	void Roll_EndUpdate(float _DeltaTime);
	void Roll_EndEnd();

	void FistAttack_IntroStart();
	void FistAttack_IntroUpdate(float _DeltaTime);
	void FistAttack_IntroEnd();

	void FistAttack_EndStart();
	void FistAttack_EndUpdate(float _DeltaTime);
	void FistAttack_EndEnd();

	void FistAttack_LoopStart();
	void FistAttack_LoopUpdate(float _DeltaTime);
	void FistAttack_LoopEnd();

	void ClapAttack_IntroStart();
	void ClapAttack_IntroUpdate(float _DeltaTime);
	void ClapAttack_IntroEnd();

	void ClapAttack_BoilStart();
	void ClapAttack_BoilUpdate(float _DeltaTime);
	void ClapAttack_BoilEnd();

	void ClapAttackStart();
	void ClapAttackUpdate(float _DeltaTime);
	void ClapAttackEnd();

	void ClapAttack_EndStart();
	void ClapAttack_EndUpdate(float _DeltaTime);
	void ClapAttack_EndEnd();
};

