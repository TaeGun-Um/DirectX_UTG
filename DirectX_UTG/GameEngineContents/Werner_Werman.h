#pragma once

enum class MouseState
{
	Intro,

	MouseIn,
	MouseOut,
	Idle,
	Move,

	Dash_Intro,
	Dash,
	Dash_Outro,

	//Phase2
	Explosion_Intro,
	Explosion_Loop,
	Explosion,

	Idle_Phase2
};

enum class CannonState
{
	Out,
	Idle,
	Fire,
	In,
};

enum class CatapultState
{
	Out,
	Loop,
	Reload,
	Reload_Loop,
	Fire,
	In,
};

enum class Phase2State
{
	Intro,
	TransA,
	TransB,
	Trans_LoopB,
	TransC,
	TransD,
	Trans_LoopD,
};

enum class ScissorState
{
	Scissor_Intro,
	Down,
	Down_Loop,
	Up,
	Up_Loop,
};

enum class WheelState
{
	Intro,
	LeftMove,
	LeftMove_Loop,
	RightMove,
	RightMove_Loop,
};

// Ό³Έν :
class Werner_Werman : public GameEngineActor
{
public:
	static Werner_Werman* WernerWermanPtr;

	// constrcuter destructer
	Werner_Werman();
	~Werner_Werman();

	// delete Function
	Werner_Werman(const Werner_Werman& _Other) = delete;
	Werner_Werman(Werner_Werman&& _Other) noexcept = delete;
	Werner_Werman& operator=(const Werner_Werman& _Other) = delete;
	Werner_Werman& operator=(Werner_Werman&& _Other) noexcept = delete;

	bool GetIsStageEnd()
	{
		return IsStageEnd;
	}

	float GetPhase2MoveDistance()
	{
		return Phase2MoveDistance;
	}

	//void SetInitReset();

