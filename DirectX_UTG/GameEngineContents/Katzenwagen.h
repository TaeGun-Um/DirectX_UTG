#pragma once

enum class KatzenwagenState
{
	Intro,
	Idle,
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
	std::shared_ptr<class GameEngineSpriteRenderer> TailHandRenderPtr = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> BodyCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> EXCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> AttackCollisionRenderPtr = nullptr;

	std::shared_ptr<class GameEngineCollision> BodyCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> EXCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> AttackCollisionPtr = nullptr;

	bool IsDebugRender = false;
	bool IsBlink = false;
	bool IsIntro = false;

	float4 OriginMulColor = float4::Zero;
	float4 BlinkMulColor = float4::Zero;
	float BlinkTime = 0.0f;
	int BlinkCount = 1;

	void ActorInitSetting();
	void CollisionCheck();
	void HitBlink(float _DeltaTime);
	void DirectCheck();
	void CollisionSetting();

	bool Directbool = false;

	int InitSetting = 1;

	void IntroAnimationSetting();
	void IntroWallBrake();
	void IntroMouseOff();
	void IntroHeadPositionSetting();

	KatzenwagenState StateValue = KatzenwagenState::Idle;

	void ChangeState(KatzenwagenState _StateValue);
	void UpdateState(float _DeltaTime);

	void IntroStart();
	void IntroUpdate(float _DeltaTime);
	void IntroEnd();

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();
};

