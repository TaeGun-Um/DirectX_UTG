#pragma once

#include <GameEngineCore\GameEngineLevel.h>

// Ό³Έν :
class TestLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TestLevel();
	~TestLevel();

	// delete Function
	TestLevel(const TestLevel& _Other) = delete;
	TestLevel(TestLevel&& _Other) noexcept = delete;
	TestLevel& operator=(const TestLevel& _Other) = delete;
	TestLevel& operator=(TestLevel&& _Other) noexcept = delete;

	std::shared_ptr<class GameEngineVideo> Video;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	void PlayerCreate();

	std::shared_ptr<class Player> PlayerObject = nullptr;
	std::shared_ptr<class TransformGUI> GUI = nullptr;
};
