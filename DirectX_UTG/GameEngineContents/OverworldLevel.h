#pragma once

// Ό³Έν :
class OverworldLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	OverworldLevel();
	~OverworldLevel();

	// delete Function
	OverworldLevel(const OverworldLevel& _Other) = delete;
	OverworldLevel(OverworldLevel&& _Other) noexcept = delete;
	OverworldLevel& operator=(const OverworldLevel& _Other) = delete;
	OverworldLevel& operator=(OverworldLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	std::shared_ptr<class Player_Overworld> PlayerObject = nullptr;
	std::shared_ptr<class Overworld_ColMap> ThisColMap = nullptr;
	std::shared_ptr<class TransformGUI> GUI = nullptr;

	std::shared_ptr<class Overworld_Map> MapObject = nullptr;
	std::shared_ptr<class PortalDoor> PortalDoorObject = nullptr;

	void PlayerDebugRenderOn();
	void PlayerDebugRenderOff();
	void LevelDebugOn();
	void LevelDebugOff();

};

