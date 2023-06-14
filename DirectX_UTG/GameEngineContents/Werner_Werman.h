#pragma once

enum class MouseState
{
	Intro,

	MouseIn,
	MouseOut,
	Idle,

	Move,
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
	Loop,
	Fire,
};

// Ό³Έν :
class Werner_Werman : public GameEngineActor
{
public:
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

	std::shared_ptr<class GameEngineSpriteRenderer> BodyCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> EXCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> BodyCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> EXCollisionPtr = nullptr;

	void ActorInitSetting();
	void DirectCheck();
	void CollisionCheck();
	void CollisionSetting();
	void HitBlink(float _DeltaTime);

	float HP = 100.0f;
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

	void ChangeState(MouseState _StateValue);
	void UpdateState(float _DeltaTime);

	void SetIntroMouseUpTexture();
	void SetIntroCanUpTexture();
	void SetIntroCanBackTexture();
	void SetMouseInCanBackTexture();
	void SetMouseOutCanBackTexture();
	void SetMoveCanBackTexture();

	float4 InitPosition = float4::Zero;

	bool IsIntro = true;
	bool Directbool = false;
	bool WeaponType = true;
	bool IsFire = false;
	bool CannonAble = false;

	float DelayTime = 0.0f;
	float MoveTime = 0.0f;
	float FireTime = 0.0f;
	float WeaponSwapTime = 0.0f;

	int CannonfireCount = 0;

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

};

