#pragma once

#include "PlayerDataBase.h"

enum class OverworldState
{
	Idle,
	Move,
	Win,
};

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

	bool Directbool = true;
	AttackDirection ADValue = AttackDirection::Right_Down;

	void PlayerInitialSetting();
	void DirectCheck();
	void MoveDirectCheck();

	void UpdateState(float _DeltaTime);
	void ChangeState(OverworldState _StateValue);
	OverworldState StateValue = OverworldState::Idle;

	void IdleStart() override;
	void IdleUpdate(float _DeltaTime) override;
	void IdleEnd() override;

	void MoveStart() override;
	void MoveUpdate(float _DeltaTime) override;
	void MoveEnd() override;

	void WinStart();
	void WinUpdate(float _DeltaTime);
	void WinEnd();
};

