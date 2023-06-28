#pragma once

// Ό³Έν :
class OverworldLevel : public GameEngineLevel
{
public:
	static OverworldLevel* OverworldLevelPtr;

	// constrcuter destructer
	OverworldLevel();
	~OverworldLevel();

	// delete Function
	OverworldLevel(const OverworldLevel& _Other) = delete;
	OverworldLevel(OverworldLevel&& _Other) noexcept = delete;
	OverworldLevel& operator=(const OverworldLevel& _Other) = delete;
	OverworldLevel& operator=(OverworldLevel&& _Other) noexcept = delete;

	std::shared_ptr<class FadeEffect> FEffect = nullptr;

	std::shared_ptr<class RoundBlackBox> GetBlackBoxPtr()
	{
		return BlackBoxPtr;
	}

	void SetFrogEnd()
	{
		FrogEnd = true;
	}

	void SetDragonEnd()
	{
		DragonEnd = true;
	}

	void SetMouseEnd()
	{
		MouseEnd = true;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	std::shared_ptr<class Player_Overworld> PlayerObject = nullptr;
	std::shared_ptr<class Overworld_ColMap> ThisColMap = nullptr;
	std::shared_ptr<class OverworldGUI> GUI = nullptr;

	std::shared_ptr<class Overworld_Map> MapObject = nullptr;
	std::shared_ptr<class PortalDoor> PortalDoorObject = nullptr;
	std::shared_ptr<class RoundBlackBox> BlackBoxPtr = nullptr;

	void BuildingFlagOn();
	void ReLoadSetting();
	void PlayerDebugRenderOn();
	void PlayerDebugRenderOff();
	void LevelDebugOn();
	void LevelDebugOff();
	
	bool IsSet1 = false;
	bool IsSet2 = false;

	bool FrogEnd = false;
	bool DragonEnd = false;
	bool MouseEnd = false;
	int FrogEndCount = 1;
	int DragonEndCount = 1;
	int MouseEndCount = 1;

	int DebugBoxCount = 1;
};

