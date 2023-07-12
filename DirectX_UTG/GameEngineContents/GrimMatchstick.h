#pragma once

enum class DragonState
{
	Intro,
	Idle,

	Meteor_Intro,
	Meteor_Intro_Loop,
	Meteor_Shoot,
	Meteor_Shoot_LollBack,
	Meteor_Outro,

	Peashoot_Intro,
	Peashoot_Shoot,
	Peashoot_Shoot_Plus,
	Peashoot_Outro,

	Ph2_Intro_Loop,
	Ph2_Intro,
	Ph2_Idle,
	Ph2_Death,
};

enum class FireRenderState
{
	Object_Fire_Waiting,

	Object_Fire_Intro,
	Object_Fire_Loop,
	Object_Fire_Outro,

	Object_FireSmoke_Intro,
	Object_FireSmoke_Loop,
	Object_FireSmoke_Outro,
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

	bool GetIsStageEnd()
	{
		return IsStageEnd;
	}

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
	std::shared_ptr<class GameEngineSpriteRenderer> UpRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> EyeRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> FireRenderPtr = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> BodyCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> EXCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Plus_BodyCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Plus_EXCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> FireCollisionRenderPtr = nullptr;

	std::shared_ptr<class GameEngineCollision> BodyCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> EXCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> Plus_BodyCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> Plus_EXCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> FireCollisionPtr = nullptr;

	float HP = 405.0f;
	bool IsDebugRender = false;
	bool IsStageEnd = false;
	bool IsBlink = false;

	float4 OriginMulColor = float4::Zero;
	float4 BlinkMulColor = float4::Zero;
	float BlinkTime = 0.0f;
	int BlinkCount = 1;

	float SpawnDelayTime = 0.0f;

	bool IsSpawn = false;
	bool Directbool = false;

	void ActorInitSetting();
	void HitBlink(float _DeltaTime);
	void CollisionCheck();
	void CollisionSetting();
	void DirectCheck();
	void GetRingAngleWithDotProduct3D();
	void UpRenderSetting();
	void UpRenderSetting_Death();

	float4 RingProjectilePostion = float4::Zero;
	float4 InitPosition = float4::Zero;
	float4 MoveAccel = float4::Zero;

	float RingRotationZ = 0.0f;
	float RingSpawnDelayTime = 0.0f;
	float TailSpawnTime = 6.0f;
	float FireWaitingTime = 0.0f;
	float FireWorkSpawnDelayTime = 0.0f;
	float ExplosionTime = 0.0f;
	bool IsTailSpawn = false;
	bool RingReverse = false;
	bool RingCreate = false;
	bool Ph2FireSetting = false;
	bool Ph2FireWorkInit = false;

	int RingMaxCreateCount = 3;
	int RingCreateCount = 0;

	void CreateTail(float _DeltaTime);
	void CreateRing(float _DeltaTime);
	void CreateMeteor();
	void CreateFireWork();
	void CreateDeathExplosion(float _DeltaTime);

	DragonState StateValue = DragonState::Idle;
	FireRenderState FireStateValue = FireRenderState::Object_Fire_Intro;

	int ChangeStateCount = 0;
	int MeteorCount = 0;
	int PeashootCount = 0;
	int MeteorMax = 0;
	int PeashootMax = 0;

	void Phase1_ChangeStateCountFunction();
	void Phase1_MeteorCountFunction();
	void Phase1_PeashootCountFunction();
	void Phase1_MeteorMaxCountFunction();
	void Phase1_PeashootMaxCountFunction();

	void ChangeState(DragonState _StateValue);
	void UpdateState(float _DeltaTime);

	void IntroStart();
	void IntroUpdate(float _DeltaTime);
	void IntroEnd();

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void Meteor_IntroStart();
	void Meteor_IntroUpdate(float _DeltaTime);
	void Meteor_IntroEnd();

	void Meteor_Intro_LoopStart();
	void Meteor_Intro_LoopUpdate(float _DeltaTime);
	void Meteor_Intro_LoopEnd();

	void Meteor_ShootStart();
	void Meteor_ShootUpdate(float _DeltaTime);
	void Meteor_ShootEnd();

	void Meteor_Shoot_LollBackStart();
	void Meteor_Shoot_LollBackUpdate(float _DeltaTime);
	void Meteor_Shoot_LollBackEnd();

	void Meteor_OutroStart();
	void Meteor_OutroUpdate(float _DeltaTime);
	void Meteor_OutroEnd();

	void Peashoot_IntroStart();
	void Peashoot_IntroUpdate(float _DeltaTime);
	void Peashoot_IntroEnd();

	void Peashoot_ShootStart();
	void Peashoot_ShootUpdate(float _DeltaTime);
	void Peashoot_ShootEnd();

	void Peashoot_Shoot_PlusStart();
	void Peashoot_Shoot_PlusUpdate(float _DeltaTime);
	void Peashoot_Shoot_PlusEnd();

	void Peashoot_OutroStart();
	void Peashoot_OutroUpdate(float _DeltaTime);
	void Peashoot_OutroEnd();

	void Ph2_Intro_LoopStart();
	void Ph2_Intro_LoopUpdate(float _DeltaTime);
	void Ph2_Intro_LoopEnd();

	void Ph2_IntroStart();
	void Ph2_IntroUpdate(float _DeltaTime);
	void Ph2_IntroEnd();

	void Ph2_IdleStart();
	void Ph2_IdleUpdate(float _DeltaTime);
	void Ph2_IdleEnd();

	void Ph2_DeathStart();
	void Ph2_DeathUpdate(float _DeltaTime);
	void Ph2_DeathEnd();

	void ChangeState_FireRender(FireRenderState _StateValue);
	void UpdateState_FireRender(float _DeltaTime);

	void Object_Fire_WaitingStart();
	void Object_Fire_WaitingUpdate(float _DeltaTime);
	void Object_Fire_WaitingEnd();

	void Object_Fire_IntroStart();
	void Object_Fire_IntroUpdate(float _DeltaTime);
	void Object_Fire_IntroEnd();

	void Object_Fire_LoopStart();
	void Object_Fire_LoopUpdate(float _DeltaTime);
	void Object_Fire_LoopEnd();

	void Object_Fire_OutroStart();
	void Object_Fire_OutroUpdate(float _DeltaTime);
	void Object_Fire_OutroEnd();

	void Object_FireSmoke_IntroStart();
	void Object_FireSmoke_IntroUpdate(float _DeltaTime);
	void Object_FireSmoke_IntroEnd();

	void Object_FireSmoke_LoopStart();
	void Object_FireSmoke_LoopUpdate(float _DeltaTime);
	void Object_FireSmoke_LoopEnd();

	void Object_FireSmoke_OutroStart();
	void Object_FireSmoke_OutroUpdate(float _DeltaTime);
	void Object_FireSmoke_OutroEnd();
};

