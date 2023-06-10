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

	Slot_Morph_Intro,
	Slot_Morph_Intro_Loop,
	Slot_Morph_Outro,

	Slot_InitialOpen,
	Slot_Idle,
	Slot_ArmMove_Intro,
	Slot_ArmMove_Loop,
	Slot_ArmMove_Outro,

	Slot_Attack_Intro,
	Slot_Attack_Loop,
	Slot_Attack_Outro,

	Slot_Death_Intro,
	Slot_Death_Loop,
};

// 설명 :
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

	void SetInitReset();

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
	std::shared_ptr<class GameEngineSpriteRenderer> WindRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> SlotMouthRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> SlotFrontRenderPtr = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> SlotImageBackRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> SlotImageRenderPtr0 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> SlotImageRenderPtr1 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> SlotImageRenderPtr2 = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> BodyCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> EXCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> PlusBodyCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> PlusEXCollisionRenderPtr = nullptr;

	std::shared_ptr<class GameEngineCollision> BodyCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> EXCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> PlusBodyCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> PlusEXCollisionPtr = nullptr;

	std::shared_ptr<class GameEngineCollision> ParryCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> ParryCollisionRenderPtr = nullptr;
	
	float MoveAbleTime = 0.0f;
	float HP = 1000;

	bool IsStageEnd = false;
	bool IsDebugRender = false;
	bool IsBlink = false;
	
	void RulletImageBlink(float _DeltaTime);
	void RulletActivate(float _DeltaTime);
	void CoinAttack(float _DeltaTime);
	void ActorInitSetting();
	void CollisionSetting();
	void CollisionCheck();
	void HitBlink(float _DeltaTime);
	void CreateFirefly();
	void CreateFrontDust();
	void CreateCoinProjectile();
	void CreatePlatform_Vipor(float _DeltaTime);
	void CreatePlatform_Bison(float _DeltaTime);
	void CreatePlatform_Tiger(float _DeltaTime);
	void CreateDeathExplosion(float _DeltaTime);

	float4 OriginMulColor = float4::Zero;
	float4 BlinkMulColor = float4::Zero;
	float BlinkTime = 0.0f;

	int BlinkCount = 1;

	CroakState StateValue = CroakState::Intro;

	float4 SlotViporPosition0 = float4::Zero;
	float4 SlotViporPosition1 = float4::Zero;
	float4 SlotViporPosition2 = float4::Zero;

	float4 SlotBisonPosition0 = float4::Zero;
	float4 SlotBisonPosition1 = float4::Zero;
	float4 SlotBisonPosition2 = float4::Zero;

	float4 SlotTigerPosition0 = float4::Zero;
	float4 SlotTigerPosition1 = float4::Zero;
	float4 SlotTigerPosition2 = float4::Zero;

	float4 LowerLimit = float4::Zero;

	float RulletDelayTime = 0.0f;
	float RulletSelectDelayTime = 0.0f;
	float ImageBlinkTime = 0.0f;
	float WaveTime0 = 0.0f;
	float WaveTime1 = 0.0f;
	float WaveTime2 = 0.0f;

	bool IsRulletActivate = false;
	bool RulletActivateEnd = false;
	bool IsVipor = false;
	bool IsBison = false;
	bool IsTiger = false;
	bool RulletWave0 = false;
	bool RulletWave1 = false;
	bool RulletWave2 = false;

	int RulletSelectCount = 1;
	int ImageBlinkCount = 0;

	float IntroLoopTime = 0.0f;
	float IdleDelayTime = 0.0f;
	float CreateMob_LoopTime = 0.0f;
	float AFanLoopTime = 0.0f;
	float BFanLoopTime = 0.0f;
	float MorphDealyTime = 0.0f;
	float CoinAttackTime = 0.0f;
	float ExplosionTime = 0.0f;

	float RulletTime = 0.0f; // 임시
	float RulletLoopTime = 0.0f; // 임시

	int CreatePlus = 0;
	int CreateMobCount = 0;
	int CreateCoinCount = 0;

	bool IsIntro = true;
	bool IsCreatefly = false;
	bool CreateAction = false;
	bool CreateLoop = false;
	bool LoopCreateAction = false;
	bool LoopCreateEnd = false;
	bool IsMorph = false;
	bool SlotInvincibility = false;
	bool IsRullet = false;
	bool IsArmParry = false;

	int RibbyFistCount = 0;
	int CroakCrateMobCount = 0;
	int MaxPatternCount = 2;
	int RollPatter = 0;
	int SlotPositionFix = 1;

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

	void Slot_Morph_IntroStart();
	void Slot_Morph_IntroUpdate(float _DeltaTime);
	void Slot_Morph_IntroEnd();

	void Slot_Morph_Intro_LoopStart();
	void Slot_Morph_Intro_LoopUpdate(float _DeltaTime);
	void Slot_Morph_Intro_LoopEnd();

	void Slot_Morph_OutroStart();
	void Slot_Morph_OutroUpdate(float _DeltaTime);
	void Slot_Morph_OutroEnd();

	void Slot_InitialOpenStart();
	void Slot_InitialOpenUpdate(float _DeltaTime);
	void Slot_InitialOpenEnd();

	void Slot_ArmMove_IntroStart();
	void Slot_ArmMove_IntroUpdate(float _DeltaTime);
	void Slot_ArmMove_IntroEnd();

	void Slot_ArmMove_LoopStart();
	void Slot_ArmMove_LoopUpdate(float _DeltaTime);
	void Slot_ArmMove_LoopEnd();

	void Slot_ArmMove_OutroStart();
	void Slot_ArmMove_OutroUpdate(float _DeltaTime);
	void Slot_ArmMove_OutroEnd();

	void Slot_IdleStart();
	void Slot_IdleUpdate(float _DeltaTime);
	void Slot_IdleEnd();

	void Slot_Attack_IntroStart();
	void Slot_Attack_IntroUpdate(float _DeltaTime);
	void Slot_Attack_IntroEnd();

	void Slot_Attack_LoopStart();
	void Slot_Attack_LoopUpdate(float _DeltaTime);
	void Slot_Attack_LoopEnd();

	void Slot_Attack_OutroStart();
	void Slot_Attack_OutroUpdate(float _DeltaTime);
	void Slot_Attack_OutroEnd();

	void Slot_Death_IntroStart();
	void Slot_Death_IntroUpdate(float _DeltaTime);
	void Slot_Death_IntroEnd();

	void Slot_DeathStart();
	void Slot_DeathUpdate(float _DeltaTime);
	void Slot_DeathEnd();
};

