#pragma once

#include "PlayerDataBase.h"

enum class PlayerState
{
	Fall,
	Idle,
	Move,
	Dash,
	DuckReady,
	Duck,
	Jump,
	Slap,
	AttackReady,
	Attack,
	RunAttack,
	DuckAttack,
	EXAttack,
	Holding,
	HoldingAttack,
	Hit,
};

// 설명 : Field 플레이어
class Player : public PlayerDataBase
{
	friend class Peashooter;
	friend class Peashooter_EX;
	friend class Spread;
	friend class Spread_EX;

public:
	static Player* MainPlayer;

	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	void PlayerDebugRenderOn()
	{
		IsDebugRender = true;
	}

	void PlayerDebugRenderOff()
	{
		IsDebugRender = false;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> PeashooterRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> ChargeUpRenderPtr = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> BodyCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> StandCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BottomSensorCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> BodyCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> StandCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> BottomSensorCollisionPtr = nullptr;
	
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr0 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr1 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr2 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr3 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr4 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr5 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr6 = nullptr;

	bool IsDebugRender = false;
	bool IsCorrection = false;

	// Init
	void PlayerInitialSetting();
	void PlayerCollisionSetting();
	void DebugRendererSetting();

	// Assistant
	void PositionCorrection();
	void PlayerDebugRenderer();

	// 픽셀, 충돌체 체크 모음
	void CollisionCalculation(float _DeltaTime);

	// 픽셀체크
	void WallCheck(const GameEnginePixelColor& _LeftWallMapPixel, const GameEnginePixelColor& _RightWallMapPixel, float _DeltaTime);
	void PixelCheck(float _DeltaTime);

	// 콜리전 체크
	void CollisionSetting();
	void PlatformBottomJump(float _DeltaTime);
	void PlatformBottomJumpStateCheck(float _DeltaTime);

	// CreateActor
	void ProjectileCreate(float _DeltaTime);
	void EXCreate();
	void CreatePeashooter();
	void CreatePeashooter_EX();
	void CreateSpread();
	void CreateSpread_EX();
	void CreateEXDust();
	void CreateDashDust();
	void CreateMoveDust();
	void CreateParryEffect();
	void CreateLandDust();

	int ProjectileSet = 0;

	// FSM
	void DirectCheck();
	void AttackDirectCheck();

	PlayerState StateValue = PlayerState::Idle;
	float4 MoveDirect = float4::Zero;
	float4 CurrentPlayerPos = float4::Zero;
	float4 PlatformScale = float4::Zero;

	bool Directbool = true;    // true == 오른쪽 // false == 왼쪽

	// Air
	bool IsJump = false;
	bool IsFall = false;
	bool IsSlap = false;
	bool PlatformCheckAble = false;
	bool PlatformFallCheck = false;
	bool PlatformFall = false;
	bool IsBottomJump = false;
	bool BottomJumpAble = false;
	bool AirEXAttackAble = false;
	bool IsDash = false;
	bool AirDash = false;

	bool IsDuck = false;
	bool IsDuckAttack = false;
	bool IsAttackReady = false;
	bool IsHold = false;
	bool IsEXAttack = false;
	bool EXPushBack = false;
	bool PushBackAble = false;

	bool Coll = false;

	float JumpTime = 0.0f;
	float DuckTime = 0.0f;
	float DashTime = 0.0f;
	float ActivateDashTime = 0.0f;
	float ProjectileCreateTime = 0.0f;
	float MoveTime = 0.0f;
	float PlatformHeight = 0.0f;

	int CreateEXCount = 1;
	int FallPosCheck = 1;

	AttackDirection ADValue = AttackDirection::Right_Front;

	void ChangeState(PlayerState _StateValue);
	void UpdateState(float _DeltaTime);

	void FallStart();
	void FallUpdate(float _DeltaTime);
	void FallEnd();

	void IdleStart() override;
	void IdleUpdate(float _DeltaTime) override;
	void IdleEnd() override;

	void MoveStart() override;
	void MoveUpdate(float _DeltaTime) override;
	void MoveEnd() override;

	void DashStart();
	void DashUpdate(float _DeltaTime);
	void DashEnd();

	void DuckReadyStart();
	void DuckReadyUpdate(float _DeltaTime);
	void DuckReadyEnd();

	void DuckStart();
	void DuckUpdate(float _DeltaTime);
	void DuckEnd();

	void JumpStart();
	void JumpUpdate(float _DeltaTime);
	void JumpEnd();

	void SlapStart();
	void SlapUpdate(float _DeltaTime);
	void SlapEnd();

	void AttackReadyStart();
	void AttackReadyUpdate(float _DeltaTime);
	void AttackReadyEnd();

	void AttackStart();
	void AttackUpdate(float _DeltaTime);
	void AttackEnd();

	void RunAttackStart();
	void RunAttackUpdate(float _DeltaTime);
	void RunAttackEnd();

	void DuckAttackStart();
	void DuckAttackUpdate(float _DeltaTime);
	void DuckAttackEnd();

	void EXAttackStart();
	void EXAttackUpdate(float _DeltaTime);
	void EXAttackEnd();

	void HoldingStart();
	void HoldingUpdate(float _DeltaTime);
	void HoldingEnd();

	void HoldingAttackStart();
	void HoldingAttackUpdate(float _DeltaTime);
	void HoldingAttackEnd();

	void HitStart();
	void HitUpdate(float _DeltaTime);
	void HitEnd();
};

