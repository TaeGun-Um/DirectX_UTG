#pragma once

// Ό³Έν :
class DragonLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	DragonLevel();
	~DragonLevel();

	// delete Function
	DragonLevel(const DragonLevel& _Other) = delete;
	DragonLevel(DragonLevel&& _Other) noexcept = delete;
	DragonLevel& operator=(const DragonLevel& _Other) = delete;
	DragonLevel& operator=(DragonLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	std::shared_ptr<class GrimMatchstick> DragonObject = nullptr;
	std::shared_ptr<class TestActor> TestActorObject = nullptr;

};

