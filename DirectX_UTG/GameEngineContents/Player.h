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
};

// ���� : Field �÷��̾�
class Player : public PlayerDataBase
{
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
	
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr0 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr1 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr2 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr3 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr4 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr5 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DebugRenderPtr6 = nullptr;

	bool IsDebugRender = false;
	bool IsCorrection = false;

	void PositionCorrection();

	// FSM
	PlayerState StateValue = PlayerState::Idle;
	bool Directbool = true; // true == ������ // false == ����

	float JumpTime = 0.0f;
	float DuckTime = 0.0f;
	float DashTime = 0.0f;
	float ProjectileCreateTime = 0.0f;

	enum class AttackDirection
	{
		//Right
		Right_Up,           // 0
		Right_DiagonalUp,   // 1
		Right_Front,        // 2
		Right_DiagonalDown, // 3
		Right_Down,         // 4
		//Left
		Left_Up,            // 5
		Left_DiagonalUp,    // 6
		Left_Front,			// 7
		Left_DiagonalDown,	// 8
		Left_Down,			// 9
	};

	AttackDirection ADValue = AttackDirection::Right_Front;

	void ProjectileCreate(float _DeltaTime);
	void CreatePeashooter();
	void CreatePeashooter_EX();
	void CreateSpread();
	void CreateSpread_EX();
	void CreateEXDust();
	void CreateMoveDust();
	void CreateLandDust();
	void CreateParryEffect();

	void DirectCheck();
	void AttackDirectCheck();
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
};

