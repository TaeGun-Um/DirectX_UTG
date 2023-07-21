#pragma once

enum class GhostState
{
	Intro,
	Idle,
	BlueBallAttack,
	PinkBallAttack,
	AttackOutro,
	Death
};

// Ό³Έν :
class GhostMouse : public GameEngineActor
{
public:
	// constrcuter destructer
	GhostMouse();
	~GhostMouse();

	// delete Function
	GhostMouse(const GhostMouse& _Other) = delete;
	GhostMouse(GhostMouse&& _Other) noexcept = delete;
	GhostMouse& operator=(const GhostMouse& _Other) = delete;
	GhostMouse& operator=(GhostMouse&& _Other) noexcept = delete;

	void SetDirection(bool _Direction)
	{
		if (false == _Direction)
		{
			GetTransform()->SetLocalNegativeScaleX();
			IsIntroSound = true;
		}

		Directbool = _Direction;
	}

	void SetStartPosition(const float4& _PlayerPosition)
	{
		GetTransform()->SetLocalPosition(_PlayerPosition);
		StartPosition = GetTransform()->GetLocalPosition();

		if (true == Directbool)
		{
			LerpPosition = StartPosition + float4{ 280, 85 };
		}
		else
		{
			LerpPosition = StartPosition + float4{ -280, 60 };
		}
	}

	void DebugRenderOn()
	{
		IsDebugRender = true;
	}

	void DebugRenderOff()
	{
		IsDebugRender = false;
	}

	void SetIsAttack()
	{
		IsAttack = true;
	}

	void SetIsDeath()
	{
		IsDeath = true;
	}

	bool GetIsDeath()
	{
		return IsDeath;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	GameEngineSoundPlayer EffectPlayer;

	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BodyCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> EXCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> BodyCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> EXCollisionPtr = nullptr;

	float HP = 70.0f;
	bool IsDebugRender = false;
	bool IsBlink = false;

	float4 OriginMulColor = float4::Zero;
	float4 BlinkMulColor = float4::Zero;
	float BlinkTime = 0.0f;
	int BlinkCount = 1;

	void AttackSound();
	void CollisionCheck();
	void HitBlink(float _DeltaTime);
	void CreateBall(bool _Is);

	GhostState StateValue = GhostState::Intro;

	float4 StartPosition = float4::Zero;
	float4 LerpPosition = float4::Zero;

	bool IsPink = false;
	bool IsDeath = false;
	bool Directbool = false;
	bool IsAttack = false;
	bool IsIntroSound = false;

	float AttackDelayTime = 0.0f;
	float LerpTime = 0.0f;

	void ChangeState(GhostState _StateValue);
	void UpdateState(float _DeltaTime);

	void IntroStart();
	void IntroUpdate(float _DeltaTime);
	void IntroEnd();

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void BlueBallAttackStart();
	void BlueBallAttackUpdate(float _DeltaTime);
	void BlueBallAttackEnd();

	void PinkBallAttackStart();
	void PinkBallAttackUpdate(float _DeltaTime);
	void PinkBallAttackEnd();

	void AttackOutroStart();
	void AttackOutroUpdate(float _DeltaTime);
	void AttackOutroEnd();

	void DeathStart();
	void DeathUpdate(float _DeltaTime);
	void DeathEnd();

};

