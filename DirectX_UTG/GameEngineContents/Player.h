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

// 설명 :
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

protected:
	void Start();
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr;

	PlayerState StateValue = PlayerState::Idle;
	bool Directbool = true; // true == 오른쪽 // false == 왼쪽

	void DirectCheck();
	void ChangeState(PlayerState _StateValue);
	void UpdateState(float _DeltaTime);

	void IdleStart() override;
	void IdleUpdate() override;
	void IdleEnd() override;

	void MoveStart() override;
	void MoveUpdate() override;
	void MoveEnd() override;

	void DashStart() override;
	void DashUpdate() override;
	void DashEnd() override;

	void DuckStart() override;
	void DuckUpdate() override;
	void DuckEnd() override;

	void JumpStart() override;
	void JumpUpdate() override;
	void JumpEnd() override;

	void SlapStart() override;
	void SlapUpdate() override;
	void SlapEnd() override;

	void AttackStart() override;
	void AttackUpdate() override;
	void AttackEnd() override;

	void RunAttackStart() override;
	void RunAttackUpdate() override;
	void RunAttackEnd() override;

	void EXAttackStart() override;
	void EXAttackUpdate() override;
	void EXAttackEnd() override;

	void HoldingStart() override;
	void HoldingUpdate() override;
	void HoldingEnd() override;
};

