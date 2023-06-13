#pragma once

enum class MouseState
{
	Intro,
	Idle,

	Move,
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
	bool IsIntro = true;
	bool Directbool = false;
	bool IsBlink = false;

	float4 OriginMulColor = float4::Zero;
	float4 BlinkMulColor = float4::Zero;
	float BlinkTime = 0.0f;
	int BlinkCount = 1;

	MouseState StateValue = MouseState::Intro;

	void ChangeState(MouseState _StateValue);
	void UpdateState(float _DeltaTime);

	void SetIntroTexture();

	void IntroStart();
	void IntroUpdate(float _DeltaTime);
	void IntroEnd();

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void MoveStart();
	void MoveUpdate(float _DeltaTime);
	void MoveEnd();

};

