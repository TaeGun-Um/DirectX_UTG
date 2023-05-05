#pragma once

#include "PlayerDataBase.h"

enum class PlayerState
{
	Idle,
	Move,
	Dash,
	Duck,
	Jump,
	Slap,
	Attack,
	RunAttack,
	EXAttack,
	Holding
};

// 설명 : Field 플레이어
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

	PlayerState StateValue = PlayerState::Idle;
	bool Directbool = true; // true == 오른쪽 // false == 왼쪽

	float JumpTime = 0.0f;
	float DuckTime = 0.0f;

	void DirectCheck();
	void ChangeState(PlayerState _StateValue);
	void UpdateState(float _DeltaTime);

	void IdleStart() override;
	void IdleUpdate(float _DeltaTime) override;
	void IdleEnd() override;

	void MoveStart() override;
	void MoveUpdate(float _DeltaTime) override;
	void MoveEnd() override;

	void DashStart();
	void DashUpdate(float _DeltaTime);
	void DashEnd();

	void DuckStart();
	void DuckUpdate(float _DeltaTime);
	void DuckEnd();

	void JumpStart();
	void JumpUpdate(float _DeltaTime);
	void JumpEnd();

	void SlapStart();
	void SlapUpdate(float _DeltaTime);
	void SlapEnd();

	void AttackStart();
	void AttackUpdate(float _DeltaTime);
	void AttackEnd();

	void RunAttackStart();
	void RunAttackUpdate(float _DeltaTime);
	void RunAttackEnd();

	void EXAttackStart();
	void EXAttackUpdate(float _DeltaTime);
	void EXAttackEnd();

	void HoldingStart();
	void HoldingUpdate(float _DeltaTime);
	void HoldingEnd();
};