	void SetInitPosition(float4 _Value)
	{
		InitPosition = _Value;
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

	void SetIsFlameEnd()
	{
		IsFlameEnd = true;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> CanRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> CanBackRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> CanUpRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> MouseRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> WeaponRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> MouseUpRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> WheelRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> FlamecannonRenderPtr_Right = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> FlamecannonRenderPtr_Left = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Phase2Parent = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> BodyCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> EXCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> PlatformCollisionRenderPtr = nullptr;

	std::shared_ptr<class GameEngineCollision> BodyCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> EXCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> PlatformCollisionPtr = nullptr;

	void ActorInitSetting();
	void DirectCheck();
	void CollisionCheck();
	void PlatformCollisionCheck(float _Value);
	void CollisionSetting();
	void HitBlink(float _DeltaTime);
	void CreateCherryBomb();
	void CreateCatapultProjectile();
	void CreateSpringObject();
	void CreateExplosionSFX();
	void CreateFlamethrower();

	float HP = 1000.0f;
	bool IsDebugRender = false;
	bool IsStageEnd = false;
	bool IsBlink = false;

	float4 OriginMulColor = float4::Zero;
	float4 BlinkMulColor = float4::Zero;
	float BlinkTime = 0.0f;
	int BlinkCount = 1;

	MouseState StateValue = MouseState::Idle;
	CannonState CannonStateValue = CannonState::Out;
	CatapultState CatapultStateValue = CatapultState::Loop;
	Phase2State Phase2StateValue = Phase2State::Intro;
	ScissorState ScissorStateValue = ScissorState::Scissor_Intro;
	WheelState WheelStateValue = WheelState::Intro;

	void ChangeState(MouseState _StateValue);
	void UpdateState(float _DeltaTime);

	void SetIntroMouseUpTexture();
	void SetIntroCanUpTexture();
	void SetIntroCanBackTexture();
	void SetMouseInCanBackTexture();
	void SetMouseOutCanBackTexture();
	void SetMoveCanBackTexture();
	void SetCanTinBackTexture();

	float4 FowardPosition = float4::Zero;
	float4 InitPosition = float4::Zero;
	float4 LeftInitPosition = float4::Zero;
	float4 Phase2InitPosition = float4::Zero;
	float4 MoveDistance = float4::Zero;
	float4 CatapultStartPosition = float4::Zero;
	float4 CatapultEndPosition = float4::Zero;
	float4 Phase2IdleDownPosition = float4::Zero;
	float4 Phase2IdleUpPosition = float4::Zero;

	float4 Phase2IdleLeftMovePosition = float4::Zero;
	float4 Phase2IdleRightMovePosition = float4::Zero;

	bool IsIntro = true;
	bool IsShake = false;
	bool Directbool = false;
	bool WeaponType = true;
	bool IsFire = false;
	bool ParryBombCreate = false;
	bool CannonAble = false;
	bool CatapultAble = false;
	bool AlreadyCannonOn = false;
	bool AlreadyCatapultOn = false;
	bool IsDash = false;
	bool IsCreateProjectile = false;
	bool IsCreateCatapultProjectile = false;
	bool IsCreateSpringObject = false;
	bool IsCreateFlamethrower = false;
	bool IsFlameEnd = false;
	bool IsWheelStart = false;

	bool IsPhase2 = false;
	bool Phase2InitCorrection = false;
	bool IsMoveState = false;
	bool IsPhase2UpPosition = false;
	bool IsPhase2DownPosition = false;

	float DelayTime = 0.0f;
	float MoveTime = 0.0f;
	float WeaponSwapTime = 0.0f;
	float CannonFireTime = 0.0f;
	float CatapultLoopTime = 0.0f;
	float CatapultReLoadLoopTime = 0.0f;
	float FireTime = 0.0f;
	float ExplosionLoopTime = 0.0f;
	float MoveLoopTime = 0.0f;
	float MoveDelayTime = 0.0f;
	float Phase2MoveDistance = 0.0f;

	int CannonFireRand = 0;
	int CannonFireCount = 0;
	int CannonFireMaxCount = 0;
	int CannonLoopCount = 0;
	int CatapultFireCount = 0;
	int WeaponSwapCount = 0;
	int Phase2PositionSetting = 1;
	int WheelMoveCount = 1;

	void IntroStart();
	void IntroUpdate(float _DeltaTime);
	void IntroEnd();

	void MouseInStart();
	void MouseInUpdate(float _DeltaTime);
	void MouseInEnd();

	void MouseOutStart();
	void MouseOutUpdate(float _DeltaTime);
	void MouseOutEnd();

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void MoveStart();
	void MoveUpdate(float _DeltaTime);
	void MoveEnd();

	void Dash_IntroStart();
	void Dash_IntroUpdate(float _DeltaTime);
	void Dash_IntroEnd();

	void DashStart();
	void DashUpdate(float _DeltaTime);
	void DashEnd();

	void Dash_OutroStart();
	void Dash_OutroUpdate(float _DeltaTime);
	void Dash_OutroEnd();

	void Explosion_IntroStart();
	void Explosion_IntroUpdate(float _DeltaTime);
	void Explosion_IntroEnd();

	void Explosion_LoopStart();
	void Explosion_LoopUpdate(float _DeltaTime);
	void Explosion_LoopEnd();

	void ExplosionStart();
	void ExplosionUpdate(float _DeltaTime);
	void ExplosionEnd();

	void Idle_Phase2Start();
	void Idle_Phase2Update(float _DeltaTime);
	void Idle_Phase2End();

	void ChangeState_Cannon(CannonState _StateValue);
	void UpdateState_Cannon(float _DeltaTime);

	void Cannon_OutStart();
	void Cannon_OutUpdate(float _DeltaTime);
	void Cannon_OutEnd();

	void Cannon_InStart();
	void Cannon_InUpdate(float _DeltaTime);
	void Cannon_InEnd();

	void Cannon_IdleStart();
	void Cannon_IdleUpdate(float _DeltaTime);
	void Cannon_IdleEnd();

	void Cannon_FireStart();
	void Cannon_FireUpdate(float _DeltaTime);
	void Cannon_FireEnd();

	void ChangeState_Catapult(CatapultState _StateValue);
	void UpdateState_Catapult(float _DeltaTime);

	void Catapult_OutStart();
	void Catapult_OutUpdate(float _DeltaTime);
	void Catapult_OutEnd();

	void Catapult_LoopStart();
	void Catapult_LoopUpdate(float _DeltaTime);
	void Catapult_LoopEnd();

	void Catapult_ReloadStart();
	void Catapult_ReloadUpdate(float _DeltaTime);
	void Catapult_ReloadEnd();

	void Catapult_Reload_LoopStart();
	void Catapult_Reload_LoopUpdate(float _DeltaTime);
	void Catapult_Reload_LoopEnd();

	void Catapult_FireStart();
	void Catapult_FireUpdate(float _DeltaTime);
	void Catapult_FireEnd();

	void Catapult_InStart();
	void Catapult_InUpdate(float _DeltaTime);
	void Catapult_InEnd();

	void ChangeState_Phase2(Phase2State _StateValue);
	void UpdateState_Phase2(float _DeltaTime);

	void Ph2MouseIntroStart();
	void Ph2MouseIntroUpdate(float _DeltaTime);
	void Ph2MouseIntroEnd();

	void TransAStart();
	void TransAUpdate(float _DeltaTime);
	void TransAEnd();

	void TransBStart();
	void TransBUpdate(float _DeltaTime);
	void TransBEnd();

	void Trans_LoopBStart();
	void Trans_LoopBUpdate(float _DeltaTime);
	void Trans_LoopBEnd();

	void TransCStart();
	void TransCUpdate(float _DeltaTime);
	void TransCEnd();

	void TransDStart();
	void TransDUpdate(float _DeltaTime);
	void TransDEnd();

	void Trans_LoopDStart();
	void Trans_LoopDUpdate(float _DeltaTime);
	void Trans_LoopDEnd();

	void ChangeState_Scissor(ScissorState _StateValue);
	void UpdateState_Scissor(float _DeltaTime);

	void Scissor_IntroStart();
	void Scissor_IntroUpdate(float _DeltaTime);
	void Scissor_IntroEnd();

	void DownStart();
	void DownUpdate(float _DeltaTime);
	void DownEnd();

	void Down_LoopStart();
	void Down_LoopUpdate(float _DeltaTime);
	void Down_LoopEnd();

	void UpStart();
	void UpUpdate(float _DeltaTime);
	void UpEnd();

	void Up_LoopStart();
	void Up_LoopUpdate(float _DeltaTime);
	void Up_LoopEnd();

	void ChangeState_Wheel(WheelState _StateValue);
	void UpdateState_Wheel(float _DeltaTime);

	void Wheel_IntroStart();
	void Wheel_IntroUpdate(float _DeltaTime);
	void Wheel_IntroEnd();

	void Wheel_LeftMoveStart();
	void Wheel_LeftMoveUpdate(float _DeltaTime);
	void Wheel_LeftMoveEnd();

	void Wheel_LeftMove_LoopStart();
	void Wheel_LeftMove_LoopUpdate(float _DeltaTime);
	void Wheel_LeftMove_LoopEnd();

	void Wheel_RightMoveStart();
	void Wheel_RightMoveUpdate(float _DeltaTime);
	void Wheel_RightMoveEnd();

	void Wheel_RightMove_LoopStart();
	void Wheel_RightMove_LoopUpdate(float _DeltaTime);
	void Wheel_RightMove_LoopEnd();

};

