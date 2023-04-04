#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Player : public GameEngineActor
{
public:
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
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:
	float Angle = 0.0f;
	std::shared_ptr<class GameEngineRenderer> Render0;
	std::shared_ptr<class GameEngineRenderer> Render1;
	std::shared_ptr<class GameEngineRenderer> Render2;

};

