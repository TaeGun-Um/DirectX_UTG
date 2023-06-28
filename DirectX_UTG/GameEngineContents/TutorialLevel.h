#pragma once

// Ό³Έν :
class TutorialLevel : public GameEngineLevel
{
public:
	static TutorialLevel* TutorialLevelPtr;

	// constrcuter destructer
	TutorialLevel();
	~TutorialLevel();

	// delete Function
	TutorialLevel(const TutorialLevel& _Other) = delete;
	TutorialLevel(TutorialLevel&& _Other) noexcept = delete;
	TutorialLevel& operator=(const TutorialLevel& _Other) = delete;
	TutorialLevel& operator=(TutorialLevel&& _Other) noexcept = delete;

	std::shared_ptr<class RoundBlackBox> GetBlackBoxPtr()
	{
		return BlackBoxPtr;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	std::shared_ptr<class HealthUI> HealthObject = nullptr;
	std::shared_ptr<class CardUI> CardObject = nullptr;
	std::shared_ptr<class WeaponUI> WeaponObject = nullptr;
	std::shared_ptr<class Player> PlayerObject = nullptr;
	std::shared_ptr<class Tutorial_ColMap> ThisColMap = nullptr;
	std::shared_ptr<class TransformGUI> GUI = nullptr;

	std::shared_ptr<class Tutorial_Map> MapObject = nullptr;
	std::shared_ptr<class Tutorial_BackLayer> LayerObject = nullptr;
	std::shared_ptr<class Tutorial_BackGround> BGObject = nullptr;
	std::shared_ptr<class Tutorial_Target> TargetObject = nullptr;
	std::shared_ptr<class PortalDoor> PortalDoorObject = nullptr;
	std::shared_ptr<class RoundBlackBox> BlackBoxPtr = nullptr;

	void PlayerDebugRenderOn();
	void PlayerDebugRenderOff();
	void LevelDebugOn();
	void LevelDebugOff();
};

