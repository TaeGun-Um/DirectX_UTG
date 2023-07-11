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
	Portal,
	Death,
	ElderKettleMove,
	ElderKettleIdle,
	ElderKettleInterAction,
	Intro,
	FallPoint,
};

// 설명 : Field 플레이어
class Player : public PlayerDataBase
{
	friend class TransformGUI;
	friend class CardUI;
	friend class HealthUI;
	friend class WeaponUI;

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

	void SetHitJump()
	{
		IsHitJump = true;
	}

	void SetIsDragonSetting()
	{
		IsDragonSetting = true;
	}

	bool GetIsIntro()
	{
		return IsIntro;
	}

	bool GetIsBottomJump()
	{
		return IsBottomJump;
	}

	void SetElderKettleInterAction(bool _Is)
	{
		ElderKettleInterAction = _Is;
	}

	void SetElderKettleInterActioning(bool _Is)
	{
		ElderKettleInterActioning = _Is;
	}

	void SetIsWattingRoomIntroTrue()
	{
		IsWattingRoomIntro = true;
	}

	void SetPopInterAction()
	{
		PopInterAction = true;
	}

	void SetParryOn()
	{
		ParryCheck = true;
		CreateParryEffect();
		AddPlayerEXStack();
	}

	void SetSpringOn()
	{
		ParryCheck = true;
		IsSpringParry = true;
		CreateParryEffect();
		AddPlayerEXStack();
	}

	void StartCameraShaking(int _ShakingMaxCount)
	{
		ShakingMaxCount = _ShakingMaxCount;
		IsCameraShaking = true;
	}

	void SetStageEndHP()
	{
		StageEndHPMax = true;
	}

	void MoveAbleTimeReset()
	{
		MoveAbleTime = 0.0f;
	}

	float GetMoveAbelTime()
	{
		return MoveAbleTime;
	}

	void PlayerReset();

	void SetIntro()
	{
		IsIntro = true;
	}

	bool GetPlatformCheckAble()
	{
		return PlatformCheckAble;
	}

	void SetBottomJumpBlock()
	{
		BottomJumpBlock = true;
	}

	void SetBottomJumpBlockOff()
	{
		BottomJumpBlock = false;
	}

	bool GetIsPlayerDeath()
	{
		return IsPlayerDeath;
	}

	bool GetIsElderKettleEnd()
	{
		return IsElderKettleEnd;
	}

	void SetCorrectionFalse()
	{
		IsCorrection = false;
	}

	bool GetParryCheck()
	{
		return ParryCheck;
	}

	void PlayerDebugRenderOn()
	{
		IsDebugRender = true;
	}

	void PlayerDebugRenderOff()
	{
		IsDebugRender = false;
	}

	// 픽셀 충돌 설정
	void SetColMap(const std::shared_ptr<GameEngineTexture>& _ColMap, PixelCollision::Coordinate _Pivot)
	{
		PixelCollisionCheck.SetColMap(_ColMap, _Pivot);
		ColMap = _ColMap;
		Pivot = _Pivot;

		ColMapHegiht_Half = PixelCollisionCheck.GetColMapHeight_Half();
		ColMapWidth_Half = PixelCollisionCheck.GetColMapWidth_Half();
	}

	std::shared_ptr<GameEngineTexture> GetColMap()
	{
		return ColMap;
	}

	bool GetPlayerPortalAble()
	{
		return PortalAble;
	}

	bool GetPlayerPortaling()
	{
		return Portaling;
	}

	std::shared_ptr<class GameEngineSpriteRenderer> GetPlayerMainRenderPtr()
	{
		return RenderPtr;
	}

	void MinusPlayerHP();
	void AddPlayerEXStack();
	void AddPlayerEXGauge_Peashooter();
	void AddPlayerEXGauge_Spread();
	void CheckPlayerEXGauge();

	void PlayerMoveDisturbance(float _Value);
	void PlayerBlockDisturbance(float _Value);

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
	std::shared_ptr<class GameEngineSpriteRenderer> FrontSensorCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> ParryCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> BodyCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> StandCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> BottomSensorCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> FrontSensorCollisionPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> ParryCollisionPtr = nullptr;
	
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr0 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr1 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr2 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr3 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr4 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr5 = nullptr;

	bool IsDebugRender = false;
	bool IsCorrection = false;

	// Init
	void SetPlayerHP(int _HP)
	{
		PlayerHP = _HP;
	}

	void SetPlayerEXGauge(float _EXGauge)
	{
		PlayerEXGauge = _EXGauge;
	}

	void SetPlayerEXStack(int _EXStack)
	{
		PlayerEXStack = _EXStack;
	}

