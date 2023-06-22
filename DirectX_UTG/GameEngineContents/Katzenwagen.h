#pragma once

enum class KatzenwagenState
{
	Intro,
	Idle,
	ArmAttack_Intro,
	ArmAttack_Loop,
	ArmAttack_Outro,
	
	GhostSpawn_Intro,
	GhostSpawn_Loop,
	GhostSpawn_Outro,

	Death,
};

enum class AttackHandState
{
	Intro,
	Loop,
	Hit,
	Outro,
};

// Ό³Έν :
class Katzenwagen : public GameEngineActor
{
	friend class Werner_Werman;

public:
	static Katzenwagen* KatzenwagenPtr;

	// constrcuter destructer
	Katzenwagen();
	~Katzenwagen();

	// delete Function
	Katzenwagen(const Katzenwagen& _Other) = delete;
	Katzenwagen(Katzenwagen&& _Other) noexcept = delete;
	Katzenwagen& operator=(const Katzenwagen& _Other) = delete;
	Katzenwagen& operator=(Katzenwagen&& _Other) noexcept = delete;

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
	std::shared_ptr<class GameEngineSpriteRenderer> HeadRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> HeadParent = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BodyRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BodyUpRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> RightHandRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> LeftHandRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> AttackHandRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> TailHandRenderPtr = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> BodyCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> EXCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> AttackCollisionRenderPtr = nullptr;

	std::shared_ptr<class GameEngineCollision> BodyCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> EXCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> AttackCollisionPtr = nullptr;

	std::shared_ptr<class GhostMouse> GhostMouse_One = nullptr;
	std::shared_ptr<class GhostMouse> GhostMouse_Two = nullptr;

	bool IsDebugRender = false;
	bool IsBlink = false;
	bool IsIntro = false;

	float4 OriginMulColor = float4::Zero;
	float4 BlinkMulColor = float4::Zero;
	float BlinkTime = 0.0f;
	int BlinkCount = 1;

	void GhostMouseAttackSetting(float _DeltaTime);
	void DebugSetting();
	void ActorInitSetting();
	void CollisionCheck();
	void HitBlink(float _DeltaTime);
	void CollisionSetting();

	float4 CurHeadPosition = float4::Zero;
	float4 LerpPosition = float4::Zero;
	float4 CurHeadPosition2 = float4::Zero;
	float4 LerpPosition2 = float4::Zero;
	
	float4 InitHandPosition = float4::Zero;
	float4 CurHandPosition = float4::Zero;

	bool Directbool = false;
	bool IsLeft = false;
	bool IsRight = false;
	bool IsClawAttackEnd = false;
	bool IsWoodCreate_Left = false;
	bool IsWoodCreate_Right = false;
	bool IsGhostMouseCreate = false;
	bool GhostMouse_One_IsDeath = false;
	bool GhostMouse_Two_IsDeath = false;
	bool IsTurn = false;

	float AttactDelayTime = 0.0f;
	float HandAttactTime = 0.0f;
	float HandIntroDelayTime = 0.0f;
	float HandSpeed = 0.0f;
	float WoodCreateTime_Left = 0.0f;
	float WoodCreateTime_Right = 0.0f;
	float ExplosionTime = 0.0f;
	float GhostAttackTime = 0.0f;

	int InitSetting = 1;
	int HandAttackCount = 0;
	int ClawCreateCount = 1;
	int WoodPieceCount_Left = 0;
	int WoodPieceCount_Right = 0;
	int CreateGhostMouseCount = 1;

	void CreateGhostMouse();
	void CreateDeathExplosion(float _DeltaTime);
	void CreateDeathDust();
	void CreateWoodPiece_Left(float _DeltaTime);
	void CreateWoodPiece_Right(float _DeltaTime);
	void IntroAnimationSetting();
	void IntroWallBrake();
	void IntroMouseOff();
	void IntroHeadPositionSetting();
	void HandAttackCountFunction();
	void HandAttackShake();
	void DeathHeadObjectLoopAnimation();

	KatzenwagenState StateValue = KatzenwagenState::Idle;
	AttackHandState AttackHandStateValue = AttackHandState::Intro;

	void ChangeState(KatzenwagenState _StateValue);
	void UpdateState(float _DeltaTime);

	void IntroStart();
	void IntroUpdate(float _DeltaTime);
	void IntroEnd();

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void ArmAttack_IntroStart();
	void ArmAttack_IntroUpdate(float _DeltaTime);
	void ArmAttack_IntroEnd();

	void ArmAttack_LoopStart();
	void ArmAttack_LoopUpdate(float _DeltaTime);
	void ArmAttack_LoopEnd();

	void ArmAttack_OutroStart();
	void ArmAttack_OutroUpdate(float _DeltaTime);
	void ArmAttack_OutroEnd();

	void ChangeState_AttackHand(AttackHandState _StateValue);
	void UpdateState_AttackHand(float _DeltaTime);

	void AttackHand_IntroStart();
	void AttackHand_IntroUpdate(float _DeltaTime);
	void AttackHand_IntroEnd();

	void AttackHand_LoopStart();
	void AttackHand_LoopUpdate(float _DeltaTime);
	void AttackHand_LoopEnd();

	void AttackHand_HitStart();
	void AttackHand_HitUpdate(float _DeltaTime);
	void AttackHand_HitEnd();

	void AttackHand_OutroStart();
	void AttackHand_OutroUpdate(float _DeltaTime);
	void AttackHand_OutroEnd();

	void GhostSpawn_IntroStart();
	void GhostSpawn_IntroUpdate(float _DeltaTime);
	void GhostSpawn_IntroEnd();

	void GhostSpawn_LoopStart();
	void GhostSpawn_LoopUpdate(float _DeltaTime);
	void GhostSpawn_LoopEnd();

	void GhostSpawn_OutroStart();
	void GhostSpawn_OutroUpdate(float _DeltaTime);
	void GhostSpawn_OutroEnd();

	void DeathStart();
	void DeathUpdate(float _DeltaTime);
	void DeathEnd();
};

