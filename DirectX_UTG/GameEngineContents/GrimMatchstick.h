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

	std::shared_ptr<class GameEngineSpriteRenderer> BodyCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> EXCollisionRenderPtr = nullptr;

	std::shared_ptr<class GameEngineCollision> BodyCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> EXCollisionPtr = nullptr;

	float HP = 1000.0f;
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

	DragonState StateValue = DragonState::Idle;
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

};

