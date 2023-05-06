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

	void PlayerMove_Overworld(float _DeltaTime);

	void IdleStart() override;
	void IdleUpdate(float _DeltaTime) override;
	void IdleEnd() override;

	void MoveStart() override;
	void MoveUpdate(float _DeltaTime) override;
	void MoveEnd() override;
};

