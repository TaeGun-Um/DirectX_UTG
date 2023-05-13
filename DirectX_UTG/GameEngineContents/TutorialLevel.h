#pragma once

// 설명 :
class TutorialLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TutorialLevel();
	~TutorialLevel();

	// delete Function
	TutorialLevel(const TutorialLevel& _Other) = delete;
	TutorialLevel(TutorialLevel&& _Other) noexcept = delete;
	TutorialLevel& operator=(const TutorialLevel& _Other) = delete;
	TutorialLevel& operator=(TutorialLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	std::shared_ptr<class Player> PlayerObject = nullptr;
	std::shared_ptr<class TestPlatform> PlatformObject = nullptr; // 지울것
	std::shared_ptr<class Tutorial_ColMap> ThisColMap = nullptr;
	std::shared_ptr<class TransformGUI> GUI = nullptr;

	void PlayerDebugRenderOn();
	void PlayerDebugRenderOff();
	void TutorialColMapOn();
	void TutorialColMapOff();
};

