#pragma once

#include "PlayerDataBase.h"

// Ό³Έν :
class Player_Overworld : public PlayerDataBase
{
public:
	static Player_Overworld* MainPlayer;

	// constrcuter destructer
	Player_Overworld();
	~Player_Overworld();

	// delete Function
	Player_Overworld(const Player_Overworld& _Other) = delete;
	Player_Overworld(Player_Overworld&& _Other) noexcept = delete;
	Player_Overworld& operator=(const Player_Overworld& _Other) = delete;
	Player_Overworld& operator=(Player_Overworld&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr;

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