	int PlayerHP = 0;
	float MaxEXGauge = 50;
	float PlayerEXGauge = 0;
	int PlayerEXStack = 0;

	void PlayerInitialSetting();
	void PlayerCollisionSetting();
	void DebugRendererSetting();

	float OriginMulColor = 0.0f;
	float BlinkMulColor = 0.0f;
	float Inter = 0.5f;

	bool MulColorCheck = false;
	bool IsHPMax = false;
	bool IsEXMax = false;
	bool IsEXUse = false;
	bool StageEndHPMax = false;
	bool IsWeaponChange = false;

	// Assistant
	void CheatKey();
	void PositionCorrection();
	void DragonSetting();
	void PlayerDebugRenderer();
	void HitBlink(float _DeltaTime);
	void PortalCheck();
	void HitAnimationBindFunction();

	// 픽셀, 충돌체 체크 모음
	void CollisionCalculation(float _DeltaTime);

	// 픽셀체크
	void WallCheck(const GameEnginePixelColor& _LeftWallMapPixel, const GameEnginePixelColor& _RightWallMapPixel, float _DeltaTime);
	void DisturbanceWallCheck(const GameEnginePixelColor& _LeftWallMapPixel, const GameEnginePixelColor& _RightWallMapPixel, float _DeltaTime, float _Value);
	void PixelCheck(float _DeltaTime);
	
	std::shared_ptr<GameEngineTexture> ColMap = nullptr;
	PixelCollision::Coordinate Pivot = PixelCollision::Coordinate::WindowOrigin;
	PixelCollision PixelCollisionCheck;

	// 콜리전 체크
	void CollisionSetting();
	void PlatformBottomJump(float _DeltaTime);
	void PlatformBottomJumpStateCheck(float _DeltaTime);
	void HitCollisionCheck(float _DeltaTime);
	void FallCollisionCheck(float _DeltaTime);
	void WallCollisionCheck(float _DeltaTime);

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
	void CreateHitEffect();
	void CreateGhostEffect();

	int ProjectileSet = 0;

	// FSM
	void DirectCheck();
	void AttackDirectCheck();

	PlayerState StateValue = PlayerState::Idle;
	float4 MoveDirect = float4::Zero;

	bool Directbool = true;    // true == 오른쪽 // false == 왼쪽
	bool WeaponType = true;    // true : Peashooter // false : Spread

	bool IsDragonSetting = false; // DragonLevel에서만 사용

	// Air
	bool IsJump = false;
	bool IsFall = false;
	bool PlatformCheckAble = false;
	bool IsSlap = false;
	bool SlapJump = false;
	bool ParryCheck = false;
	bool IsSpringParry = false;
	bool OuterParryCheck = false;
	bool IsBottomJump = false;
	bool BottomJumpBlock = false;
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
	bool IsHit = false;
	bool IsHitJump = false;
	bool HitTimeCheck = false;
	bool FallHitTimeCheck = false;
	bool IsDeath = false;
	bool PortalAble = false;
	bool Portaling = false;
	bool IsIntro = false;
	bool IsPlayerDeath = false;

	bool FallHitCheck = true;

	bool ElderKettleInterAction = false;
	bool IsWattingRoomIntro = false;
	bool ElderKettleInterActioning = false;
	bool PopInterAction = false;
	bool IsElderKettleEnd = false;

	float MoveAbleTime = 0.0f;
	float JumpTime = 0.0f;
	float DuckTime = 0.0f;
	float DashTime = 0.0f;
	float ProjectileCreateTime = 0.0f;
	float MoveTime = 0.0f;
	float HitTime = 0.0f;
	float FallHitTime = 0.0f;
	float NormalDeltaTime = 0.0f;
	float FallCheckDelayTime = 0.0f;

	int CreateEXCount = 1;
	int ParryCountSet = 1;
	size_t ParryFrame = 0;

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

	void PortalStart();
	void PortalUpdate(float _DeltaTime);
	void PortalEnd();

	void DeathStart();
	void DeathUpdate(float _DeltaTime);
	void DeathEnd();

	void ElderKettleMoveStart();
	void ElderKettleMoveUpdate(float _DeltaTime);
	void ElderKettleMoveEnd();

	void ElderKettleIdleStart();
	void ElderKettleIdleUpdate(float _DeltaTime);
	void ElderKettleIdleEnd();

	void ElderKettleInterActionStart();
	void ElderKettleInterActionUpdate(float _DeltaTime);
	void ElderKettleInterActionEnd();

	void IntroStart();
	void IntroUpdate(float _DeltaTime);
	void IntroEnd();

	void FallPointStart();
	void FallPointUpdate(float _DeltaTime);
	void FallPointEnd();
};

